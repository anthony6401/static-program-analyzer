#include "SuchThatClauseSyntaxChecker.h"

using namespace qps;

SuchThatClauseSyntaxChecker::SuchThatClauseSyntaxChecker() {
	this->suchThatSyntax.push(TokenType::RELREF);
	this->suchThatSyntax.push(TokenType::THAT);
	this->suchThatSyntax.push(TokenType::SUCH);
};

SuchThatClauseSyntaxChecker::~SuchThatClauseSyntaxChecker() {};

bool SuchThatClauseSyntaxChecker::isSyntacticallyCorrect(std::vector<TokenObject> &tokenizedClause) {
	int index = 0;
	bool isPrevTokenRelref = false;

	while (index < tokenizedClause.size()) {
		TokenObject &token = tokenizedClause.at(index);
		TokenType tokenType = token.getTokenType();

		if (isPrevTokenRelref) {
			if (tokenType == TokenType::AND) {
				this->suchThatSyntax.push(TokenType::RELREF);
				isPrevTokenRelref = false;
				index++;
				continue;
			}

			if (tokenType == TokenType::SUCH) {
				this->suchThatSyntax.push(TokenType::RELREF);
				this->suchThatSyntax.push(TokenType::THAT);
				this->suchThatSyntax.push(TokenType::SUCH);
				isPrevTokenRelref = false;
			}
		}

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
			index++;
			continue;
		}

		// Checking for RELREF syntax
		std::vector<TokenType> &possibleTokenTypes = this->generalSyntax.at(syntax);
		bool foundToken = std::binary_search(possibleTokenTypes.begin(), possibleTokenTypes.end(), tokenType);

		if (!foundToken) {
			return false;
		}

		this->suchThatSyntax.pop();

		// Extract relationship tokens starting from token after the RELREF token
		auto [closedBracketIndex, relationshipClauseTokens] = getRelationshipClauseTokens(tokenizedClause, index);
		bool hasValidSyntax = isRelationshipSyntacticallyCorrect(relationshipClauseTokens, tokenType);
		
		if (!hasValidSyntax) {
			return false;
		}

		isPrevTokenRelref = true;
		index = closedBracketIndex + 1;
	}

	if (!this->suchThatSyntax.empty()) {
		return false;
	}

	return true;
};

std::tuple<int, std::vector<TokenObject>> SuchThatClauseSyntaxChecker::getRelationshipClauseTokens(std::vector<TokenObject> &tokenizedClause, int relrefIndex) {
	auto closedBracketTokenIterator = std::find(tokenizedClause.begin() + relrefIndex + 1, tokenizedClause.end(), TokenObject(TokenType::CLOSED_BRACKET, ")"));

	if (closedBracketTokenIterator == tokenizedClause.end()) {
		return {};
	}

	int closedBracketTokenIndex = closedBracketTokenIterator - tokenizedClause.begin();
	std::vector<TokenObject> relationshipClauseTokens(tokenizedClause.begin() + relrefIndex + 1, closedBracketTokenIterator + 1);

	return { closedBracketTokenIndex, relationshipClauseTokens };

}

bool SuchThatClauseSyntaxChecker::isRelationshipSyntacticallyCorrect(std::vector<TokenObject> &relationshipClauseTokens, TokenType relrefToken) {
	if (relationshipClauseTokens.empty()) {
		return false;
	}

	bool hasValidSyntax = false;

	if (relrefToken == TokenType::USES || relrefToken == TokenType::MODIFIES) {
		hasValidSyntax = hasValidUsesModifiesSyntax(relationshipClauseTokens);
	} else if (relrefToken == TokenType::CALLS || relrefToken == TokenType::CALLS_T) {
		hasEntrefEntrefSyntax();
		hasValidSyntax = hasValidRelationshipSyntax(relationshipClauseTokens);
	} else {
		hasStmtrefStmtrefSyntax();
		hasValidSyntax = hasValidRelationshipSyntax(relationshipClauseTokens);
	}

	return hasValidSyntax;
}

bool SuchThatClauseSyntaxChecker::hasValidRelationshipSyntax(std::vector<TokenObject> &relationshipClauseTokens) {
	for (int i = 0; i < relationshipClauseTokens.size(); i++) {
		TokenObject &token = relationshipClauseTokens.at(i);
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

		// STMTREF or ENTREF
		std::vector<TokenType> &possibleTokenTypes = this->generalSyntax.at(syntax);
		bool foundToken = std::binary_search(possibleTokenTypes.begin(), possibleTokenTypes.end(), tokenType);

		if (!foundToken && !isSynonymToken(tokenType)) {
			return false;
		}
		this->suchThatSyntax.pop();
	}

	return true;
}


bool SuchThatClauseSyntaxChecker::hasValidUsesModifiesSyntax(std::vector<TokenObject> &relationshipClauseTokens) {
	this->suchThatSyntax.push(TokenType::CLOSED_BRACKET);
	this->suchThatSyntax.push(TokenType::ENTREF);
	this->suchThatSyntax.push(TokenType::COMMA);
	this->suchThatSyntax.push(TokenType::ENTREF);
	this->suchThatSyntax.push(TokenType::OPEN_BRACKET);

	bool isFirstParameter = true;

	for (int i = 0; i < relationshipClauseTokens.size(); i++) {
		TokenObject &token = relationshipClauseTokens.at(i);
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
		std::vector<TokenType> &possibleTokenTypes = this->generalSyntax.at(syntax);
		bool foundToken = std::binary_search(possibleTokenTypes.begin(), possibleTokenTypes.end(), tokenType);

		// Check if token is SYNONYM
		if (!foundToken) {
			foundToken = isSynonymToken(tokenType);
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

bool SuchThatClauseSyntaxChecker::isSynonymToken(TokenType tokenType) {
	std::vector<TokenType> synonymTokens = this->generalSyntax.at(TokenType::SYNONYM);
	bool foundToken = std::binary_search(synonymTokens.begin(), synonymTokens.end(), tokenType);

	return foundToken;
}

void SuchThatClauseSyntaxChecker::hasEntrefEntrefSyntax() {
	this->suchThatSyntax.push(TokenType::CLOSED_BRACKET);
	this->suchThatSyntax.push(TokenType::ENTREF);
	this->suchThatSyntax.push(TokenType::COMMA);
	this->suchThatSyntax.push(TokenType::ENTREF);
	this->suchThatSyntax.push(TokenType::OPEN_BRACKET);
}

void SuchThatClauseSyntaxChecker::hasStmtrefStmtrefSyntax() {
	this->suchThatSyntax.push(TokenType::CLOSED_BRACKET);
	this->suchThatSyntax.push(TokenType::STMTREF);
	this->suchThatSyntax.push(TokenType::COMMA);
	this->suchThatSyntax.push(TokenType::STMTREF);
	this->suchThatSyntax.push(TokenType::OPEN_BRACKET);
}
