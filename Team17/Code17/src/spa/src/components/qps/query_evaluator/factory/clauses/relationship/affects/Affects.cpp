#include "Affects.h"
#include <utility>
#include "components/qps/query_evaluator/factory/utils/ClauseUtils.h"

Affects::Affects(TokenObject left, TokenObject right, RelationshipType relationshipType, size_t priority,
                             std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                             QPSClient qpsClient) : left(std::move(left)), right(std::move(right)), relationshipType(relationshipType), priority(priority),
                                                    synonymToDesignEntityMap(std::move(synonymToDesignEntityMap)), qpsClient(qpsClient) {}

ResultTable Affects::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::NAME && rightType == TokenType::NAME) {
        return Affects::evaluateSynonymSynonym(relationshipType);
    } else if (leftType == TokenType::NAME && rightType == TokenType::WILDCARD) {
        return Affects::evaluateSynonymWildcard(relationshipType);
    } else if (leftType == TokenType::NAME && rightType == TokenType::INTEGER) {
        return Affects::evaluateSynonymInteger(relationshipType);
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::NAME) {
        return Affects::evaluateIntegerSynonym(relationshipType);
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::WILDCARD) {
        return Affects::evaluateIntegerWildcard(relationshipType);
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::INTEGER) {
        return Affects::evaluateIntegerInteger(relationshipType);
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::NAME) {
        return Affects::evaluateWildcardSynonym(relationshipType);
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::WILDCARD) {
        return Affects::evaluateWildcardWildcard(relationshipType);
    } else {
        return Affects::evaluateWildcardInteger(relationshipType);
    }
}

size_t Affects::getPriority() {
    return priority;
}

std::set<std::string> Affects::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (left.getTokenType() == TokenType::NAME) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::NAME) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
}

size_t Affects::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

ResultTable Affects::evaluateSynonymSynonym(RelationshipType relationshipType) {
    std::string leftValue = left.getValue();
    std::string rightValue = right.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(relationshipType, leftType, rightType);

    if (leftValue == rightValue) {
        std::unordered_set<std::string> leftAndRightEqualResults = ClauseUtils::processMapToSetByMapIntersection(results);
        return {leftValue, leftAndRightEqualResults};
    }

    std::vector<std::pair<std::string, std::string>> processedMap = ClauseUtils::processMapToVectorPair(results);
    return {leftValue, rightValue, processedMap};
}

ResultTable Affects::evaluateSynonymWildcard(RelationshipType relationshipType) {
    std::string leftValue = left.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    DesignEntity rightType = DesignEntity::STMT;
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(relationshipType, leftType, rightType);
    std::unordered_set<std::string> processedMap = ClauseUtils::processMapToSetFromFirst(results);
    return {leftValue, processedMap};
}

ResultTable Affects::evaluateSynonymInteger(RelationshipType relationshipType) {
    std::string leftValue = left.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(relationshipType, leftType, right);
    return {leftValue, results};
}

ResultTable Affects::evaluateIntegerSynonym(RelationshipType relationshipType) {
    std::string rightValue = right.getValue();
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(relationshipType, left, rightType);
    return {rightValue, results};
}

ResultTable Affects::evaluateIntegerWildcard(RelationshipType relationshipType) {
    DesignEntity rightType = DesignEntity::STMT;
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(relationshipType, left, rightType);
    bool result = !results.empty();
    return {result};
}

ResultTable Affects::evaluateIntegerInteger(RelationshipType relationshipType) {
    bool result = qpsClient.getRelationship(relationshipType, left, right);
    return {result};
}

ResultTable Affects::evaluateWildcardSynonym(RelationshipType relationshipType) {
    DesignEntity leftType = DesignEntity::STMT;
    std::string rightValue = right.getValue();
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(relationshipType, leftType, rightType);
    std::unordered_set<std::string> processedMap = ClauseUtils::processMapToSetFromSecond(results);
    return {rightValue, processedMap};
}

ResultTable Affects::evaluateWildcardWildcard(RelationshipType relationshipType) {
    DesignEntity stmtType = DesignEntity::STMT;
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(relationshipType, stmtType, stmtType);
    bool result = !results.empty();
    return {result};
}

ResultTable Affects::evaluateWildcardInteger(RelationshipType relationshipType) {
    DesignEntity leftType = DesignEntity::STMT;
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(relationshipType, leftType, right);
    bool result = !results.empty();
    return {result};
}


