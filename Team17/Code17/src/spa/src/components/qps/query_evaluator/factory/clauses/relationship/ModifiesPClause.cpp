#include "ModifiesPClause.h"

ModifiesPClause::ModifiesPClause(TokenObject left, TokenObject right, Select synonym,
                                 std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                                 QPSClient qpsClient) : left(left), right(right), synonym(synonym),
                                                        synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {};

RawResult ModifiesPClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::SYNONYM && rightType == TokenType::SYNONYM) {
        return ModifiesPClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::SYNONYM && rightType == TokenType::WILDCARD) {
        return ModifiesPClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::SYNONYM && rightType == TokenType::NAME_WITH_QUOTATION) {
        return ModifiesPClause::evaluateSynonymNameQuotes();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::SYNONYM) {
        return ModifiesPClause::evaluateNameQuotesSynonym();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::WILDCARD) {
        return ModifiesPClause::evaluateNameQuotesWildcard();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::NAME_WITH_QUOTATION) {
        return ModifiesPClause::evaluateNameQuotesNameQuotes();
    } else {
        return {};
    }
}

size_t ModifiesPClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::SYNONYM) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::SYNONYM) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

TokenType ModifiesPClause::getRelationshipType() {
    return TokenType::MODIFIES;
}

RawResult ModifiesPClause::evaluateSynonymSynonym() {
    return {};
}

RawResult ModifiesPClause::evaluateSynonymWildcard() {
    return {};
}

RawResult ModifiesPClause::evaluateSynonymNameQuotes() {
    return {};
}

RawResult ModifiesPClause::evaluateNameQuotesSynonym() {
    return {};
}

RawResult ModifiesPClause::evaluateNameQuotesWildcard() {
    return {};
}

RawResult ModifiesPClause::evaluateNameQuotesNameQuotes() {
    return {};
}

