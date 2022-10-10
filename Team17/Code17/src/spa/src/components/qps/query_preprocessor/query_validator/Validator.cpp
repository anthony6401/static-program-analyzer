#include "Validator.h"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/qps/abstract_query_object/SuchThat.h"
#include "components/qps/abstract_query_object/Pattern.h"
#include "components/qps/abstract_query_object/With.h"
#include <unordered_map>
#include <stdexcept>
#include <memory>

using namespace qps;

Validator::Validator(QueryObject parsedQuery) {
	this->parsedQuery = parsedQuery;
};

QueryObject Validator::validate() {
	if (!isSemanticallyValid()) {
		this->parsedQuery.setSemanticallyInvalid();
	}

	return this->parsedQuery;
}

bool Validator::isSemanticallyValid() {
	// If query has SyntaxError, do not proceed with checking for SemanticError
	if (!this->parsedQuery.isSyntacticallyCorrect()) {
		return true;
	}

	int numOfDeclaredSynonyms = this->parsedQuery.getNumOfDeclaredSynonyms();

	// No declaration clause
	if (numOfDeclaredSynonyms == 0) {
		return false;
	}

	std::unordered_map<std::string, DesignEntity> declaredSynonyms = this->parsedQuery.getSynonymToDesignEntityMap();

	// Declaration contains multiple synonyms with the same name
	if (numOfDeclaredSynonyms > declaredSynonyms.size()) {
		return false;
	}

	if (!selectClauseIsSemanticallyCorrect()) {
		return false;
	}

	if (!suchThatClauseIsSemanticallyCorrect()) {
		return false;
	}

	if (!patternClauseIsSemanticallyCorrect()) {
		return false;
	}

	if (!withClauseIsSemanticallyCorrect()) {
		return false;
	}

	return true;
};

bool Validator::selectClauseIsSemanticallyCorrect() {
	Select selectClause = this->parsedQuery.getSelect();
	TokenType returnType = selectClause.getReturnType();
	std::vector<TokenObject> returnValues = selectClause.getReturnValues();

	std::vector<TokenObject> attributeTokens{};

	std::unordered_map<std::string, DesignEntity> mappedSynonyms = this->parsedQuery.getSynonymToDesignEntityMap();

	for (TokenObject token : returnValues) {
		TokenType currTokenType = token.getTokenType();
		std::string tokenValue = token.getValue();

		if ((currTokenType == TokenType::ATTRIBUTE_SYNONYM) || currTokenType == TokenType::ATTRIBUTE_NAME) {
			attributeTokens.push_back(token);
			continue;
		}

		// Synonym is not declared
		if (mappedSynonyms.find(tokenValue) == mappedSynonyms.end()) {
			if (tokenValue == "BOOLEAN" && returnType == TokenType::BOOLEAN) {
				continue;
			}
			return false;
		}

		// BOOLEAN used as a synonym in declaration, convert return type to SYNONYM
		if (tokenValue == "BOOLEAN" && returnType == TokenType::BOOLEAN) {
			this->parsedQuery.setReturnTypeToSynonym();
		}

	}
	
	if (!isValidAttrRef(attributeTokens)) {
		return false;
	}

	return true;
};

bool Validator::suchThatClauseIsSemanticallyCorrect() {
	std::vector<SuchThat> suchThatClause = this->parsedQuery.getRelationships();
	bool isSemanticallyCorrect = true;

	for (SuchThat relationship : suchThatClause) {
		TokenType relationshipType = relationship.getRelationshipType();

		if (relationshipType == TokenType::USES || relationshipType == TokenType::MODIFIES) {
			isSemanticallyCorrect = isSemanticallyCorrect && isValidUsesAndModifies(relationship);
		}

		if (relationshipType == TokenType::CALLS || relationshipType == TokenType::CALLS_T) {
			isSemanticallyCorrect = isSemanticallyCorrect && isValidCalls(relationship);
		}

		if (relationshipType == TokenType::FOLLOWS || relationshipType == TokenType::FOLLOWS_T ||
			relationshipType == TokenType::PARENT || relationshipType == TokenType::PARENT_T ||
			relationshipType == TokenType::NEXT || relationshipType == TokenType::NEXT_T) {
			isSemanticallyCorrect = isSemanticallyCorrect && isValidFollowsParentNext(relationship);

		}

		if (!isSemanticallyCorrect) {
			return false;
		}
	}

	return true;
};

