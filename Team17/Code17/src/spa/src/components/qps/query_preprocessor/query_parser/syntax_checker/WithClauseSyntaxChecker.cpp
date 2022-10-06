#include "WithClauseSyntaxChecker.h"
#include <iostream>

using namespace qps;

WithClauseSyntaxChecker::WithClauseSyntaxChecker() {
	this->withSyntax.push(TokenType::REF);
	this->withSyntax.push(TokenType::EQUALS);
	this->withSyntax.push(TokenType::REF);
	this->withSyntax.push(TokenType::WITH);
};

WithClauseSyntaxChecker::~WithClauseSyntaxChecker() {};

bool WithClauseSyntaxChecker::isSyntacticallyCorrect(std::vector<TokenObject> tokenizedClause) {
	for (int i = 0; i < tokenizedClause.size(); i++) {
		TokenObject token = tokenizedClause.at(i);
		TokenType tokenType = token.getTokenType();

		if (this->withSyntax.empty()) {
			// Multiple instances of with clause
			if (tokenType == TokenType::AND) {
				this->withSyntax.push(TokenType::REF);
				this->withSyntax.push(TokenType::EQUALS);
				this->withSyntax.push(TokenType::REF);
				continue;
			}

			return false;
		}

		TokenType syntax = this->withSyntax.top();

		// SELECT or EQUALS token
		if (this->generalSyntax.find(syntax) == this->generalSyntax.end()) {
			if (tokenType != syntax) {
				return false;
			}
		}

		// REF token
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

		this->withSyntax.pop();
		continue;

	}

	if (!this->withSyntax.empty()) {
		return false;
	}

	return true;

};
