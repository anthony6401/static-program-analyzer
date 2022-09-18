#include "SuchThatClauseSyntaxChecker.h"
#include <iostream>

using namespace qps;

SuchThatClauseSyntaxChecker::SuchThatClauseSyntaxChecker() {
	this->suchThatSyntax.push(TokenType::RELREF);
	this->suchThatSyntax.push(TokenType::THAT);
	this->suchThatSyntax.push(TokenType::SUCH);
};

SuchThatClauseSyntaxChecker::~SuchThatClauseSyntaxChecker() {};

bool SuchThatClauseSyntaxChecker::isSyntacticallyCorrect(std::vector<TokenObject> tokenizedClause) {
	for (int i = 0; i < tokenizedClause.size(); i++) {
		TokenObject token = tokenizedClause.at(i);
		TokenType tokenType = token.getTokenType();

		if (this->suchThatSyntax.empty()) {
			return false;
		}

		TokenType syntax = this->suchThatSyntax.top();

		// SUCH, THAT
		if (this->generalSyntax.find(syntax) == this->generalSyntax.end()) {
			if (tokenType != syntax) {
				return false;
			}

			this->suchThatSyntax.pop();
			continue;
		}


		// Checking for RELREF syntax
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

		this->suchThatSyntax.pop();

		// Extract relationship tokens starting from token after the RELREF token
		std::vector<TokenObject> relationshipClauseTokens(tokenizedClause.begin() + i + 1, tokenizedClause.end());
		
		if (relationshipClauseTokens.empty()) {
			std::cout << "no relationship";
			return false;
		}

		if (tokenType == TokenType::FOLLOWS || tokenType == TokenType::FOLLOWS_T ||
			tokenType == TokenType::PARENT || tokenType == TokenType::PARENT_T) {
			bool hasValidSyntax = hasValidFollowsParentSyntax(relationshipClauseTokens);

			if (!hasValidSyntax) {
				return false;
			}
		}
		else {
			bool hasValidSyntax = hasValidUsersModifiesSyntax(relationshipClauseTokens);
			if (!hasValidSyntax) {
				return false;
			}
		}

		break;

	}

	if (!this->suchThatSyntax.empty()) {
		return false;
	}

	return true;
};

bool SuchThatClauseSyntaxChecker::hasValidFollowsParentSyntax(std::vector<TokenObject> relationshipClauseTokens) {
	this->suchThatSyntax.push(TokenType::CLOSED_BRACKET);
	this->suchThatSyntax.push(TokenType::STMTREF);
	this->suchThatSyntax.push(TokenType::COMMA);
	this->suchThatSyntax.push(TokenType::STMTREF);
	this->suchThatSyntax.push(TokenType::OPEN_BRACKET);

	for (int i = 0; i < relationshipClauseTokens.size(); i++) {
		TokenObject token = relationshipClauseTokens.at(i);
		TokenType tokenType = token.getTokenType();

		if (this->suchThatSyntax.empty()) {
			return false;
		}

		TokenType syntax = this->suchThatSyntax.top();

		if (this->generalSyntax.find(syntax) == this->generalSyntax.end()) {
			if (tokenType != syntax) {
				return false;
			}

			this->suchThatSyntax.pop();
			continue;
		}

		// STMTREF
		std::vector<TokenType> possibleTokenTypes = this->generalSyntax.at(syntax);
		bool foundToken = false;
		for (int j = 0; j < possibleTokenTypes.size(); j++) {
			TokenType possibleTokenType = possibleTokenTypes.at(j);

			if (tokenType == possibleTokenType) {
				foundToken = true;
				break;
			}

			if (possibleTokenType == TokenType::SYNONYM) {
				std::vector<TokenType> synonymTokens = this->generalSyntax.at(TokenType::SYNONYM);
				for (int k = 0; k < synonymTokens.size(); k++) {
					TokenType synonymToken = synonymTokens.at(k);

					if (tokenType == synonymToken) {
						foundToken = true;
						break;
					}
				}
			}
		}

		if (!foundToken) {
			return false;
		}
		this->suchThatSyntax.pop();
	}

	return true;
}


bool SuchThatClauseSyntaxChecker::hasValidUsersModifiesSyntax(std::vector<TokenObject> relationshipClauseTokens) {
	this->suchThatSyntax.push(TokenType::CLOSED_BRACKET);
	this->suchThatSyntax.push(TokenType::ENTREF);
	this->suchThatSyntax.push(TokenType::COMMA);
	this->suchThatSyntax.push(TokenType::ENTREF);
	this->suchThatSyntax.push(TokenType::OPEN_BRACKET);

	bool isFirstParameter = true;

	for (int i = 0; i < relationshipClauseTokens.size(); i++) {
		TokenObject token = relationshipClauseTokens.at(i);
		TokenType tokenType = token.getTokenType();

		if (this->suchThatSyntax.empty()) {
			return false;
		}

		TokenType syntax = this->suchThatSyntax.top();

		// BRACKETS, COMMA
		if (this->generalSyntax.find(syntax) == this->generalSyntax.end()) {
			if (tokenType != syntax) {
				return false;
			}

			this->suchThatSyntax.pop();
			continue;
		}

		// ENTREF
		std::vector<TokenType> possibleTokenTypes = this->generalSyntax.at(syntax);
		bool foundToken = false;
		for (int j = 0; j < possibleTokenTypes.size(); j++) {
			TokenType possibleTokenType = possibleTokenTypes.at(j);

			if (tokenType == possibleTokenType) {
				foundToken = true;
				break;
			}

			if (possibleTokenType == TokenType::SYNONYM) {
				std::vector<TokenType> synonymTokens = this->generalSyntax.at(TokenType::SYNONYM);
				for (int k = 0; k < synonymTokens.size(); k++) {
					TokenType synonymToken = synonymTokens.at(k);

					if (tokenType == synonymToken) {
						foundToken = true;
						break;
					}
				}
			}
		}

		// If token is not ENTREF, check if token is STMTREF only if it is the first parameter token
		// Only check INTEGER token since it is the only difference between STMTREF and ENTREF
		if (!foundToken && isFirstParameter) {
			if ((tokenType != TokenType::INTEGER)) {
				return false;
			}

			foundToken = true;
		}

		if (!foundToken) {
			return false;
		}

		this->suchThatSyntax.pop();
		isFirstParameter = false;


	}

	return true;
}
