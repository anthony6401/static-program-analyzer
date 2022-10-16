#include "CallsTClause.h"
#include <utility>
#include "components/qps/query_evaluator/factory/utils/ClauseUtils.h"

CallsTClause::CallsTClause(TokenObject left, TokenObject right,
                         std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                         QPSClient qpsClient) : left(std::move(left)), right(std::move(right)),
                                                synonymToDesignEntityMap(std::move(synonymToDesignEntityMap)), qpsClient(qpsClient) {};

ResultTable CallsTClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::NAME && rightType == TokenType::NAME) {
        return CallsTClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::NAME && rightType == TokenType::WILDCARD) {
        return CallsTClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::NAME && rightType == TokenType::NAME_WITH_QUOTATION) {
        return CallsTClause::evaluateSynonymNameQuotes();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::NAME) {
        return CallsTClause::evaluateWildcardSynonym();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::WILDCARD) {
        return CallsTClause::evaluateWildcardWildcard();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::NAME_WITH_QUOTATION) {
        return CallsTClause::evaluateWildcardNameQuotes();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::NAME) {
        return CallsTClause::evaluateNameQuotesSynonym();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::WILDCARD) {
        return CallsTClause::evaluateNameQuotesWildcard();
    } else {
        return CallsTClause::evaluateNameQuotesNameQuotes();
    }
}

size_t CallsTClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

std::set<std::string> CallsTClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (left.getTokenType() == TokenType::NAME) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::NAME) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
}


ResultTable CallsTClause::evaluateSynonymSynonym() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string leftValue = left.getValue();
    std::string rightValue = right.getValue();
    if (leftValue == rightValue) {
        return {false};
    }
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::CALLS_T, procType, procType);
    std::vector<std::pair<std::string, std::string>> processedMap = ClauseUtils::processMapToVectorPair(results);
    return {leftValue, rightValue, processedMap};
}

ResultTable CallsTClause::evaluateSynonymWildcard() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string leftValue = left.getValue();
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::CALLS_T, procType, procType);
    std::unordered_set<std::string> processedMap = ClauseUtils::processMapToSetFromFirst(results);
    return {leftValue, processedMap};
}

ResultTable CallsTClause::evaluateSynonymNameQuotes() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string leftValue = left.getValue();
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(RelationshipType::CALLS_T, procType, right);
    return {leftValue, results};
}

ResultTable CallsTClause::evaluateWildcardSynonym() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string rightValue = right.getValue();
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::CALLS_T, procType, procType);
    std::unordered_set<std::string> processedMap = ClauseUtils::processMapToSetFromSecond(results);
    return {rightValue, processedMap};
}

ResultTable CallsTClause::evaluateWildcardWildcard() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(RelationshipType::CALLS_T, procType, procType);
    bool result = !results.empty();
    return {result};
}

ResultTable CallsTClause::evaluateWildcardNameQuotes() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string leftValue = left.getValue();
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(RelationshipType::CALLS_T, procType, right);
    bool booleanResult = !results.empty();
    return {booleanResult};
}

ResultTable CallsTClause::evaluateNameQuotesSynonym() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string rightValue = right.getValue();
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(RelationshipType::CALLS_T, left, procType);
    return {rightValue, results};
}

ResultTable CallsTClause::evaluateNameQuotesWildcard() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(RelationshipType::CALLS_T, left, procType);
    bool result = !results.empty();
    return {result};
}

ResultTable CallsTClause::evaluateNameQuotesNameQuotes() {
    bool result = qpsClient.getRelationship(RelationshipType::CALLS_T, left, right);
    return {result};
}