bool Validator::patternClauseIsSemanticallyCorrect() {
	std::vector<Pattern> patternClause = this->parsedQuery.getPattern();

	for (Pattern pattern : patternClause) {
		std::string assignSynonym = pattern.getSynonym();
		TokenObject leftParam = pattern.getLeft();

		// Check that synonym is declared and declared as assign design entity
		if (!isDeclaredSynonym(assignSynonym)) {
			return false;
		}

		if (!isAssign(assignSynonym)) {
			return false;
		}

		// Check first parameter is valid
		if (leftParam.getTokenType() == TokenType::NAME) {
			std::string synonymName = leftParam.getValue();

			// Synonym name is not declared or does not have the appropriate design entity
			if (!isDeclaredSynonym(synonymName)) {
				return false;
			}

			if (!isVariable(synonymName)) {
				return false;
			}

		}

	}

	return true;
};

bool Validator::withClauseIsSemanticallyCorrect() {
	std::vector<With> withClause = this->parsedQuery.getWith();

	for (With with : withClause) {
		TokenType leftType = with.getLeftType();
		TokenType rightType = with.getRightType();

		if (leftType != rightType) {
			return false;
		}

		// If ref is IDENT or INTEGER, no need to validate. Hence, we only check if attribute is valid
		std::vector<TokenObject> left = with.getLeft();

		if (left.size() > 1) {
			if (!isValidAttrRef(left)) {
				return false;
			}
		}

		std::vector<TokenObject> right = with.getRight();

		if (right.size() > 1) {
			if (!isValidAttrRef(right)) {
				return false;
			}
		}


	}

	return true;
};

bool Validator::isValidUsesAndModifies(SuchThat relationship) {
	TokenObject leftParam = relationship.getLeft();
	TokenObject rightParam = relationship.getRight();

	// First parameter of Uses and Modifies cannot be WILDCARD due to ambiguity
	if (leftParam.getTokenType() == TokenType::WILDCARD) {
		return false;
	}

	// Check first parameter is valid
	if (leftParam.getTokenType() == TokenType::NAME) {
		std::string synonymName = leftParam.getValue();

		// Synonym name is not declared or does not have the appropriate design entity
		if (!isDeclaredSynonym(synonymName)) {
			return false;
		}

		if (!isValidUsesAndModifiesLeftParameter(synonymName)) {
			return false;
		}

	}

	// Check second parameter if valid
	if (rightParam.getTokenType() == TokenType::NAME) {
		std::string synonymName = rightParam.getValue();

		// Synonym name is not declared or does not have the appropriate design entity
		if (!isDeclaredSynonym(synonymName)) {
			return false;
		}

		if (!isVariable(synonymName)) {
			return false;
		}

	}

	return true;
}

bool Validator::isValidFollowsParentNext(SuchThat relationship) {
	TokenObject leftParam = relationship.getLeft();
	TokenObject rightParam = relationship.getRight();

	// Check first parameter is valid
	if (leftParam.getTokenType() == TokenType::NAME) {
		std::string synonymName = leftParam.getValue();

		// Synonym name is not declared or does not have the appropriate design entity
		if (!isDeclaredSynonym(synonymName)) {
			return false;
		}

		if (!isStatement(synonymName)) {
			return false;
		}

	}

	// Check second parameter if valid
	if (rightParam.getTokenType() == TokenType::NAME) {
		std::string synonymName = rightParam.getValue();

		// Synonym name is not declared or does not have the appropriate design entity
		if (!isDeclaredSynonym(synonymName)) {
			return false;
		}

		if (!isStatement(synonymName)) {
			return false;
		}

	}

	return true;
}


bool Validator::isValidCalls(SuchThat relationship) {
	TokenObject leftParam = relationship.getLeft();
	TokenObject rightParam = relationship.getRight();

	// Check first parameter is valid
	if (leftParam.getTokenType() == TokenType::NAME) {
		std::string synonymName = leftParam.getValue();

		// Synonym name is not declared or does not have the appropriate design entity
		if (!isDeclaredSynonym(synonymName)) {
			return false;
		}

		if (!isProcedure(synonymName)) {
			return false;
		}

	}

	// Check second parameter if valid
	if (rightParam.getTokenType() == TokenType::NAME) {
		std::string synonymName = rightParam.getValue();

		// Synonym name is not declared or does not have the appropriate design entity
		if (!isDeclaredSynonym(synonymName)) {
			return false;
		}

		if (!isProcedure(synonymName)) {
			return false;
		}

	}

	return true;
}

