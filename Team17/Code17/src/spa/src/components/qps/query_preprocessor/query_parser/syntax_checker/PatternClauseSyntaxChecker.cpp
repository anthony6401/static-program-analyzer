#include "PatternClauseSyntaxChecker.h"
#include <iostream>

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

		// PATTERN, BRACKET, COMMA tokens
		if (this->generalSyntax.find(syntax) == this->generalSyntax.end()) {
			if (tokenType != syntax) {
				return false;
			}

			if (tokenType == TokenType::CLOSED_BRACKET) {
				isPrevTokenClosedBracket = true;
			}

			this->patternSyntax.pop();
			continue;
		}

		// ENTREF
		if (syntax == TokenType::ENTREF) {
			std::vector<TokenType> possibleTokenTypes = this->generalSyntax.at(syntax);
			bool foundToken = false;
			for (int j = 0; j < possibleTokenTypes.size(); j++) {
				TokenType possibleTokenType = possibleTokenTypes.at(j);

				if (tokenType == possibleTokenType) {
					foundToken = true;
					break;
				}

				if (possibleTokenType != TokenType::SYNONYM) {
					continue;
				}

				// Check if ENTREF is SYNONYM
				std::vector<TokenType> synonymTokens = this->generalSyntax.at(TokenType::SYNONYM);
				for (int k = 0; k < synonymTokens.size(); k++) {
					TokenType synonymToken = synonymTokens.at(k);

					if (tokenType == synonymToken) {
						foundToken = true;
						break;
					}
				}
			}

			if (!foundToken) {
				return false;
			}

			this->patternSyntax.pop();
			continue;

		}
		

		// SYNONYM, EXPRESSION_SPEC token
		std::vector<TokenType> possibleTokenTypes = this->generalSyntax.at(syntax);
		bool foundToken = false;
		for (int j = 0; j < possibleTokenTypes.size(); j++) {
			TokenType possibleTokenType = possibleTokenTypes.at(j);

			if (tokenType == possibleTokenType) {
				foundToken = true;
				break;
			}
		}

		if (!foundToken) {
			return false;
		}

		this->patternSyntax.pop();

	}

	if (!this->patternSyntax.empty()) {
		return false;
	}

	return true;

};
