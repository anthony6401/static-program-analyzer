#include "FollowsTClause.h"

FollowsTClause::FollowsTClause(TokenObject left, TokenObject right, Select synonym,
                             std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                             QPSClient qpsClient) : left(left), right(right), synonym(synonym),
                                                    synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {}

RawResult FollowsTClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::SYNONYM && rightType == TokenType::SYNONYM) {
        return FollowsTClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::SYNONYM && rightType == TokenType::WILDCARD) {
        return FollowsTClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::SYNONYM && rightType == TokenType::INTEGER) {
        return FollowsTClause::evaluateSynonymInteger();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::SYNONYM) {
        return FollowsTClause::evaluateIntegerSynonym();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::WILDCARD) {
        return FollowsTClause::evaluateIntegerWildcard();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::INTEGER) {
        return FollowsTClause::evaluateIntegerInteger();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::SYNONYM) {
        return FollowsTClause::evaluateWildcardSynonym();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::WILDCARD) {
        return FollowsTClause::evaluateWildcardWildcard();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::INTEGER) {
        return FollowsTClause::evaluateWildcardInteger();
    } else {
        return {};
    }
}

size_t FollowsTClause::getNumberOfSynonyms() {
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
    return TokenType::FOLLOWS_T;
}

RawResult FollowsTClause::evaluateSynonymSynonym() {
    return {};
}

RawResult FollowsTClause::evaluateSynonymWildcard() {
    return {};
}

RawResult FollowsTClause::evaluateSynonymInteger() {
    return {};
}

RawResult FollowsTClause::evaluateIntegerSynonym() {
    return {};
}

RawResult FollowsTClause::evaluateIntegerWildcard() {
    return {};
}

RawResult FollowsTClause::evaluateIntegerInteger() {
    return {};
}

RawResult FollowsTClause::evaluateWildcardSynonym() {
    return {};
}

RawResult FollowsTClause::evaluateWildcardWildcard() {
    return {};
}

RawResult FollowsTClause::evaluateWildcardInteger() {
    return {};
}