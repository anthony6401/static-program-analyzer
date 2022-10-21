#include "ParentClause.h"
#include <utility>
#include "components/qps/query_evaluator/factory/utils/ClauseUtils.h"

ParentClause::ParentClause(TokenObject left, TokenObject right,
                             std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                             QPSClient qpsClient) : left(std::move(left)), right(std::move(right)),
                                                    synonymToDesignEntityMap(std::move(synonymToDesignEntityMap)), qpsClient(qpsClient) {}

ResultTable ParentClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::NAME && rightType == TokenType::NAME) {
        return ParentClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::NAME && rightType == TokenType::WILDCARD) {
        return ParentClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::NAME && rightType == TokenType::INTEGER) {
        return ParentClause::evaluateSynonymInteger();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::NAME) {
        return ParentClause::evaluateIntegerSynonym();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::WILDCARD) {
        return ParentClause::evaluateIntegerWildcard();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::INTEGER) {
        return ParentClause::evaluateIntegerInteger();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::NAME) {
        return ParentClause::evaluateWildcardSynonym();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::WILDCARD) {
        return ParentClause::evaluateWildcardWildcard();
    } else {
        return ParentClause::evaluateWildcardInteger();
    }
}

size_t ParentClause::getPriority() {
    return priority;
}

std::set<std::string> ParentClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (left.getTokenType() == TokenType::NAME) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::NAME) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
}

size_t ParentClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

ResultTable ParentClause::evaluateSynonymSynonym() {
    std::string leftValue = left.getValue();
    std::string rightValue = right.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    if (leftValue == rightValue) {
        return {false};
    }
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::PARENT, leftType, rightType);
    std::vector<std::pair<std::string, std::string>> processedMap = ClauseUtils::processMapToVectorPair(results);
    return {leftValue, rightValue, processedMap};
}

ResultTable ParentClause::evaluateSynonymWildcard() {
    std::string leftValue = left.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    DesignEntity rightType = DesignEntity::STMT;
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::PARENT, leftType, rightType);
    std::unordered_set<std::string> processedMap = ClauseUtils::processMapToSetFromFirst(results);
    return {leftValue, processedMap};
}

ResultTable ParentClause::evaluateSynonymInteger() {
    std::string leftValue = left.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(RelationshipType::PARENT, leftType, right);
    return {leftValue, results};
}

ResultTable ParentClause::evaluateIntegerSynonym() {
    std::string rightValue = right.getValue();
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(RelationshipType::PARENT, left, rightType);
    return {rightValue, results};
}

ResultTable ParentClause::evaluateIntegerWildcard() {
    DesignEntity rightType = DesignEntity::STMT;
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(RelationshipType::PARENT, left, rightType);
    bool result = !results.empty();
    return {result};
}

ResultTable ParentClause::evaluateIntegerInteger() {
    bool result = qpsClient.getRelationship(RelationshipType::PARENT, left, right);
    return {result};
}

ResultTable ParentClause::evaluateWildcardSynonym() {
    DesignEntity leftType = DesignEntity::STMT;
    std::string rightValue = right.getValue();
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::PARENT, leftType, rightType);
    std::unordered_set<std::string> processedMap = ClauseUtils::processMapToSetFromSecond(results);
    return {rightValue, processedMap};
}

ResultTable ParentClause::evaluateWildcardWildcard() {
    DesignEntity stmtType = DesignEntity::STMT;
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::PARENT, stmtType, stmtType);
    bool result = !results.empty();
    return {result};
}

ResultTable ParentClause::evaluateWildcardInteger() {
    DesignEntity leftType = DesignEntity::STMT;
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(RelationshipType::PARENT, leftType, right);
    bool result = !results.empty();
    return {result};
}


