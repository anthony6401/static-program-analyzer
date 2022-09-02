#include"Parser.h"
#include<stdexcept>

using namespace qps;

Parser::Parser(std::vector<TokenObject> tokenizedQuery) {
	this->tokenizedQuery = tokenizedQuery;
};

std::string Parser::parse() {
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
		return "SyntaxError";
	}

	return "";
};

std::vector<std::vector<TokenObject>> Parser::groupQueryIntoClause() {
	std::vector<TokenObject> declarationTokenObjects;
	std::vector<TokenObject> selectTokenObjects;
	std::vector<TokenObject> relationshipTokenObjects;
	std::vector<TokenObject> patternTokenObjects;

	// Get vector of token types of objects
	std::vector<TokenType> tokenTypes = getTokenTypes();
	
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

std::vector<TokenType> Parser::getTokenTypes() {
	std::vector<TokenType> tokenTypes;
	
	for (TokenObject token: this->tokenizedQuery) {
		tokenTypes.push_back(token.getTokenType());
	}

	return tokenTypes;
};

std::vector<TokenObject> Parser::getTokenizedQuery() {
	return this->tokenizedQuery;
}
