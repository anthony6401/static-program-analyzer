#include "Next.h"
#include <utility>
#include "components/qps/query_evaluator/factory/utils/ClauseUtils.h"

Next::Next(TokenObject left, TokenObject right, RelationshipType relationshipType, size_t priority,
                       std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                       QPSClient qpsClient) : left(std::move(left)), right(std::move(right)), relationshipType(relationshipType), priority(priority),
                                              synonymToDesignEntityMap(std::move(synonymToDesignEntityMap)), qpsClient(qpsClient) {}

ResultTable Next::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::NAME && rightType == TokenType::NAME) {
        return Next::evaluateSynonymSynonym(relationshipType);
    } else if (leftType == TokenType::NAME && rightType == TokenType::WILDCARD) {
        return Next::evaluateSynonymWildcard(relationshipType);
    } else if (leftType == TokenType::NAME && rightType == TokenType::INTEGER) {
        return Next::evaluateSynonymInteger(relationshipType);
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::NAME) {
        return Next::evaluateIntegerSynonym(relationshipType);
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::WILDCARD) {
        return Next::evaluateIntegerWildcard(relationshipType);
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::INTEGER) {
        return Next::evaluateIntegerInteger(relationshipType);
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::NAME) {
        return Next::evaluateWildcardSynonym(relationshipType);
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::WILDCARD) {
        return Next::evaluateWildcardWildcard(relationshipType);
    } else {
        return Next::evaluateWildcardInteger(relationshipType);
    }
}

size_t Next::getPriority() {
    return priority;
}

std::set<std::string> Next::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (left.getTokenType() == TokenType::NAME) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::NAME) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
}

size_t Next::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

ResultTable Next::evaluateSynonymSynonym(RelationshipType relationshipType) {
    std::string leftValue = left.getValue();
    std::string rightValue = right.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];

    if (leftValue == rightValue && relationshipType == RelationshipType::NEXT) {
        return {false};
    }

    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(relationshipType, leftType, rightType);

    if (leftValue == rightValue && relationshipType == RelationshipType::NEXT_T) {
        std::unordered_set<std::string> leftAndRightEqualResults = ClauseUtils::processMapToSetByMapIntersection(results);
        return {leftValue, leftAndRightEqualResults};
    }

    std::vector<std::pair<std::string, std::string>> processedMap = ClauseUtils::processMapToVectorPair(results);
    return {leftValue, rightValue, processedMap};
}

ResultTable Next::evaluateSynonymWildcard(RelationshipType relationshipType) {
    std::string leftValue = left.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipWithSecondWildcard(relationshipType, leftType);
    return {leftValue, results};
}

ResultTable Next::evaluateSynonymInteger(RelationshipType relationshipType) {
    std::string leftValue = left.getValue();
    DesignEntity leftType = synonymToDesignEntityMap[leftValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(relationshipType, leftType, right);
    return {leftValue, results};
}

ResultTable Next::evaluateIntegerSynonym(RelationshipType relationshipType) {
    std::string rightValue = right.getValue();
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(relationshipType, left, rightType);
    return {rightValue, results};
}

ResultTable Next::evaluateIntegerWildcard(RelationshipType relationshipType) {
    bool result = qpsClient.getRelationship(relationshipType, left, right);
    return {result};
}

ResultTable Next::evaluateIntegerInteger(RelationshipType relationshipType) {
    bool result = qpsClient.getRelationship(relationshipType, left, right);
    return {result};
}

ResultTable Next::evaluateWildcardSynonym(RelationshipType relationshipType) {
    std::string rightValue = right.getValue();
    DesignEntity rightType = synonymToDesignEntityMap[rightValue];
    std::unordered_set<std::string> results = qpsClient.getRelationshipWithFirstWildcard(relationshipType, rightType);
    return {rightValue, results};
}

ResultTable Next::evaluateWildcardWildcard(RelationshipType relationshipType) {
    bool result = qpsClient.getRelationship(relationshipType, left, right);
    return {result};
}

ResultTable Next::evaluateWildcardInteger(RelationshipType relationshipType) {
    bool result = qpsClient.getRelationship(relationshipType, left, right);
    return {result};
}


