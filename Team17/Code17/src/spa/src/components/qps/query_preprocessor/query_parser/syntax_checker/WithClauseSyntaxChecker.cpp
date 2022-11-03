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

bool WithClauseSyntaxChecker::isSyntacticallyCorrect(std::vector<TokenObject> &tokenizedClause) {
	bool isSecondRef = false;
	
	for (int i = 0; i < tokenizedClause.size(); i++) {
		TokenObject &token = tokenizedClause.at(i);
		TokenType tokenType = token.getTokenType();

		if (isSecondRef) {
			if (tokenType == TokenType::AND) {
				this->withSyntax.push(TokenType::REF);
				this->withSyntax.push(TokenType::EQUALS);
				this->withSyntax.push(TokenType::REF);
				isSecondRef = false;
				continue;
			}

			if (tokenType == TokenType::WITH) {
				this->withSyntax.push(TokenType::REF);
				this->withSyntax.push(TokenType::EQUALS);
				this->withSyntax.push(TokenType::REF);
				this->withSyntax.push(TokenType::WITH);
				isSecondRef = false;
			}
		}

		if (this->withSyntax.empty()) {
			return false;
		}

		TokenType syntax = this->withSyntax.top();

		// SELECT or EQUALS token
		if (this->generalSyntax.find(syntax) == this->generalSyntax.end()) {
			if (tokenType != syntax) {
				return false;
			}

			if (tokenType == TokenType::EQUALS) {
				isSecondRef = true;
			}

			this->withSyntax.pop();
			continue;
		}

		// REF token
		std::vector<TokenType> &possibleTokenTypes = this->generalSyntax.at(syntax);
		bool foundToken = std::binary_search(possibleTokenTypes.begin(), possibleTokenTypes.end(), tokenType);

		if (!foundToken) {
			return false;
		}

		this->withSyntax.pop();

	}

	if (!this->withSyntax.empty()) {
		return false;
	}

	return true;

};
