#include "Parser.h"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/qps/abstract_query_object/SuchThat.h"
#include "components/qps/abstract_query_object/Pattern.h"
#include "components/qps/abstract_query_object/With.h"
#include <unordered_map>
#include <stdexcept>
#include <memory>
#include <sstream>

using namespace qps;

Parser::Parser(std::vector<TokenObject> tokenizedQuery) {
	this->tokenizedQuery = tokenizedQuery;
};

QueryObject Parser::parse() {
	std::vector<std::vector<TokenObject>> groupedQueryTokens = groupQueryIntoClause();
	std::vector<TokenObject> declarationTokenObjects = groupedQueryTokens[0];
	std::vector<TokenObject> selectTokenObjects = groupedQueryTokens[1];
	std::vector<TokenObject> relationshipTokenObjects = groupedQueryTokens[2];
	std::vector<TokenObject> patternTokenObjects = groupedQueryTokens[3];
	std::vector<TokenObject> withTokenObjects = groupedQueryTokens[4];

	bool hasNoSyntaxError = true;

	if (declarationTokenObjects.size() > 0) {
		hasNoSyntaxError = hasNoSyntaxError && isSyntacticallyCorrect(declarationTokenObjects, new DeclarationClauseSyntaxChecker());
	}

	hasNoSyntaxError = hasNoSyntaxError && isSyntacticallyCorrect(selectTokenObjects, new SelectClauseSyntaxChecker);

	if (relationshipTokenObjects.size() > 0) {
		hasNoSyntaxError = hasNoSyntaxError && isSyntacticallyCorrect(relationshipTokenObjects, new SuchThatClauseSyntaxChecker());
	}

	if (patternTokenObjects.size() > 0) {
		hasNoSyntaxError = hasNoSyntaxError && isSyntacticallyCorrect(patternTokenObjects, new PatternClauseSyntaxChecker());
	}

	if (withTokenObjects.size() > 0) {
		hasNoSyntaxError = hasNoSyntaxError && isSyntacticallyCorrect(withTokenObjects, new WithClauseSyntaxChecker());
	}

	if (!hasNoSyntaxError) {
		return QueryObject();
	}

	auto [numOfDeclaredSynonyms, mappedSynonyms] = mapSynonymToDesignEntity(declarationTokenObjects);
	Select select = parseTokensIntoSelectObject(selectTokenObjects);
	std::vector<SuchThat> relationships = parseTokensIntoSuchThatObjects(relationshipTokenObjects);
	std::vector<Pattern> patterns = parseTokensIntoPatternObjects(patternTokenObjects);
	std::vector<With> withs = parseTokensIntoWithObjects(withTokenObjects);

	return QueryObject(select, relationships, patterns, mappedSynonyms, numOfDeclaredSynonyms);
};

