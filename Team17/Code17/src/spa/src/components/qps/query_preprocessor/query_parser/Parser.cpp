#include "Parser.h"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/abstract_query_object/Declaration.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/qps/abstract_query_object/SuchThat.h"
#include "components/qps/abstract_query_object/Pattern.h"
#include <unordered_map>

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

	// Syntax checking for such that clause and pattern clause to be done next sprint

	if (!hasNoSyntaxError) {
		return *new QueryObject();
	}

	std::unordered_map<std::string, TokenType> mappedSynonyms = mapSynonymToDesignEntity(declarationTokenObjects);
	std::vector<Declaration> declarations = parseTokensIntoDeclarationObjects(mappedSynonyms);
	Select select = parseTokensIntoSelectObject(selectTokenObjects, mappedSynonyms);
	std::vector<SuchThat> relationships = parseTokensIntoSuchThatObjects();
	std::vector<Pattern> pattern = parseTokensIntoPatternObjects();

	return *new QueryObject(declarations, select, relationships, pattern, mappedSynonyms);
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

std::unordered_map<std::string, TokenType> Parser::mapSynonymToDesignEntity(std::vector<TokenObject> declarations) {
	std::unordered_map<std::string, TokenType> mappedSynonyms;
	TokenType currDesignEntity;

	for (TokenObject token : declarations) {
		TokenType currTokenType = token.getTokenType();

		if (currTokenType == TokenType::COMMA || currTokenType == TokenType::SEMI_COLON) {
			continue;
		}

		// Design entity
		if (currTokenType != TokenType::NAME) {
			currDesignEntity = currTokenType;
			continue;
		}

		mappedSynonyms.insert({token.getValue(), currDesignEntity});

	}

	return mappedSynonyms;
}


std::vector<Declaration> Parser::parseTokensIntoDeclarationObjects(std::unordered_map<std::string, TokenType> mappedSynonyms) {
	std::vector<Declaration> declarations;
	
	// Since declared synonyms are done in declaration clause, mapped synonyms are all found within declaration clause
	// Hence, we create Declaration objects from the mapped synonyms
	for (std::pair<std::string, TokenType> synonym : mappedSynonyms) {
		std::string synonymValue = synonym.first;
		TokenType designEntity = synonym.second;

		Declaration declaration = *new Declaration(designEntity, synonymValue);
		declarations.push_back(declaration);
	}

	return declarations;
};

Select Parser::parseTokensIntoSelectObject(std::vector<TokenObject> selectTokens, std::unordered_map<std::string, TokenType> mappedSynonyms) {
	for (TokenObject token : selectTokens) {
		if (token.getTokenType() == TokenType::SELECT) {
			continue;
		}

		std::string returnValue = token.getValue();

		// Return empty Select object if return value is not declared for now
		if (mappedSynonyms.find(returnValue) == mappedSynonyms.end()) {
			return Select();
		}

		TokenType returnType = mappedSynonyms.at(returnValue);

		return Select(returnType, returnValue);

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
