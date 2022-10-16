#include "FollowsTClause.h"
#include <utility>
#include "components/qps/query_evaluator/factory/utils/ClauseUtils.h"

FollowsTClause::FollowsTClause(TokenObject left, TokenObject right,
                             std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                             QPSClient qpsClient) : left(std::move(left)), right(std::move(right)),
                                                    synonymToDesignEntityMap(std::move(synonymToDesignEntityMap)), qpsClient(qpsClient) {}

ResultTable FollowsTClause::evaluateClause() {
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
    } else {
        return FollowsTClause::evaluateWildcardInteger();
    }
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

ResultTable FollowsTClause::evaluateSynonymSynonym() {
    std::string leftValue = left.getValue();
    std::string rightValue = right.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    if (leftValue == rightValue) {
        return {false};
    }
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::FOLLOWS_T, leftType, rightType);
    std::vector<std::pair<std::string, std::string>> processedMap = ClauseUtils::processMapToVectorPair(results);
    return {leftValue, rightValue, processedMap};
}

ResultTable FollowsTClause::evaluateSynonymWildcard() {
    std::string leftValue = left.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    DesignEntity rightType = DesignEntity::STMT;
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::FOLLOWS_T, leftType, rightType);
    std::unordered_set<std::string> processedMap = ClauseUtils::processMapToSetFromFirst(results);
    return {leftValue, processedMap};
}

ResultTable FollowsTClause::evaluateSynonymInteger() {
    std::string leftValue = left.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(RelationshipType::FOLLOWS_T, leftType, right);
    return {leftValue, results};
}

ResultTable FollowsTClause::evaluateIntegerSynonym() {
    std::string rightValue = right.getValue();
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(RelationshipType::FOLLOWS_T, left, rightType);
    return {rightValue, results};
}

ResultTable FollowsTClause::evaluateIntegerWildcard() {
    DesignEntity rightType = DesignEntity::STMT;
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(RelationshipType::FOLLOWS_T, left, rightType);
    bool result = !results.empty();
    return {result};
}

ResultTable FollowsTClause::evaluateIntegerInteger() {
    bool result = qpsClient.getRelationship(RelationshipType::FOLLOWS_T, left, right);
    return {result};
}

ResultTable FollowsTClause::evaluateWildcardSynonym() {
    DesignEntity leftType = DesignEntity::STMT;
    std::string rightValue = right.getValue();
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::FOLLOWS_T, leftType, rightType);
    std::unordered_set<std::string> processedMap = ClauseUtils::processMapToSetFromSecond(results);
    return {rightValue, processedMap};
}

ResultTable FollowsTClause::evaluateWildcardWildcard() {
    DesignEntity stmtType = DesignEntity::STMT;
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::FOLLOWS_T, stmtType, stmtType);
    bool result = !results.empty();
    return {result};
}

ResultTable FollowsTClause::evaluateWildcardInteger() {
    DesignEntity leftType = DesignEntity::STMT;
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(RelationshipType::FOLLOWS_T, leftType, right);
    bool result = !results.empty();
    return {result};
}


