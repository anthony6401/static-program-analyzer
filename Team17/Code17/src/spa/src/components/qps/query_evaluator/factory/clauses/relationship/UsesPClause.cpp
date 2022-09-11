#include "UsesPClause.h"

UsesPClause::UsesPClause(TokenObject left, TokenObject right, Select synonym,
                         std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient) :
        left(left), right(right), synonym(synonym),
        synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {};

RawResult UsesPClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::SYNONYM && rightType == TokenType::SYNONYM) {
        return UsesPClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::SYNONYM && rightType == TokenType::WILDCARD) {
        return UsesPClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::SYNONYM && rightType == TokenType::NAME_WITH_QUOTATION) {
        return UsesPClause::evaluateSynonymNameQuotes();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::SYNONYM) {
        return UsesPClause::evaluateNameQuotesSynonym();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::WILDCARD) {
        return UsesPClause::evaluateNameQuotesWildcard();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::NAME_WITH_QUOTATION) {
        return UsesPClause::evaluateNameQuotesNameQuotes();
    } else {
        return {};
    }
}

TokenType UsesPClause::getRelationshipType() {
    return TokenType::USES;
}

RawResult UsesPClause::evaluateSynonymSynonym() {
    return {};
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