std::vector<std::vector<TokenObject>> Parser::groupQueryIntoClause() {
	std::vector<TokenObject> declarationTokenObjects;
	std::vector<TokenObject> selectTokenObjects;
	std::vector<TokenObject> relationshipTokenObjects;
	std::vector<TokenObject> patternTokenObjects;
	std::vector<TokenObject> withTokenObjects;

	bool isEndOfDeclaration = true;
	bool isSelectClause = false;
	bool isSuchThatClause = false;
	bool isPatternClause = false;
	bool isWithClause = false;
	bool isPrevClauseSuchThatClause = false;
	bool isPrevClausePatternClause = false;
	bool isPrevClauseWithClause = false;
	bool isPrevEqualsToken = false;

	for (TokenObject token : this->getTokenizedQuery()) {
		TokenType tokenType = token.getTokenType();

		if (isDesignEntityToken(tokenType) && isEndOfDeclaration && !isSelectClause && !isSuchThatClause && !isPatternClause && !isWithClause) {
			declarationTokenObjects.push_back(token);
			isEndOfDeclaration = false;
			continue;
		}

		// Any extra semi-colons shall be taken as a declaration token
		if (tokenType == TokenType::SEMI_COLON) {
			declarationTokenObjects.push_back(token);
			isEndOfDeclaration = true;
			continue;
		}

		if (!isEndOfDeclaration) {
			declarationTokenObjects.push_back(token);
			continue;
		}

		// Start of such that clause
		if (tokenType == TokenType::SUCH && !isSuchThatClause && !isPatternClause && !isWithClause) {
			if (isSelectClause && selectTokenObjects.size() < 2) {
				selectTokenObjects.push_back(token);
				continue;
			}
			relationshipTokenObjects.push_back(token);
			isSelectClause = false;
			isSuchThatClause = true;
			continue;
		}

		// End of such that clause
		if (tokenType == TokenType::CLOSED_BRACKET && !isSelectClause && isSuchThatClause && !isPatternClause && !isWithClause) {
			relationshipTokenObjects.push_back(token);
			isSuchThatClause = false;
			isPrevClauseSuchThatClause = true;
			isPrevClausePatternClause = false;
			isPrevClauseWithClause = false;
			continue;
		}

		// Start of pattern clause
		if (tokenType == TokenType::PATTERN && !isSuchThatClause && !isPatternClause && !isWithClause) {
			if (isSelectClause && selectTokenObjects.size() < 2) {
				selectTokenObjects.push_back(token);
				continue;
			}
			patternTokenObjects.push_back(token);
			isPatternClause = true;
			isSelectClause = false;
			continue;
		}

		// End of pattern clause
		if (tokenType == TokenType::CLOSED_BRACKET && !isSelectClause && !isSuchThatClause && isPatternClause && !isWithClause) {
			patternTokenObjects.push_back(token);
			isPatternClause = false;
			isPrevClauseSuchThatClause = false;
			isPrevClausePatternClause = true;
			isPrevClauseWithClause = false;
			continue;
		}

		// Start of with clause
		if (tokenType == TokenType::WITH && !isSuchThatClause && !isPatternClause && !isWithClause) {
			if (isSelectClause && selectTokenObjects.size() < 2) {
				selectTokenObjects.push_back(token);
				continue;
			}
			withTokenObjects.push_back(token);
			isSelectClause = false;
			isWithClause = true;
			continue;
		}

		if (tokenType == TokenType::EQUALS && !isSuchThatClause && !isPatternClause && isWithClause) {
			withTokenObjects.push_back(token);
			isPrevEqualsToken = true;
			continue;
		}

		// End of with clause
		if (isPrevEqualsToken && !isSuchThatClause && !isPatternClause && isWithClause) {
			withTokenObjects.push_back(token);
			isPrevEqualsToken = false;
			isWithClause = false;
			isPrevClauseSuchThatClause = false;
			isPrevClausePatternClause = false;
			isPrevClauseWithClause = true;
			continue;
		}

		if (tokenType == TokenType::AND && !isSuchThatClause && !isPatternClause && !isWithClause) {
			if (isSelectClause && selectTokenObjects.size() < 2) {
				selectTokenObjects.push_back(token);
				continue;
			}

			if (isPrevClauseSuchThatClause) {
				relationshipTokenObjects.push_back(token);
				isSelectClause = false;
				isSuchThatClause = true;
				isWithClause = false;
				isPrevClauseSuchThatClause = false;
				continue;
			}

			if (isPrevClausePatternClause) {
				patternTokenObjects.push_back(token);
				isPatternClause = true;
				isSelectClause = false;
				isWithClause = false;
				isPrevClausePatternClause = false;
				continue;
			}

			if (isPrevClauseWithClause) {
				withTokenObjects.push_back(token);
				isWithClause = true;
				isPatternClause = false;
				isSelectClause = false;
				isPrevClauseWithClause = false;
				continue;
			}

		}

		// Start of select clause
		if (isEndOfDeclaration && !isSelectClause && !isSuchThatClause && !isPatternClause && !isWithClause) {
			selectTokenObjects.push_back(token);
			isSelectClause = true;
			continue;
		}

		if (isSelectClause) {
			selectTokenObjects.push_back(token);
			continue;
		}

		if (isSuchThatClause) {
			relationshipTokenObjects.push_back(token);
			continue;
		}

		if (isPatternClause) {
			patternTokenObjects.push_back(token);
			continue;
		}

		if (isWithClause) {
			patternTokenObjects.push_back(token);
			continue;
		}

		// Throw generalized exception for now, will change in the future
		throw std::runtime_error("Error parsing query");
	}

	std::vector<std::vector<TokenObject>> groupedQuery{
		declarationTokenObjects,
		selectTokenObjects,
		relationshipTokenObjects,
		patternTokenObjects,
		withTokenObjects
	};

	return groupedQuery;
};

