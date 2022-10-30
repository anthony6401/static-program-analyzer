#include "Follows.h"
#include <utility>
#include "components/qps/query_evaluator/factory/utils/ClauseUtils.h"

Follows::Follows(TokenObject left, TokenObject right, RelationshipType relationshipType, size_t priority,
                             std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                             QPSClient qpsClient) : left(std::move(left)), right(std::move(right)), relationshipType(relationshipType), priority(priority),
                                                    synonymToDesignEntityMap(std::move(synonymToDesignEntityMap)), qpsClient(qpsClient) {}

ResultTable Follows::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::NAME && rightType == TokenType::NAME) {
        return Follows::evaluateSynonymSynonym(relationshipType);
    } else if (leftType == TokenType::NAME && rightType == TokenType::WILDCARD) {
        return Follows::evaluateSynonymWildcard(relationshipType);
    } else if (leftType == TokenType::NAME && rightType == TokenType::INTEGER) {
        return Follows::evaluateSynonymInteger(relationshipType);
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::NAME) {
        return Follows::evaluateIntegerSynonym(relationshipType);
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::WILDCARD) {
        return Follows::evaluateIntegerWildcard(relationshipType);
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::INTEGER) {
        return Follows::evaluateIntegerInteger(relationshipType);
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::NAME) {
        return Follows::evaluateWildcardSynonym(relationshipType);
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::WILDCARD) {
        return Follows::evaluateWildcardWildcard(relationshipType);
    } else {
        return Follows::evaluateWildcardInteger(relationshipType);
    }
}

size_t Follows::getPriority() {
    return priority;
}

std::set<std::string> Follows::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (left.getTokenType() == TokenType::NAME) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::NAME) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
}

size_t Follows::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

ResultTable Follows::evaluateSynonymSynonym(RelationshipType relationshipType) {
    std::string leftValue = left.getValue();
    std::string rightValue = right.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    if (leftValue == rightValue) {
        return {false};
    }
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(relationshipType, leftType, rightType);
    std::vector<std::pair<std::string, std::string>> processedMap = ClauseUtils::processMapToVectorPair(results);
    return {leftValue, rightValue, processedMap};
}

ResultTable Follows::evaluateSynonymWildcard(RelationshipType relationshipType) {
    std::string leftValue = left.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipWithSecondWildcard(relationshipType, leftType);
    return {leftValue, results};
}

ResultTable Follows::evaluateSynonymInteger(RelationshipType relationshipType) {
    std::string leftValue = left.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(relationshipType, leftType, right);
    return {leftValue, results};
}

ResultTable Follows::evaluateIntegerSynonym(RelationshipType relationshipType) {
    std::string rightValue = right.getValue();
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(relationshipType, left, rightType);
    return {rightValue, results};
}

ResultTable Follows::evaluateIntegerWildcard(RelationshipType relationshipType) {
    bool result = qpsClient.getRelationship(relationshipType, left, right);
    return {result};
}

ResultTable Follows::evaluateIntegerInteger(RelationshipType relationshipType) {
    bool result = qpsClient.getRelationship(relationshipType, left, right);
    return {result};
}

ResultTable Follows::evaluateWildcardSynonym(RelationshipType relationshipType) {
    std::string rightValue = right.getValue();
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipWithFirstWildcard(relationshipType, rightType);
    return {rightValue, results};
}

ResultTable Follows::evaluateWildcardWildcard(RelationshipType relationshipType) {
    bool result = qpsClient.getRelationship(relationshipType, left, right);
    return {result};
}

ResultTable Follows::evaluateWildcardInteger(RelationshipType relationshipType) {
    bool result = qpsClient.getRelationship(relationshipType, left, right);
    return {result};
}



