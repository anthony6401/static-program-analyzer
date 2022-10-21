#include "FollowsClause.h"
#include <utility>
#include "components/qps/query_evaluator/factory/utils/ClauseUtils.h"

FollowsClause::FollowsClause(TokenObject left, TokenObject right,
                             std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                             QPSClient qpsClient) : left(std::move(left)), right(std::move(right)),
                                                    synonymToDesignEntityMap(std::move(synonymToDesignEntityMap)), qpsClient(qpsClient) {}

ResultTable FollowsClause::evaluateClause() {
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
    } else {
        return FollowsClause::evaluateWildcardInteger();
    }
}

size_t FollowsClause::getPriority() {
    return priority;
}

std::set<std::string> FollowsClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (left.getTokenType() == TokenType::NAME) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::NAME) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
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

ResultTable FollowsClause::evaluateSynonymSynonym() {
    std::string leftValue = left.getValue();
    std::string rightValue = right.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    if (leftValue == rightValue) {
        return {false};
    }
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::FOLLOWS, leftType, rightType);
    std::vector<std::pair<std::string, std::string>> processedMap = ClauseUtils::processMapToVectorPair(results);
    return {leftValue, rightValue, processedMap};
}

ResultTable FollowsClause::evaluateSynonymWildcard() {
    std::string leftValue = left.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    DesignEntity rightType = DesignEntity::STMT;
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::FOLLOWS, leftType, rightType);
    std::unordered_set<std::string> processedMap = ClauseUtils::processMapToSetFromFirst(results);
    return {leftValue, processedMap};
}

ResultTable FollowsClause::evaluateSynonymInteger() {
    std::string leftValue = left.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(RelationshipType::FOLLOWS, leftType, right);
    return {leftValue, results};
}

ResultTable FollowsClause::evaluateIntegerSynonym() {
    std::string rightValue = right.getValue();
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(RelationshipType::FOLLOWS, left, rightType);
    return {rightValue, results};
}

ResultTable FollowsClause::evaluateIntegerWildcard() {
    DesignEntity rightType = DesignEntity::STMT;
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(RelationshipType::FOLLOWS, left, rightType);
    bool result = !results.empty();
    return {result};
}

ResultTable FollowsClause::evaluateIntegerInteger() {
    bool result = qpsClient.getRelationship(RelationshipType::FOLLOWS, left, right);
    return {result};
}

ResultTable FollowsClause::evaluateWildcardSynonym() {
    DesignEntity leftType = DesignEntity::STMT;
    std::string rightValue = right.getValue();
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::FOLLOWS, leftType, rightType);
    std::unordered_set<std::string> processedMap = ClauseUtils::processMapToSetFromSecond(results);
    return {rightValue, processedMap};
}

ResultTable FollowsClause::evaluateWildcardWildcard() {
    DesignEntity stmtType = DesignEntity::STMT;
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::FOLLOWS, stmtType, stmtType);
    bool result = !results.empty();
    return {result};
}

ResultTable FollowsClause::evaluateWildcardInteger() {
    DesignEntity leftType = DesignEntity::STMT;
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(RelationshipType::FOLLOWS, leftType, right);
    bool result = !results.empty();
    return {result};
}