bool Parser::isSyntacticallyCorrect(std::vector<TokenObject> tokenizedClause, SyntaxChecker* checker) {
	return checker->isSyntacticallyCorrect(tokenizedClause);
}

std::vector<TokenObject> Parser::getTokenizedQuery() {
	return this->tokenizedQuery;
}

std::tuple<int, std::unordered_map<std::string, DesignEntity>> Parser::mapSynonymToDesignEntity(std::vector<TokenObject> declarations) {
	std::unordered_map<std::string, DesignEntity> mappedSynonyms;
	DesignEntity currDesignEntity;
	bool newDeclaration = true;
	int numOfDeclaredSynonyms = 0;

	for (TokenObject token : declarations) {
		TokenType currTokenType = token.getTokenType();

		if (currTokenType == TokenType::COMMA) {
			continue;
		}

		if (currTokenType == TokenType::SEMI_COLON) {
			newDeclaration = true;
			continue;
		}

		if (newDeclaration) {
			currDesignEntity = this->tokenToDesignEntity.at(currTokenType);
			newDeclaration = false;
			continue;
		}

		mappedSynonyms.insert({ token.getValue(), currDesignEntity });
		++numOfDeclaredSynonyms;

	}

	return { numOfDeclaredSynonyms, mappedSynonyms };
}

Select Parser::parseTokensIntoSelectObject(std::vector<TokenObject> selectTokens) {
	bool isFirstSelectToken = true;

	for (TokenObject token : selectTokens) {
		TokenType currTokenType = token.getTokenType();

		if ((currTokenType == TokenType::SELECT) && isFirstSelectToken) {
			isFirstSelectToken = false;
			continue;
		}

		// Will check if BOOLEAN is declared as a design entity in Validator
		if (currTokenType == TokenType::BOOLEAN) {
			// Set TokenType to NAME in the event BOOLEAN is declared as a design entity
			// If return type is BOOLEAN, return values are ignored
			token.setTokenType(TokenType::NAME);
			return Select(TokenType::BOOLEAN, {token});
		}

		if (currTokenType == TokenType::TUPLE) {
			std::vector<TokenObject> tupleElements = parseTupleIntoIndividualTokens(token.getValue());
			return Select(TokenType::TUPLE, tupleElements);
		}

		if (currTokenType == TokenType::ATTRIBUTE) {
			auto [attrSynonym, attrName] = parseAttributeIntoIndividualTokens(token.getValue());
			return Select(TokenType::ATTRIBUTE, {attrSynonym, attrName});
		}

		// Change TokenType of synonyms tokenized to design entity tokens etc to NAME
		if ((currTokenType != TokenType::ATTRIBUTE) && (currTokenType != TokenType::NAME)) {
			token.setTokenType(TokenType::NAME);
		}

		return Select(TokenType::SYNONYM, {token});

	}

	return Select();
};

