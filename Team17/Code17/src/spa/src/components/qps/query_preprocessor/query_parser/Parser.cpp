#include "Parser.h"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/abstract_query_object/Declaration.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/qps/abstract_query_object/SuchThat.h"
#include "components/qps/abstract_query_object/Pattern.h"
#include <unordered_map>
#include <memory>

using namespace qps;

Parser::Parser() {};

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

	// Syntax checking for such that clause and pattern clause to be done next sprint

	if (!hasNoSyntaxError) {
		return QueryObject();
	}

	std::unordered_map<std::string, DesignEntity> mappedSynonyms = mapSynonymToDesignEntity(declarationTokenObjects);
	Select select = parseTokensIntoSelectObject(selectTokenObjects, mappedSynonyms);
	std::vector<SuchThat> relationships = parseTokensIntoSuchThatObjects();
	std::vector<Pattern> pattern = parseTokensIntoPatternObjects();

	return QueryObject(select, relationships, pattern, mappedSynonyms);
};

std::vector<std::vector<TokenObject>> Parser::groupQueryIntoClause() {
	std::vector<TokenObject> declarationTokenObjects;
	std::vector<TokenObject> selectTokenObjects;
	std::vector<TokenObject> relationshipTokenObjects;
	std::vector<TokenObject> patternTokenObjects;

	// Get vector of token types of objects
	std::vector<TokenType> tokenTypes = getTokenTypes(this->tokenizedQuery);
	
	// Find where each clause starts and ends
	auto beginIndex = this->tokenizedQuery.begin();
	int endIndex = this->tokenizedQuery.size();
	int selectIndex = getTokenIndex(TokenType::SELECT, tokenTypes);
	int suchIndex = getTokenIndex(TokenType::SUCH, tokenTypes);
	int patternIndex = getTokenIndex(TokenType::PATTERN, tokenTypes);

	// Group declarations
	// One or more declarations present
	if (selectIndex > 0) {
		std::vector<TokenObject> declarationTokens(beginIndex, beginIndex + selectIndex);
		declarationTokenObjects = declarationTokens;
	}

	// Group Select clause
	// Such that clause present
	if (suchIndex < endIndex) {
		std::vector<TokenObject> selectTokens(beginIndex + selectIndex, beginIndex + suchIndex);
		selectTokenObjects = selectTokens;
	}
	// Only pattern clause present
	else if (patternIndex < endIndex) {
		std::vector<TokenObject> selectTokens(beginIndex + selectIndex, beginIndex + patternIndex);
		selectTokenObjects = selectTokens;
	}
	// Neither such that nor pattern clause present
	else {
		std::vector<TokenObject> selectTokens(beginIndex + selectIndex, beginIndex + patternIndex);
		selectTokenObjects = selectTokens;
	}

	// Group such that clause
	if (suchIndex < endIndex) {
		// If no pattern clause, patternIndex == this->tokenizedQuery.end()
		std::vector<TokenObject> relationshipTokens(beginIndex + suchIndex, beginIndex + patternIndex);
		relationshipTokenObjects = relationshipTokens;
	}

	// Group pattern clause
	if (patternIndex < endIndex) {
		std::vector<TokenObject> patternTokens(beginIndex + patternIndex, beginIndex + endIndex);
		patternTokenObjects = patternTokens;
	}

	std::vector<std::vector<TokenObject>> groupedQuery{
		declarationTokenObjects, 
		selectTokenObjects, 
		relationshipTokenObjects, 
		patternTokenObjects 
	};

	return groupedQuery;
};

int Parser::getTokenIndex(TokenType token, std::vector<TokenType> tokenTypes) {
	auto index = std::find(tokenTypes.begin(), tokenTypes.end(), token);

	return index - tokenTypes.begin();
};

bool Parser::isSyntacticallyCorrect(std::vector<TokenObject> tokenizedClause, SyntaxChecker* checker) {
	return checker->isSyntacticallyCorrect(tokenizedClause);
}

std::vector<TokenType> Parser::getTokenTypes(std::vector<TokenObject> tokenObjects) {
	std::vector<TokenType> tokenTypes;
	
	for (TokenObject token: tokenObjects) {
		tokenTypes.push_back(token.getTokenType());
	}

	return tokenTypes;
};

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

		mappedSynonyms.insert({token.getValue(), currDesignEntity});

	}

	return mappedSynonyms;
}

Select Parser::parseTokensIntoSelectObject(std::vector<TokenObject> selectTokens, std::unordered_map<std::string, DesignEntity> mappedSynonyms) {
	for (TokenObject token : selectTokens) {
		if (token.getTokenType() == TokenType::SELECT) {
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

// To be amended
std::vector<SuchThat> Parser::parseTokensIntoSuchThatObjects() {
	std::vector<SuchThat> relationships;
	return relationships;
};

// To be amended
std::vector<Pattern> Parser::parseTokensIntoPatternObjects() {
	std::vector<Pattern> patterns;
	return patterns;
};
