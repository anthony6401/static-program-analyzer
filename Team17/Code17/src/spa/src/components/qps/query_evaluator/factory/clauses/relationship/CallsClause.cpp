#include "CallsClause.h"
#include <utility>
#include "components/qps/query_evaluator/factory/utils/ClauseUtils.h"

CallsClause::CallsClause(TokenObject left, TokenObject right,
                                 std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                                 QPSClient qpsClient) : left(std::move(left)), right(std::move(right)),
                                                        synonymToDesignEntityMap(std::move(synonymToDesignEntityMap)), qpsClient(qpsClient) {};

ResultTable CallsClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::NAME && rightType == TokenType::NAME) {
        return CallsClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::NAME && rightType == TokenType::WILDCARD) {
        return CallsClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::NAME && rightType == TokenType::NAME_WITH_QUOTATION) {
        return CallsClause::evaluateSynonymNameQuotes();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::NAME) {
        return CallsClause::evaluateWildcardSynonym();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::WILDCARD) {
        return CallsClause::evaluateWildcardWildcard();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::NAME_WITH_QUOTATION) {
        return CallsClause::evaluateWildcardNameQuotes();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::NAME) {
        return CallsClause::evaluateNameQuotesSynonym();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::WILDCARD) {
        return CallsClause::evaluateNameQuotesWildcard();
    } else {
        return CallsClause::evaluateNameQuotesNameQuotes();
    }
}

size_t CallsClause::getPriority() {
    return priority;
}

size_t CallsClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

std::set<std::string> CallsClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (left.getTokenType() == TokenType::NAME) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::NAME) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
}


ResultTable CallsClause::evaluateSynonymSynonym() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string leftValue = left.getValue();
    std::string rightValue = right.getValue();
    if (leftValue == rightValue) {
        return {false};
    }
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::CALLS, procType, procType);
    std::vector<std::pair<std::string, std::string>> processedMap = ClauseUtils::processMapToVectorPair(results);
    return {leftValue, rightValue, processedMap};
}

ResultTable CallsClause::evaluateSynonymWildcard() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string leftValue = left.getValue();
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::CALLS, procType, procType);
    std::unordered_set<std::string> processedMap = ClauseUtils::processMapToSetFromFirst(results);
    return {leftValue, processedMap};
}

ResultTable CallsClause::evaluateSynonymNameQuotes() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string leftValue = left.getValue();
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(RelationshipType::CALLS, procType, right);
    return {leftValue, results};
}

ResultTable CallsClause::evaluateWildcardSynonym() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string rightValue = right.getValue();
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::CALLS, procType, procType);
    std::unordered_set<std::string> processedMap = ClauseUtils::processMapToSetFromSecond(results);
    return {rightValue, processedMap};
}

ResultTable CallsClause::evaluateWildcardWildcard() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::CALLS, procType, procType);
    bool result = !results.empty();
    return {result};
}

ResultTable CallsClause::evaluateWildcardNameQuotes() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string leftValue = left.getValue();
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(RelationshipType::CALLS, procType, right);
    bool booleanResult = !results.empty();
    return {booleanResult};
}

ResultTable CallsClause::evaluateNameQuotesSynonym() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string rightValue = right.getValue();
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(RelationshipType::CALLS, left, procType);
    return {rightValue, results};
}

ResultTable CallsClause::evaluateNameQuotesWildcard() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(RelationshipType::CALLS, left, procType);
    bool result = !results.empty();
    return {result};
}

ResultTable CallsClause::evaluateNameQuotesNameQuotes() {
    bool result = qpsClient.getRelationship(RelationshipType::CALLS, left, right);
    return {result};
}


