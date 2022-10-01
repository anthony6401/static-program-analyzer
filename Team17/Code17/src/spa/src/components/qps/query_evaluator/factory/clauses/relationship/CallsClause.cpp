#include "CallsClause.h"

CallsClause::CallsClause(TokenObject left, TokenObject right, Select synonym,
                                 std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                                 QPSClient qpsClient) : left(left), right(right), synonym(synonym),
                                                        synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {};

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
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::NAME_WITH_QUOTATION) {
        return CallsClause::evaluateNameQuotesNameQuotes();
    } else {
        return {};
    }
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

std::vector<std::pair<std::string, std::string>> CallsClause::processMapToVectorPair(std::unordered_map<std::string, std::unordered_set<std::string>> results) {
    std::vector<std::pair<std::string, std::string>> processedResult;
    for (auto entry : results) {
        std::string firstSynonym = entry.first;
        std::unordered_set<std::string> secondSynonymList = entry.second;
        for (auto secondSynonym : secondSynonymList) {
            std::pair<std::string, std::string> newPair = {firstSynonym, secondSynonym};
            processedResult.emplace_back(newPair);
        }
    }
    return processedResult;
}

std::unordered_set<std::string> CallsClause::processMapToSetFromFirst(std::unordered_map<std::string, std::unordered_set<std::string>> results) {
    std::unordered_set<std::string> processedResult;
    for (auto entry : results) {
        std::string firstSynonym = entry.first;
        processedResult.insert(firstSynonym);
    }
    return processedResult;
}

std::unordered_set<std::string> CallsClause::processMapToSetFromSecond(std::unordered_map<std::string, std::unordered_set<std::string>> results) {
    std::unordered_set<std::string> processedResult;
    for (auto entry : results) {
        std::unordered_set<std::string> valuesInRow = entry.second;
        processedResult.insert(valuesInRow.begin(), valuesInRow.end());
    }
    return processedResult;
}

RelationshipType CallsClause::getRelationshipType() {
    return RelationshipType::CALLS;
}

ResultTable CallsClause::evaluateSynonymSynonym() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string leftValue = left.getValue();
    std::string rightValue = right.getValue();
    if (leftValue == rightValue) {
        return {false};
    }
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), procType, procType);
    std::vector<std::pair<std::string, std::string>> processedMap = CallsClause::processMapToVectorPair(results); // {{"1", "x"}, {"2", "y"}}
    return {leftValue, rightValue, processedMap};
}

ResultTable CallsClause::evaluateSynonymWildcard() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string leftValue = left.getValue();
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), procType, procType);
    std::unordered_set<std::string> processedMap = CallsClause::processMapToSetFromFirst(results);
    return {leftValue, processedMap};
}

ResultTable CallsClause::evaluateSynonymNameQuotes() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string leftValue = left.getValue();
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(getRelationshipType(), procType, right);
    return {leftValue, results};
}

ResultTable CallsClause::evaluateWildcardSynonym() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string rightValue = right.getValue();
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), procType, procType);
    std::unordered_set<std::string> processedMap = CallsClause::processMapToSetFromSecond(results);
    return {rightValue, processedMap};
}

ResultTable CallsClause::evaluateWildcardWildcard() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), procType, procType);
    bool booleanResult = !results.empty();
    return {booleanResult};
}

ResultTable CallsClause::evaluateWildcardNameQuotes() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string leftValue = left.getValue();
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(getRelationshipType(), procType, right);
    bool booleanResult = !results.empty();
    return {booleanResult};
}

ResultTable CallsClause::evaluateNameQuotesSynonym() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string rightValue = right.getValue();
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(getRelationshipType(), left, procType);
    return {rightValue, results};
}

ResultTable CallsClause::evaluateNameQuotesWildcard() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(getRelationshipType(), left, procType);
    bool booleanResult = !results.empty();
    // {1,2,3} -> boolean result = true
    return {booleanResult}; //true
}

ResultTable CallsClause::evaluateNameQuotesNameQuotes() {
    // Returns boolean
    bool result = qpsClient.getRelationship(getRelationshipType(), left, right);
    // result = true -> setIsFalseResult(true) -> isFalseResult = false
    return {result};
}


