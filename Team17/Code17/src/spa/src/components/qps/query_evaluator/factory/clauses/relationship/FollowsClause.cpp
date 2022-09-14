#include "FollowsClause.h"
#include "iostream"

FollowsClause::FollowsClause(TokenObject left, TokenObject right, Select synonym,
                             std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                             QPSClient qpsClient) : left(left), right(right), synonym(synonym),
                                                    synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {}

RawResult FollowsClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::NAME && rightType == TokenType::NAME) {
        return FollowsClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::NAME && rightType == TokenType::WILDCARD) {
        return FollowsClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::NAME && rightType == TokenType::INTEGER) {
        return FollowsClause::evaluateSynonymInteger();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::NAME) {
        return FollowsClause::evaluateIntegerSynonym();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::WILDCARD) {
        return FollowsClause::evaluateIntegerWildcard();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::INTEGER) {
        return FollowsClause::evaluateIntegerInteger();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::NAME) {
        return FollowsClause::evaluateWildcardSynonym();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::WILDCARD) {
        return FollowsClause::evaluateWildcardWildcard();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::INTEGER) {
        return FollowsClause::evaluateWildcardInteger();
    } else {
        return {};
    }
}

size_t FollowsClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

std::set<std::string> FollowsClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (left.getTokenType() == TokenType::SYNONYM) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::SYNONYM) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
}

TokenType FollowsClause::getRelationshipType() {
    return TokenType::FOLLOWS;
}

RawResult FollowsClause::evaluateSynonymSynonym() {
    return {};
}

RawResult FollowsClause::evaluateSynonymWildcard() {
    return {};
}

RawResult FollowsClause::evaluateSynonymInteger() {
    return {};
}

RawResult FollowsClause::evaluateIntegerSynonym() {
    return {};
}

RawResult FollowsClause::evaluateIntegerWildcard() {
    return {};
}

RawResult FollowsClause::evaluateIntegerInteger() {
    return {};
}

RawResult FollowsClause::evaluateWildcardSynonym() {
    return {};
}

RawResult FollowsClause::evaluateWildcardWildcard() {
    return {};
}

RawResult FollowsClause::evaluateWildcardInteger() {
    return {};
}