bool Validator::isDeclaredSynonym(std::string synonym) {
	std::unordered_map<std::string, DesignEntity> mappedSynonyms = this->parsedQuery.getSynonymToDesignEntityMap();
	if (mappedSynonyms.find(synonym) == mappedSynonyms.end()) {
		return false;
	}

	return true;
}


bool Validator::isStatement(std::string synonym) {
	std::vector<DesignEntity> validDesignEntities = this->statementDesignEntities;
	DesignEntity designEntityOfSynonym = this->parsedQuery.getSynonymToDesignEntityMap().at(synonym);

	if (std::find(validDesignEntities.begin(), validDesignEntities.end(), designEntityOfSynonym) == validDesignEntities.end()) {
		return false;
	}

	return true;
};

bool Validator::isVariable(std::string synonym) {
	DesignEntity designEntityOfSynonym = this->parsedQuery.getSynonymToDesignEntityMap().at(synonym);

	if (designEntityOfSynonym != DesignEntity::VARIABLE) {
		return false;
	}

	return true;
};

bool Validator::isAssign(std::string synonym) {
	DesignEntity designEntityOfSynonym = this->parsedQuery.getSynonymToDesignEntityMap().at(synonym);

	if (designEntityOfSynonym != DesignEntity::ASSIGN) {
		return false;
	}

	return true;
};

bool Validator::isProcedure(std::string synonym) {
	DesignEntity designEntityOfSynonym = this->parsedQuery.getSynonymToDesignEntityMap().at(synonym);

	if (designEntityOfSynonym != DesignEntity::PROCEDURE) {
		return false;
	}

	return true;
};

bool Validator::isValidUsesAndModifiesLeftParameter(std::string synonym) {
	// Removed READ since according to the slides, READ is not a valid parameter for Uses and Modifies
	std::vector<DesignEntity> validDesignEntities = this->validDesignEntitiesForUsesAndModifies;

	DesignEntity designEntityOfSynonym = this->parsedQuery.getSynonymToDesignEntityMap().at(synonym);

	if (std::find(validDesignEntities.begin(), validDesignEntities.end(), designEntityOfSynonym) == validDesignEntities.end()) {
		return false;
	}

	return true;
};

bool Validator::isValidAttrNameToAttrSynonym(std::string attrName, DesignEntity attrSynonymDesignEntity) {
	std::vector<DesignEntity> validDesignEntities = this->attrNameToValidDesignEntity.at(attrName);

	if (std::find(validDesignEntities.begin(), validDesignEntities.end(), attrSynonymDesignEntity) == validDesignEntities.end()) {
		return false;
	}

	return true;
};

bool Validator::isValidAttrRef(std::vector<TokenObject> ref) {
	DesignEntity currAttributeSynonymDesignEntity{};
	std::unordered_map<std::string, DesignEntity> mappedSynonyms = this->parsedQuery.getSynonymToDesignEntityMap();

	for (TokenObject token : ref) {
		TokenType currTokenType = token.getTokenType();
		std::string tokenValue = token.getValue();

		if (currTokenType == TokenType::ATTRIBUTE_SYNONYM) {
			// Synonym is not declared
			if (mappedSynonyms.find(tokenValue) == mappedSynonyms.end()) {
				return false;
			}

			currAttributeSynonymDesignEntity = mappedSynonyms.at(tokenValue);
			continue;
		}

		if (currTokenType == TokenType::ATTRIBUTE_NAME) {
			bool isValidAttrName = isValidAttrNameToAttrSynonym(tokenValue, currAttributeSynonymDesignEntity);

			if (!isValidAttrName) {
				return false;
			}
			continue;
		}

		// token is neither attribute synonym nor attribute name, thus not valid attribute
		// should never reach here!!
		throw std::runtime_error("Error validating attribute");
	}

	return true;

}

