#include "ParentClause.h"

ParentClause::ParentClause(TokenObject left, TokenObject right, Select synonym,
                             std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                             QPSClient qpsClient) : left(left), right(right), synonym(synonym),
                                                    synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {}

RawResult ParentClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::SYNONYM && rightType == TokenType::SYNONYM) {
        return ParentClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::SYNONYM && rightType == TokenType::WILDCARD) {
        return ParentClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::SYNONYM && rightType == TokenType::INTEGER) {
        return ParentClause::evaluateSynonymInteger();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::SYNONYM) {
        return ParentClause::evaluateIntegerSynonym();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::WILDCARD) {
        return ParentClause::evaluateIntegerWildcard();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::INTEGER) {
        return ParentClause::evaluateIntegerInteger();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::SYNONYM) {
        return ParentClause::evaluateWildcardSynonym();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::WILDCARD) {
        return ParentClause::evaluateWildcardWildcard();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::INTEGER) {
        return ParentClause::evaluateWildcardInteger();
    } else {
        return {};
    }
}

TokenType getRelationshipType() {
    return TokenType::PARENT;
}

RawResult ParentClause::evaluateSynonymSynonym() {
    return {};
}

RawResult ParentClause::evaluateSynonymWildcard() {
    return {};
}

RawResult ParentClause::evaluateSynonymInteger() {
    return {};
}

RawResult ParentClause::evaluateIntegerSynonym() {
    return {};
}

RawResult ParentClause::evaluateIntegerWildcard() {
    return {};
}

RawResult ParentClause::evaluateIntegerInteger() {
    return {};
}

RawResult ParentClause::evaluateWildcardSynonym() {
    return {};
}

RawResult ParentClause::evaluateWildcardWildcard() {
    return {};
}

RawResult ParentClause::evaluateWildcardInteger() {
    return {};
}


