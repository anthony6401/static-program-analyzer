#include "ParentTClause.h"

ParentTClause::ParentTClause(TokenObject left, TokenObject right, Select synonym,
                               std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                               QPSClient qpsClient) : left(left), right(right), synonym(synonym),
                                                      synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {}

RawResult ParentTClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::SYNONYM && rightType == TokenType::SYNONYM) {
        return ParentTClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::SYNONYM && rightType == TokenType::WILDCARD) {
        return ParentTClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::SYNONYM && rightType == TokenType::INTEGER) {
        return ParentTClause::evaluateSynonymInteger();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::SYNONYM) {
        return ParentTClause::evaluateIntegerSynonym();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::WILDCARD) {
        return ParentTClause::evaluateIntegerWildcard();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::INTEGER) {
        return ParentTClause::evaluateIntegerInteger();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::SYNONYM) {
        return ParentTClause::evaluateWildcardSynonym();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::WILDCARD) {
        return ParentTClause::evaluateWildcardWildcard();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::INTEGER) {
        return ParentTClause::evaluateWildcardInteger();
    } else {
        return {};
    }
}

size_t ParentTClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::SYNONYM) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::SYNONYM) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

TokenType getRelationshipType() {
    return TokenType::PARENT_T;
}

RawResult ParentTClause::evaluateSynonymSynonym() {
    return {};
}

RawResult ParentTClause::evaluateSynonymWildcard() {
    return {};
}

RawResult ParentTClause::evaluateSynonymInteger() {
    return {};
}

RawResult ParentTClause::evaluateIntegerSynonym() {
    return {};
}

RawResult ParentTClause::evaluateIntegerWildcard() {
    return {};
}

RawResult ParentTClause::evaluateIntegerInteger() {
    return {};
}

RawResult ParentTClause::evaluateWildcardSynonym() {
    return {};
}

RawResult ParentTClause::evaluateWildcardWildcard() {
    return {};
}

RawResult ParentTClause::evaluateWildcardInteger() {
    return {};
}