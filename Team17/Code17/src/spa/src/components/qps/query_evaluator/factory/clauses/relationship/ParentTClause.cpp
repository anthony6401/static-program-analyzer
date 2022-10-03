#include "ParentTClause.h"

ParentTClause::ParentTClause(TokenObject left, TokenObject right, Select synonym,
                               std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                               QPSClient qpsClient) : left(left), right(right), synonym(synonym),
                                                      synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {}

ResultTable ParentTClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::NAME && rightType == TokenType::NAME) {
        return ParentTClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::NAME && rightType == TokenType::WILDCARD) {
        return ParentTClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::NAME && rightType == TokenType::INTEGER) {
        return ParentTClause::evaluateSynonymInteger();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::NAME) {
        return ParentTClause::evaluateIntegerSynonym();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::WILDCARD) {
        return ParentTClause::evaluateIntegerWildcard();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::INTEGER) {
        return ParentTClause::evaluateIntegerInteger();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::NAME) {
        return ParentTClause::evaluateWildcardSynonym();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::WILDCARD) {
        return ParentTClause::evaluateWildcardWildcard();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::INTEGER) {
        return ParentTClause::evaluateWildcardInteger();
    } else {
        return {};
    }
}

std::set<std::string> ParentTClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (left.getTokenType() == TokenType::NAME) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::NAME) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
}

size_t ParentTClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

RelationshipType ParentTClause::getRelationshipType() {
    return RelationshipType::PARENT_T;
}

std::vector<std::pair<std::string, std::string>> ParentTClause::processMapToVectorPair(std::unordered_map<std::string, std::unordered_set<std::string>> results) {
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

std::unordered_set<std::string> ParentTClause::processMapToSetFromFirst(std::unordered_map<std::string, std::unordered_set<std::string>> results) {
    std::unordered_set<std::string> processedResult;
    for (auto entry : results) {
        std::string firstSynonym = entry.first;
        processedResult.insert(firstSynonym);
    }
    return processedResult;
}

std::unordered_set<std::string> ParentTClause::processMapToSetFromSecond(std::unordered_map<std::string, std::unordered_set<std::string>> results) {
    std::unordered_set<std::string> processedResult;
    for (auto entry : results) {
        std::unordered_set<std::string> valuesInRow = entry.second;
        processedResult.insert(valuesInRow.begin(), valuesInRow.end());
    }
    return processedResult;
}

ResultTable ParentTClause::evaluateSynonymSynonym() {
    DesignEntity leftType = synonymToDesignEntityMap[left.getValue()];
    DesignEntity rightType = synonymToDesignEntityMap[right.getValue()];
    std::string leftValue = left.getValue();
    std::string rightValue = right.getValue();
    if (leftValue == rightValue) {
        return {false};
    }
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), leftType, rightType);
    std::vector<std::pair<std::string, std::string>> processedMap = ParentTClause::processMapToVectorPair(results); // {{"1", "x"}, {"2", "y"}}
    return {leftValue, rightValue, processedMap};
}

ResultTable ParentTClause::evaluateSynonymWildcard() {
    DesignEntity leftType = synonymToDesignEntityMap[left.getValue()];
    DesignEntity rightType = DesignEntity::STMT;
    std::string leftValue = left.getValue();
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), leftType, rightType);
    std::unordered_set<std::string> processedMap = ParentTClause::processMapToSetFromFirst(results);
    return {leftValue, processedMap};
}

ResultTable ParentTClause::evaluateSynonymInteger() {
    DesignEntity leftType = synonymToDesignEntityMap[left.getValue()];
    std::string leftValue = left.getValue();
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(getRelationshipType(), leftType, right);
    return {leftValue, results};
}

ResultTable ParentTClause::evaluateIntegerSynonym() {
    std::string rightValue = right.getValue();
    DesignEntity rightType = synonymToDesignEntityMap[right.getValue()];
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(getRelationshipType(), left, rightType);
    return {rightValue, results};
}

ResultTable ParentTClause::evaluateIntegerWildcard() {
    // Returns boolean
    DesignEntity rightType = DesignEntity::STMT;
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(getRelationshipType(), left, rightType);
    bool booleanResult = !results.empty();
    // {1,2,3} -> boolean result = true
    return {booleanResult};
}

ResultTable ParentTClause::evaluateIntegerInteger() {
    // Returns boolean
    bool result = qpsClient.getRelationship(getRelationshipType(), left, right);
    // result = true -> setIsFalseResult(true) -> isFalseResult = false
    return {result};
}

ResultTable ParentTClause::evaluateWildcardSynonym() {
    DesignEntity leftType = DesignEntity::STMT;
    DesignEntity rightType = synonymToDesignEntityMap[right.getValue()];
    std::string rightValue = right.getValue();
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), leftType, rightType);
    std::unordered_set<std::string> processedMap = ParentTClause::processMapToSetFromSecond(results);
    return {rightValue, processedMap};
}

ResultTable ParentTClause::evaluateWildcardWildcard() {
    DesignEntity stmtType = DesignEntity::STMT;
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), stmtType, stmtType);
    bool booleanResult = !results.empty();
    return {booleanResult};
}

ResultTable ParentTClause::evaluateWildcardInteger() {
    DesignEntity leftType = DesignEntity::STMT;
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(getRelationshipType(), leftType, right);
    bool booleanResult = !results.empty();
    return {booleanResult};
}