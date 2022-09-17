#include "Validator.h"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/abstract_query_object/Declaration.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/qps/abstract_query_object/SuchThat.h"
#include "components/qps/abstract_query_object/Pattern.h"
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

	return true;
};

bool Validator::selectClauseIsSemanticallyCorrect() {
	Select selectClause = this->parsedQuery.getSelect();
	std::string returnValue = selectClause.getSynonym();
	std::unordered_map<std::string, DesignEntity> mappedSynonyms = this->parsedQuery.getSynonymToDesignEntityMap();
	
	if (mappedSynonyms.find(returnValue) == mappedSynonyms.end()) {
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

		if (relationshipType == TokenType::FOLLOWS || relationshipType == TokenType::FOLLOWS_T ||
			relationshipType == TokenType::PARENT || relationshipType == TokenType::PARENT_T) {
			isSemanticallyCorrect = isSemanticallyCorrect && isValidFollowsAndParent(relationship);

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

bool Validator::isValidUsesAndModifies(SuchThat relationship) {
	TokenType relationshipType = relationship.getRelationshipType();
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

		if (relationshipType == TokenType::USES && !isValidUsesLeftParameter(synonymName)) {
			return false;
		}

		if (relationshipType == TokenType::MODIFIES && !isValidModifiesLeftParameter(synonymName)) {
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

bool Validator::isValidFollowsAndParent(SuchThat relationship) {
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

bool Validator::isValidUsesLeftParameter(std::string synonym) {
	// Removed READ since according to the slides, READ is not a valid parameter for Uses and Modifies
	std::vector<DesignEntity> validDesignEntities = this->validDesignEntitiesForUses;

	DesignEntity designEntityOfSynonym = this->parsedQuery.getSynonymToDesignEntityMap().at(synonym);

	if (std::find(validDesignEntities.begin(), validDesignEntities.end(), designEntityOfSynonym) == validDesignEntities.end()) {
		return false;
	}

	return true;
};


bool Validator::isValidModifiesLeftParameter(std::string synonym) {
	// Removed READ since according to the slides, READ is not a valid parameter for Uses and Modifies
	std::vector<DesignEntity> validDesignEntities = this->validDesignEntitiesForModifies;

	DesignEntity designEntityOfSynonym = this->parsedQuery.getSynonymToDesignEntityMap().at(synonym);

	if (std::find(validDesignEntities.begin(), validDesignEntities.end(), designEntityOfSynonym) == validDesignEntities.end()) {
		return false;
	}

	return true;
};