std::vector<SuchThat> Parser::parseTokensIntoSuchThatObjects(std::vector<TokenObject> relationshipTokens) {
	std::vector<SuchThat> relationships;
	bool isFirstSuchToken = true;
	bool isFirstThatToken = true;
	bool isFirstParam = true;
	bool isNewRelationship = true;
	TokenType currRelationship{};
	TokenObject leftParam = TokenObject();
	TokenObject rightParam = TokenObject();

	for (TokenObject token : relationshipTokens) {
		TokenType currTokenType = token.getTokenType();

		if ((currTokenType == TokenType::OPEN_BRACKET) || (currTokenType == TokenType::AND && isNewRelationship)) {
			continue;
		}

		if (currTokenType == TokenType::CLOSED_BRACKET) {
			// For multi such that clauses in advanced SPA
			isFirstSuchToken = true;
			isFirstThatToken = true;
			isNewRelationship = true;
			continue;
		}

		if ((currTokenType == TokenType::SUCH) && isFirstSuchToken) {
			isFirstSuchToken = false;
			continue;
		}

		if ((currTokenType == TokenType::THAT) && isFirstThatToken) {
			isFirstThatToken = false;
			continue;
		}

		if (currTokenType == TokenType::COMMA) {
			isFirstParam = false;
			continue;
		}

		if (this->isRelationshipToken(currTokenType) && isNewRelationship) {
			currRelationship = currTokenType;
			isNewRelationship = false;
			isFirstParam = true;
			continue;
		}


		// Change TokenType of synonyms tokenized to design entity tokens etc to NAME
		if ((currTokenType != TokenType::WILDCARD) && (currTokenType != TokenType::INTEGER) && (currTokenType != TokenType::NAME_WITH_QUOTATION)) {
			
			if (token.getTokenType() != TokenType::NAME) {
				token.setTokenType(TokenType::NAME);
			}
		}


		if (isFirstParam) {
			leftParam = token;
			continue;
		}

		rightParam = token;
		SuchThat relationship = SuchThat(currRelationship, leftParam, rightParam);
		relationships.push_back(relationship);

	}

	return relationships;
};

std::vector<Pattern> Parser::parseTokensIntoPatternObjects(std::vector<TokenObject> patternTokens) {
	std::vector<Pattern> patterns;
	bool isNewPattern = true;
	bool isFirstParam = true;
	std::string assignSynonym = "";
	TokenObject leftParam = TokenObject();
	TokenObject rightParam = TokenObject();

	for (TokenObject token : patternTokens) {
		TokenType currTokenType = token.getTokenType();

		if (currTokenType == TokenType::OPEN_BRACKET) {
			continue;
		}

		if (currTokenType == TokenType::CLOSED_BRACKET) {
			// For multi such that clauses in advanced SPA
			isNewPattern = true;
			isFirstParam = true;
			assignSynonym = "";
			continue;
		}

		if ((currTokenType == TokenType::PATTERN || currTokenType == TokenType::AND) && isNewPattern) {
			isNewPattern = false;
			continue;
		}

		if (currTokenType == TokenType::COMMA) {
			isFirstParam = false;
			continue;
		}

		// Change TokenType of synonyms tokenized to design entity tokens etc to NAME
		if ((currTokenType != TokenType::WILDCARD) && (currTokenType != TokenType::NAME_WITH_QUOTATION) && 
			(currTokenType != TokenType::EXPRESSION) && (currTokenType != TokenType::SUBEXPRESSION)) {

			if (token.getTokenType() != TokenType::NAME) {
				token.setTokenType(TokenType::NAME);
			}
		}

		if (assignSynonym.empty()) {
			assignSynonym = token.getValue();
			continue;
		}

		if (isFirstParam) {
			leftParam = token;
			continue;
		}

		rightParam = token;
		Pattern pattern = Pattern(assignSynonym, leftParam, rightParam);
		patterns.push_back(pattern);

	}
	return patterns;
};

