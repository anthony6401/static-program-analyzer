#include "SelectClauseSyntaxChecker.h"

using namespace qps;

SelectClauseSyntaxChecker::SelectClauseSyntaxChecker() {
	this->selectSyntax.push(TokenType::RESULT_CL);
	this->selectSyntax.push(TokenType::SELECT);
};

SelectClauseSyntaxChecker::~SelectClauseSyntaxChecker() {};

bool SelectClauseSyntaxChecker::isSyntacticallyCorrect(std::vector<TokenObject> tokenizedClause) {
	for (int i = 0; i < tokenizedClause.size(); i++) {
		TokenObject token = tokenizedClause.at(i);
		TokenType tokenType = token.getTokenType();

		if (this->selectSyntax.empty()) {
			return false;
		}

		TokenType syntax = this->selectSyntax.top();

		// SELECT token
		if (this->generalSyntax.find(syntax) == this->generalSyntax.end()) {
			if (tokenType != syntax) {
				return false;
			}

			this->selectSyntax.pop();
			continue;
		}

		// RESULT_CL token
		std::vector<TokenType> possibleTokenTypes = this->generalSyntax.at(syntax);
		bool foundToken = false;
		for (int j = 0; j < possibleTokenTypes.size(); j++) {
			TokenType possibleTokenType = possibleTokenTypes.at(j);

			if (tokenType == possibleTokenType) {
				foundToken = true;
				break;
			}

			if (possibleTokenType == TokenType::SYNONYM) {
				foundToken = isSynonymToken(tokenType);
			}
		}

		if (!foundToken) {
			return false;
		}

		this->selectSyntax.pop();
		continue;

	}

	if (!this->selectSyntax.empty()) {
		return false;
	}

	return true;

};

bool SelectClauseSyntaxChecker::isSynonymToken(TokenType tokenType) {
	std::vector<TokenType> synonymTokens = this->generalSyntax.at(TokenType::SYNONYM);
	for (int k = 0; k < synonymTokens.size(); k++) {
		TokenType synonymToken = synonymTokens.at(k);

		if (tokenType == synonymToken) {
			return true;
		}
	}

	return false;
}
