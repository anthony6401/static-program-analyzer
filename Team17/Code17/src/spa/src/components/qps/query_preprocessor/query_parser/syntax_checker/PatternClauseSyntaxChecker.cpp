#include "PatternClauseSyntaxChecker.h"

using namespace qps;

PatternClauseSyntaxChecker::PatternClauseSyntaxChecker() {
	this->patternSyntax.push(TokenType::CLOSED_BRACKET);
	this->patternSyntax.push(TokenType::EXPRESSION_SPEC);
	this->patternSyntax.push(TokenType::COMMA);
	this->patternSyntax.push(TokenType::ENTREF);
	this->patternSyntax.push(TokenType::OPEN_BRACKET);
	this->patternSyntax.push(TokenType::SYNONYM);
	this->patternSyntax.push(TokenType::PATTERN);

};

PatternClauseSyntaxChecker::~PatternClauseSyntaxChecker() {};

bool PatternClauseSyntaxChecker::isSyntacticallyCorrect(std::vector<TokenObject> tokenizedClause) {
	bool isPrevTokenClosedBracket = false;
	bool isSecondParam = false;
	bool isSecondParamWildcard = false;
	
	for (int i = 0; i < tokenizedClause.size(); i++) {
		TokenObject token = tokenizedClause.at(i);
		TokenType tokenType = token.getTokenType();

		if (isPrevTokenClosedBracket) {
			if (tokenType == TokenType::AND || tokenType == TokenType::PATTERN) {
				this->patternSyntax.push(TokenType::CLOSED_BRACKET);
				this->patternSyntax.push(TokenType::EXPRESSION_SPEC);
				this->patternSyntax.push(TokenType::COMMA);
				this->patternSyntax.push(TokenType::ENTREF);
				this->patternSyntax.push(TokenType::OPEN_BRACKET);
				this->patternSyntax.push(TokenType::SYNONYM);
				isPrevTokenClosedBracket = false;
				continue;
			}
		}

		if (this->patternSyntax.empty()) {
			return false;
		}

		TokenType syntax = this->patternSyntax.top();

		if (syntax == TokenType::CLOSED_BRACKET) {
			// if pattern
			if (tokenType == TokenType::COMMA && isSecondParamWildcard) {
				this->patternSyntax.push(TokenType::WILDCARD);
				continue;
			}

			if (tokenType != syntax) {
				return false;
			}

			isPrevTokenClosedBracket = true;
			this->patternSyntax.pop();
			continue;
		}

		// PATTERN, BRACKET, COMMA tokens
		if (this->generalSyntax.find(syntax) == this->generalSyntax.end()) {
			if (tokenType != syntax) {
				return false;
			}

			this->patternSyntax.pop();
			continue;
		}

		// ENTREF
		if (syntax == TokenType::ENTREF) {
			bool foundToken = isEntrefToken(tokenType);

			if (!foundToken) {
				return false;
			}

			isSecondParam = true;
			this->patternSyntax.pop();
			continue;

		}

		// SYNONYM, EXPRESSION_SPEC token
		std::vector<TokenType> possibleTokenTypes = this->generalSyntax.at(syntax);
		bool foundToken = std::binary_search(possibleTokenTypes.begin(), possibleTokenTypes.end(), tokenType);

		if (!foundToken) {
			return false;
		}

		// Ensure second parameter of if pattern is wildcard
		if (tokenType == TokenType::WILDCARD && isSecondParam) {
			isSecondParamWildcard = true;
		}

		this->patternSyntax.pop();

	}

	if (!this->patternSyntax.empty()) {
		return false;
	}

	return true;

};

bool PatternClauseSyntaxChecker::isEntrefToken(TokenType tokenType) {
	std::vector<TokenType> possibleTokenTypes = this->generalSyntax.at(TokenType::ENTREF);
	for (int j = 0; j < possibleTokenTypes.size(); j++) {
		TokenType possibleTokenType = possibleTokenTypes.at(j);

		if (tokenType == possibleTokenType) {
			return true;
		}

		if (possibleTokenType != TokenType::SYNONYM) {
			continue;
		}

		// Check if ENTREF is SYNONYM
		std::vector<TokenType> synonymTokens = this->generalSyntax.at(TokenType::SYNONYM);
		for (int k = 0; k < synonymTokens.size(); k++) {
			TokenType synonymToken = synonymTokens.at(k);

			if (tokenType == synonymToken) {
				return true;
			}
		}
	}

	return false;
}


