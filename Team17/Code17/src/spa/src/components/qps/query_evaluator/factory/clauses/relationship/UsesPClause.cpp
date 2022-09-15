#include "UsesPClause.h"
#include "iostream"

UsesPClause::UsesPClause(TokenObject left, TokenObject right, Select synonym,
                         std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient) :
        left(left), right(right), synonym(synonym),
        synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {};

RawResult UsesPClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::NAME && rightType == TokenType::NAME) {
        return UsesPClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::NAME && rightType == TokenType::WILDCARD) {
        return UsesPClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::NAME && rightType == TokenType::NAME_WITH_QUOTATION) {
        return UsesPClause::evaluateSynonymNameQuotes();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::NAME) {
        return UsesPClause::evaluateNameQuotesSynonym();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::WILDCARD) {
        return UsesPClause::evaluateNameQuotesWildcard();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::NAME_WITH_QUOTATION) {
        return UsesPClause::evaluateNameQuotesNameQuotes();
    } else {
        return {};
    }
}

size_t UsesPClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

std::set<std::string> UsesPClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (left.getTokenType() == TokenType::NAME) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::NAME) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
}

TokenType UsesPClause::getRelationshipType() {
    return TokenType::USES;
}

RawResult UsesPClause::evaluateSynonymSynonym() {
    std::cout << "----- UsesP: synonym synonym -------" << std::endl;
    return {"p", "v", {{"main", "x"}}};
}

RawResult UsesPClause::evaluateSynonymWildcard() {
    return {};
}

RawResult UsesPClause::evaluateSynonymNameQuotes() {
    return {};
}

RawResult UsesPClause::evaluateNameQuotesSynonym() {
    return {};
}

RawResult UsesPClause::evaluateNameQuotesWildcard() {
    return {};
}

RawResult UsesPClause::evaluateNameQuotesNameQuotes() {
    return {};
}