std::vector<With> Parser::parseTokensIntoWithObjects(std::vector<TokenObject> withTokens) {
	std::vector<With> withs;
	bool isNewWith = true;
	bool isLeft = true;
	TokenType leftType;
	TokenType rightType;
	std::vector<TokenObject> left;
	std::vector<TokenObject> right;

	for (TokenObject token : withTokens) {
		TokenType currTokenType = token.getTokenType();

		if (currTokenType == TokenType::EQUALS) {
			continue;
		}

		if ((currTokenType == TokenType::WITH || currTokenType == TokenType::AND) && isNewWith) {
			isNewWith = false;
			continue;
		}

		if (isLeft) {
			if (currTokenType == TokenType::ATTRIBUTE) {
				auto [attrSynonym, attrName] = parseAttributeIntoIndividualTokens(token.getValue());
				left.push_back(attrSynonym);
				left.push_back(attrName);
				isLeft = false;

				leftType = setTokenTypeOfAttribute(attrName.getValue());
				continue;
			}

			// Ref is either NAME_WITH_QUOTATION or INTEGER
			left.push_back(token);
			leftType = token.getTokenType() == TokenType::NAME_WITH_QUOTATION ? TokenType::NAME : TokenType::INTEGER;
			continue;
		}

		if (currTokenType == TokenType::ATTRIBUTE) {
			auto [attrSynonym, attrName] = parseAttributeIntoIndividualTokens(token.getValue());
			right.push_back(attrSynonym);
			right.push_back(attrName);

			rightType = setTokenTypeOfAttribute(attrName.getValue());
		}
		else {
			// Ref is either NAME_WITH_QUOTATION or INTEGER
			right.push_back(token);
			rightType = token.getTokenType() == TokenType::NAME_WITH_QUOTATION ? TokenType::NAME : TokenType::INTEGER;
		}

		With with = With(leftType, rightType, left, right);
		withs.push_back(with);

		isLeft = true;
		isNewWith = true;
		left.clear();
		right.clear();

	}
	return withs;
}


bool Parser::isRelationshipToken(TokenType token) {
	std::vector<TokenType> relationshipTokens{
		TokenType::FOLLOWS, TokenType::FOLLOWS_T, TokenType::PARENT,
		TokenType::PARENT_T, TokenType::USES, TokenType::MODIFIES,
		TokenType::CALLS, TokenType::CALLS_T, TokenType::NEXT, TokenType::NEXT_T 
	};

	if (std::find(relationshipTokens.begin(), relationshipTokens.end(), token) == relationshipTokens.end()) {
		return false;
	}

	return true;
};

bool Parser::isDesignEntityToken(TokenType token) {
	std::vector<TokenType> designEntityTokens{
		TokenType::STMT, TokenType::READ, TokenType::PRINT, TokenType::CALL, TokenType::WHILE, 
		TokenType::IF, TokenType::ASSIGN, TokenType::VARIABLE, TokenType::CONSTANT, TokenType::PROCEDURE 
};

	if (std::find(designEntityTokens.begin(), designEntityTokens.end(), token) == designEntityTokens.end()) {
		return false;
	}

	return true;
};

std::vector<TokenObject> Parser::parseTupleIntoIndividualTokens(std::string tupleValue) {
	std::vector<TokenObject> elements{};
	std::string stringOfElements = tupleValue.substr(1, tupleValue.length() - 2);
	std::stringstream ss(stringOfElements);

	while (ss.good()) {
		std::string elementValue;
		std::getline(ss, elementValue, ',');

		bool isAttribute = std::find(elementValue.begin(), elementValue.end(), '.') != elementValue.end();

		if (isAttribute) {
			auto [attrSynonym, attrName] = parseAttributeIntoIndividualTokens(elementValue);
			elements.push_back(attrSynonym);
			elements.push_back(attrName);
			continue;
		}

		// Synonym
		elements.push_back({ TokenObject(TokenType::NAME, elementValue) });
	}

	return elements;
}

std::tuple<TokenObject, TokenObject> Parser::parseAttributeIntoIndividualTokens(std::string attribute) {
    size_t fullstopIndex = attribute.find('.');
    std::string synonymName = attribute.substr(0, fullstopIndex);
    std::string attributeName = attribute.substr(fullstopIndex + 1, attribute.length() - fullstopIndex - 1);

	return {TokenObject(TokenType::ATTRIBUTE_SYNONYM, synonymName), TokenObject(TokenType::ATTRIBUTE_NAME, attributeName)};
}

TokenType Parser::setTokenTypeOfAttribute(std::string attrName) {
	if ((attrName == "procName") || (attrName == "varName")) {
		return TokenType::NAME;
	}

	return TokenType::INTEGER;
}
