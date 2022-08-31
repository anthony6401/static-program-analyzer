#include "DeclarationClauseSyntaxChecker.h"
#include <iostream>

using namespace qps;

DeclarationClauseSyntaxChecker::DeclarationClauseSyntaxChecker() {
	this->declarationSyntax.push(TokenType::SEMI_COLON);
	this->declarationSyntax.push(TokenType::SYNONYM);
	this->declarationSyntax.push(TokenType::DESIGN_ENTITY);
};

DeclarationClauseSyntaxChecker::~DeclarationClauseSyntaxChecker() {};

bool DeclarationClauseSyntaxChecker::isSyntacticallyCorrect(std::vector<TokenObject> tokenizedClause) {
	// Parser checks if there are any declaration.
	// If there are no declarations, mwthod will not be called
	
	for (int i = 0; i < tokenizedClause.size(); i++) {
		TokenObject token = tokenizedClause.at(i);
		TokenType tokenType = token.getTokenType();

		if (!this->declarationSyntax.empty()) {
			TokenType syntax = this->declarationSyntax.top();

			if (tokenType == TokenType::SEMI_COLON) {
				if (syntax != TokenType::SEMI_COLON) {
					return false;
				}

				// Multiple declarations, need to check syntax for other declarations
				if (i < tokenizedClause.size() - 1) {
					this->declarationSyntax.push(TokenType::SYNONYM);
					this->declarationSyntax.push(TokenType::DESIGN_ENTITY);
					continue;
				}

				this->declarationSyntax.pop();
				continue;
			}

			// Multiple synonyms for a single declaration type
			if (tokenType == TokenType::COMMA) {
				// Ensures that previous TokenType checked was SYNONYM since SYNONYM always
				// comes before SEMI_COLON
				if (syntax != TokenType::SEMI_COLON) {
					return false;
				}
				this->declarationSyntax.push(TokenType::SYNONYM);
				continue;
			}

			if (this->generalSyntax.find(syntax) == this->generalSyntax.end()) {
				if (tokenType != syntax) {
					return false;
				}
			}

			// Token is either DESIGN_ENTITY or SYNONYM
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

			this->declarationSyntax.pop();
			continue;
		}
	}

	if (!this->declarationSyntax.empty()) {
		return false;
	}

	return true;

};
