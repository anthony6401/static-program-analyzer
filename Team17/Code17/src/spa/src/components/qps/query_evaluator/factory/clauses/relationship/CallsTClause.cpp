#include "CallsTClause.h"

CallsTClause::CallsTClause(TokenObject left, TokenObject right, Select synonym,
                         std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                         QPSClient qpsClient) : left(left), right(right), synonym(synonym),
                                                synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {};

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
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::NAME_WITH_QUOTATION) {
        return CallsTClause::evaluateNameQuotesNameQuotes();
    } else {
        return {};
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

std::vector<std::pair<std::string, std::string>> CallsTClause::processMapToVectorPair(std::unordered_map<std::string, std::unordered_set<std::string>> results) {
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

std::unordered_set<std::string> CallsTClause::processMapToSetFromFirst(std::unordered_map<std::string, std::unordered_set<std::string>> results) {
    std::unordered_set<std::string> processedResult;
    for (auto entry : results) {
        std::string firstSynonym = entry.first;
        processedResult.insert(firstSynonym);
    }
    return processedResult;
}

std::unordered_set<std::string> CallsTClause::processMapToSetFromSecond(std::unordered_map<std::string, std::unordered_set<std::string>> results) {
    std::unordered_set<std::string> processedResult;
    for (auto entry : results) {
        std::unordered_set<std::string> valuesInRow = entry.second;
        processedResult.insert(valuesInRow.begin(), valuesInRow.end());
    }
    return processedResult;
}

RelationshipType CallsTClause::getRelationshipType() {
    return RelationshipType::CALLS_T;
}

ResultTable CallsTClause::evaluateSynonymSynonym() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string leftValue = left.getValue();
    std::string rightValue = right.getValue();
    if (leftValue == rightValue) {
        return {false};
    }
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), procType, procType);
    std::vector<std::pair<std::string, std::string>> processedMap = CallsTClause::processMapToVectorPair(results); // {{"1", "x"}, {"2", "y"}}
    return {leftValue, rightValue, processedMap};
}

ResultTable CallsTClause::evaluateSynonymWildcard() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string leftValue = left.getValue();
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), procType, procType);
    std::unordered_set<std::string> processedMap = CallsTClause::processMapToSetFromFirst(results);
    return {leftValue, processedMap};
}

ResultTable CallsTClause::evaluateSynonymNameQuotes() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string leftValue = left.getValue();
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(getRelationshipType(), procType, right);
    return {leftValue, results};
}

ResultTable CallsTClause::evaluateWildcardSynonym() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string rightValue = right.getValue();
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), procType, procType);
    std::unordered_set<std::string> processedMap = CallsTClause::processMapToSetFromSecond(results);
    return {rightValue, processedMap};
}

ResultTable CallsTClause::evaluateWildcardWildcard() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), procType, procType);
    bool booleanResult = !results.empty();
    return {booleanResult};
}

ResultTable CallsTClause::evaluateWildcardNameQuotes() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string leftValue = left.getValue();
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(getRelationshipType(), procType, right);
    bool booleanResult = !results.empty();
    return {booleanResult};
}

ResultTable CallsTClause::evaluateNameQuotesSynonym() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::string rightValue = right.getValue();
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(getRelationshipType(), left, procType);
    return {rightValue, results};
}

ResultTable CallsTClause::evaluateNameQuotesWildcard() {
    DesignEntity procType = DesignEntity::PROCEDURE;
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(getRelationshipType(), left, procType);
    bool booleanResult = !results.empty();
    // {1,2,3} -> boolean result = true
    return {booleanResult}; //true
}

ResultTable CallsTClause::evaluateNameQuotesNameQuotes() {
    // Returns boolean
    bool result = qpsClient.getRelationship(getRelationshipType(), left, right);
    // result = true -> setIsFalseResult(true) -> isFalseResult = false
    return {result};
}


