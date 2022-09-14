#include "FollowsTClause.h"
#include "iostream"

FollowsTClause::FollowsTClause(TokenObject left, TokenObject right, Select synonym,
                             std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                             QPSClient qpsClient) : left(left), right(right), synonym(synonym),
                                                    synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {}

RawResult FollowsTClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::NAME && rightType == TokenType::NAME) {
        return FollowsTClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::NAME && rightType == TokenType::WILDCARD) {
        return FollowsTClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::NAME && rightType == TokenType::INTEGER) {
        return FollowsTClause::evaluateSynonymInteger();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::NAME) {
        return FollowsTClause::evaluateIntegerSynonym();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::WILDCARD) {
        return FollowsTClause::evaluateIntegerWildcard();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::INTEGER) {
        return FollowsTClause::evaluateIntegerInteger();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::NAME) {
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
    if (left.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

std::set<std::string> FollowsTClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (left.getTokenType() == TokenType::NAME) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::NAME) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
}

TokenType FollowsTClause::getRelationshipType() {
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
    std::cout << "----- Follows*: integer synonym -------" << std::endl;
    return {"v", {}};
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