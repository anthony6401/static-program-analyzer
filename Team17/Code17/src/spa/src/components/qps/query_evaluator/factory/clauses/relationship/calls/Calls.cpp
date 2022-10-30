#include "Calls.h"
#include <utility>
#include "components/qps/query_evaluator/factory/utils/ClauseUtils.h"

Calls::Calls(TokenObject left, TokenObject right, RelationshipType relationshipType, size_t priority,
                         std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                         QPSClient qpsClient) : left(std::move(left)), right(std::move(right)), relationshipType(relationshipType), priority(priority),
                                                synonymToDesignEntityMap(std::move(synonymToDesignEntityMap)), qpsClient(qpsClient) {};

ResultTable Calls::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::NAME && rightType == TokenType::NAME) {
        return Calls::evaluateSynonymSynonym(relationshipType);
    } else if (leftType == TokenType::NAME && rightType == TokenType::WILDCARD) {
        return Calls::evaluateSynonymWildcard(relationshipType);
    } else if (leftType == TokenType::NAME && rightType == TokenType::NAME_WITH_QUOTATION) {
        return Calls::evaluateSynonymNameQuotes(relationshipType);
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::NAME) {
        return Calls::evaluateWildcardSynonym(relationshipType);
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::WILDCARD) {
        return Calls::evaluateWildcardWildcard(relationshipType);
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::NAME_WITH_QUOTATION) {
        return Calls::evaluateWildcardNameQuotes(relationshipType);
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::NAME) {
        return Calls::evaluateNameQuotesSynonym(relationshipType);
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::WILDCARD) {
        return Calls::evaluateNameQuotesWildcard(relationshipType);
    } else {
        return Calls::evaluateNameQuotesNameQuotes(relationshipType);
    }
}

size_t Calls::getPriority() {
    return priority;
}

size_t Calls::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

std::set<std::string> Calls::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (left.getTokenType() == TokenType::NAME) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::NAME) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
}


ResultTable Calls::evaluateSynonymSynonym(RelationshipType relationshipType) {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string leftValue = left.getValue();
    std::string rightValue = right.getValue();
    if (leftValue == rightValue) {
        return {false};
    }
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(relationshipType, procType, procType);
    std::vector<std::pair<std::string, std::string>> processedMap = ClauseUtils::processMapToVectorPair(results);
    return {leftValue, rightValue, processedMap};
}

ResultTable Calls::evaluateSynonymWildcard(RelationshipType relationshipType) {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string leftValue = left.getValue();
    std::unordered_set<std::string> results = qpsClient.getRelationshipWithSecondWildcard(relationshipType, procType);
    return {leftValue, results};
}

ResultTable Calls::evaluateSynonymNameQuotes(RelationshipType relationshipType) {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string leftValue = left.getValue();
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(relationshipType, procType, right);
    return {leftValue, results};
}

ResultTable Calls::evaluateWildcardSynonym(RelationshipType relationshipType) {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string rightValue = right.getValue();
    std::unordered_set<std::string> results = qpsClient.getRelationshipWithFirstWildcard(relationshipType, procType);
    return {rightValue, results};
}

ResultTable Calls::evaluateWildcardWildcard(RelationshipType relationshipType) {
    bool result = qpsClient.getRelationship(relationshipType, left, right);
    return {result};
}

ResultTable Calls::evaluateWildcardNameQuotes(RelationshipType relationshipType) {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string leftValue = left.getValue();
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(relationshipType, procType, right);
    bool booleanResult = !results.empty();
    return {booleanResult};
}

ResultTable Calls::evaluateNameQuotesSynonym(RelationshipType relationshipType) {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string rightValue = right.getValue();
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(relationshipType, left, procType);
    return {rightValue, results};
}

ResultTable Calls::evaluateNameQuotesWildcard(RelationshipType relationshipType) {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(relationshipType, left, procType);
    bool result = !results.empty();
    return {result};
}

ResultTable Calls::evaluateNameQuotesNameQuotes(RelationshipType relationshipType) {
    bool result = qpsClient.getRelationship(relationshipType, left, right);
    return {result};
}



