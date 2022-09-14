#include "Parser.h"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/abstract_query_object/Declaration.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/qps/abstract_query_object/SuchThat.h"
#include "components/qps/abstract_query_object/Pattern.h"
#include <unordered_map>
#include <stdexcept>
#include <memory>

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

	if (!hasNoSyntaxError) {
		return QueryObject();
	}

	std::unordered_map<std::string, DesignEntity> mappedSynonyms = mapSynonymToDesignEntity(declarationTokenObjects);
	Select select = parseTokensIntoSelectObject(selectTokenObjects, mappedSynonyms);
	std::vector<SuchThat> relationships = parseTokensIntoSuchThatObjects(relationshipTokenObjects, mappedSynonyms);
	std::vector<Pattern> patterns = parseTokensIntoPatternObjects(patternTokenObjects, mappedSynonyms);

	return QueryObject(select, relationships, patterns, mappedSynonyms);
};

std::vector<std::vector<TokenObject>> Parser::groupQueryIntoClause() {
	std::vector<TokenObject> declarationTokenObjects;
	std::vector<TokenObject> selectTokenObjects;
	std::vector<TokenObject> relationshipTokenObjects;
	std::vector<TokenObject> patternTokenObjects;

	bool isEndOfDeclaration = true;
	bool isSelectClause = false;
	bool isSuchThatClause = false;
	bool isPatternClause = false;

	for (TokenObject token : this->getTokenizedQuery()) {
		TokenType tokenType = token.getTokenType();

		if (isDesignEntityToken(tokenType) && isEndOfDeclaration && !isSelectClause && !isSuchThatClause && !isPatternClause) {
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
		if (tokenType == TokenType::SUCH && !isSuchThatClause && !isPatternClause) {
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
		if (tokenType == TokenType::CLOSED_BRACKET && !isSelectClause && isSuchThatClause && !isPatternClause) {
			relationshipTokenObjects.push_back(token);
			isSuchThatClause = false;
			continue;
		}

		// Start of pattern clause
		if (tokenType == TokenType::PATTERN && !isSuchThatClause && !isPatternClause) {
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
		if (tokenType == TokenType::CLOSED_BRACKET && !isSelectClause && !isSuchThatClause && isPatternClause) {
			patternTokenObjects.push_back(token);
			isPatternClause = false;
			continue;
		}

		// Start of select clause
		if (isEndOfDeclaration && !isSelectClause && !isSuchThatClause && !isPatternClause) {
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

		// Throw generalized exception for now, will change in the future
		throw std::runtime_error("Error parsing query");
	}

	std::vector<std::vector<TokenObject>> groupedQuery{
		declarationTokenObjects,
		selectTokenObjects,
		relationshipTokenObjects,
		patternTokenObjects
	};

	return groupedQuery;
};

bool Parser::isSyntacticallyCorrect(std::vector<TokenObject> tokenizedClause, SyntaxChecker* checker) {
	return checker->isSyntacticallyCorrect(tokenizedClause);
}

std::vector<TokenObject> Parser::getTokenizedQuery() {
	return this->tokenizedQuery;
}

std::unordered_map<std::string, DesignEntity> Parser::mapSynonymToDesignEntity(std::vector<TokenObject> declarations) {
	std::unordered_map<std::string, DesignEntity> mappedSynonyms;
	DesignEntity currDesignEntity;
	bool newDeclaration = true;

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

	}

	return mappedSynonyms;
}

Select Parser::parseTokensIntoSelectObject(std::vector<TokenObject> selectTokens, std::unordered_map<std::string, DesignEntity> mappedSynonyms) {
	bool isFirstSelectToken = true;

	for (TokenObject token : selectTokens) {
		if ((token.getTokenType() == TokenType::SELECT) && isFirstSelectToken) {
			isFirstSelectToken = false;
			continue;
		}

		std::string returnValue = token.getValue();

		// Return empty Select object if return value is not declared for now
		if (mappedSynonyms.find(returnValue) == mappedSynonyms.end()) {
			return Select();
		}

		return Select(returnValue);

	}

	return Select();
};

std::vector<SuchThat> Parser::parseTokensIntoSuchThatObjects(std::vector<TokenObject> relationshipTokens, std::unordered_map<std::string, DesignEntity> mappedSynonyms) {
	std::vector<SuchThat> relationships;
	bool isFirstSuchToken = true;
	bool isFirstThatToken = true;
	bool isFirstParam = true;
	TokenType currRelationship{};
	TokenObject leftParam = TokenObject();
	TokenObject rightParam = TokenObject();

	for (TokenObject token : relationshipTokens) {
		TokenType currTokenType = token.getTokenType();

		if ((currTokenType == TokenType::OPEN_BRACKET) || (currTokenType == TokenType::CLOSED_BRACKET)) {
			continue;
		}

		if (currTokenType == TokenType::CLOSED_BRACKET) {
			// For multi such that clauses in advanced SPA
			isFirstSuchToken = true;
			isFirstThatToken = true;
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

		if (this->isRelationshipToken(currTokenType)) {
			currRelationship = currTokenType;
			continue;
		}


		// Return vector with only empty SuchThat object if parameter value is not declared for now
		// SemanticError should be caught in PQL validator
		if ((currTokenType != TokenType::WILDCARD) && (currTokenType != TokenType::INTEGER) && (currTokenType != TokenType::NAME_WITH_QUOTATION)) {
			std::string paramValue = token.getValue();

			// Check synonym is declared
			if (mappedSynonyms.find(paramValue) == mappedSynonyms.end()) {
				relationships.clear();
				relationships.push_back(SuchThat());
				return relationships;
			}

			// Change TokenType of synonyms tokenized to design entity tokens etc to NAME
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

std::vector<Pattern> Parser::parseTokensIntoPatternObjects(std::vector<TokenObject> patternTokens, std::unordered_map<std::string, DesignEntity> mappedSynonyms) {
	std::vector<Pattern> patterns;
	bool isFirstPatternToken = true;
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
			isFirstPatternToken = true;
			isFirstParam = true;
			assignSynonym = "";
			continue;
		}

		if ((currTokenType == TokenType::PATTERN) && isFirstPatternToken) {
			isFirstPatternToken = false;
			continue;
		}

		if (currTokenType == TokenType::COMMA) {
			isFirstParam = false;
			continue;
		}

		// Return vector with only empty Pattern object if parameter value is not declared for now
		// SemanticError should be caught in PQL validator
		if ((currTokenType != TokenType::WILDCARD) && (currTokenType != TokenType::NAME_WITH_QUOTATION) && 
			(currTokenType != TokenType::EXPRESSION) && (currTokenType != TokenType::SUBEXPRESSION)) {
			std::string synonymValue = token.getValue();

			// Check synonym is declared
			if (mappedSynonyms.find(synonymValue) == mappedSynonyms.end()) {
				patterns.clear();
				patterns.push_back(Pattern());
				return patterns;
			}

			// Change TokenType of synonyms tokenized to design entity tokens etc to NAME
			if (token.getTokenType() != TokenType::NAME) {
				token.setTokenType(TokenType::NAME);
			}
		}

		if (assignSynonym.empty()) {
			// Semantic Error as synonym has to be of declared as ASSIGN
			if (mappedSynonyms.at(token.getValue()) != DesignEntity::ASSIGN) {
				patterns.clear();
				patterns.push_back(Pattern());
				return patterns;
			}

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

bool Parser::isRelationshipToken(TokenType token) {
	std::vector<TokenType> relationshipTokens{
		TokenType::FOLLOWS, TokenType::FOLLOWS_T, TokenType::PARENT,
		TokenType::PARENT_T, TokenType::USES, TokenType::MODIFIES };

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
