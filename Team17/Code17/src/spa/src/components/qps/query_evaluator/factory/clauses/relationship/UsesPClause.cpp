#include "UsesPClause.h"
#include "iostream"

UsesPClause::UsesPClause(TokenObject left, TokenObject right, Select synonym,
                         std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient) :
        left(left), right(right), synonym(synonym),
        synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {};

ResultTable UsesPClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::NAME && rightType == TokenType::NAME) {
        return UsesPClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::NAME && rightType == TokenType::WILDCARD) {
        return UsesPClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::NAME && rightType == TokenType::NAME_WITH_QUOTATION) {
        return UsesPClause::evaluateSynonymNameQuotes();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::NAME) {
        return UsesPClause::evaluateNameQuotesSynonym();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::WILDCARD) {
        return UsesPClause::evaluateNameQuotesWildcard();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::NAME_WITH_QUOTATION) {
        return UsesPClause::evaluateNameQuotesNameQuotes();
    } else {
        return {};
    }
}

size_t UsesPClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

std::set<std::string> UsesPClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (left.getTokenType() == TokenType::NAME) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::NAME) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
}

std::vector<std::pair<std::string, std::string>> UsesPClause::processMapToVectorPair(std::unordered_map<std::string, std::unordered_set<std::string>> results) {
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

std::unordered_set<std::string> UsesPClause::processMapToSetFromFirst(std::unordered_map<std::string, std::unordered_set<std::string>> results) {
    std::unordered_set<std::string> processedResult;
    for (auto entry : results) {
        std::string firstSynonym = entry.first;
        processedResult.insert(firstSynonym);
    }
    return processedResult;
}

RelationshipType UsesPClause::getRelationshipType() {
    return RelationshipType::USES;
}

ResultTable UsesPClause::evaluateSynonymSynonym() {
    DesignEntity stmtType = synonymToDesignEntityMap[left.getValue()]; // Procedure
    DesignEntity rightType = synonymToDesignEntityMap[right.getValue()];
    std::string leftValue = left.getValue();
    std::string rightValue = right.getValue();
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), stmtType, rightType);
    std::vector<std::pair<std::string, std::string>> processedMap = UsesPClause::processMapToVectorPair(results); // {{"1", "x"}, {"2", "y"}}
    return {leftValue, rightValue, processedMap};
}

ResultTable UsesPClause::evaluateSynonymWildcard() {
    DesignEntity stmtType = synonymToDesignEntityMap[left.getValue()]; // Procedure
    DesignEntity rightType = DesignEntity::VARIABLE;
    std::string leftValue = left.getValue();
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), stmtType, rightType);
    std::unordered_set<std::string> processedMap = UsesPClause::processMapToSetFromFirst(results);
    return {leftValue, processedMap};
}

ResultTable UsesPClause::evaluateSynonymNameQuotes() {
    DesignEntity stmtType = synonymToDesignEntityMap[left.getValue()];
    std::string leftValue = left.getValue();
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(getRelationshipType(), stmtType, right);
    return {leftValue, results};
}

ResultTable UsesPClause::evaluateNameQuotesSynonym() {
    std::string rightValue = right.getValue();
    DesignEntity rightType = synonymToDesignEntityMap[right.getValue()];
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(getRelationshipType(), left, rightType);
    return {rightValue, results};
}

ResultTable UsesPClause::evaluateNameQuotesWildcard() {
    DesignEntity rightType = DesignEntity::VARIABLE;
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(getRelationshipType(), left, rightType);
    bool booleanResult = !results.empty();
    // {1,2,3} -> boolean result = true
    return {booleanResult}; //true
}

ResultTable UsesPClause::evaluateNameQuotesNameQuotes() {
    // Returns boolean
    bool result = qpsClient.getRelationship(getRelationshipType(), left, right);
    // result = true -> setIsFalseResult(true) -> isFalseResult = false
    return {result};
}


