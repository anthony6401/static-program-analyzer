#include "FollowsClause.h"
#include "iostream"

FollowsClause::FollowsClause(TokenObject left, TokenObject right, Select synonym,
                             std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                             QPSClient qpsClient) : left(left), right(right), synonym(synonym),
                                                    synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {}

RawResult FollowsClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::NAME && rightType == TokenType::NAME) {
        return FollowsClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::NAME && rightType == TokenType::WILDCARD) {
        return FollowsClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::NAME && rightType == TokenType::INTEGER) {
        return FollowsClause::evaluateSynonymInteger();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::NAME) {
        return FollowsClause::evaluateIntegerSynonym();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::WILDCARD) {
        return FollowsClause::evaluateIntegerWildcard();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::INTEGER) {
        return FollowsClause::evaluateIntegerInteger();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::NAME) {
        return FollowsClause::evaluateWildcardSynonym();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::WILDCARD) {
        return FollowsClause::evaluateWildcardWildcard();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::INTEGER) {
        return FollowsClause::evaluateWildcardInteger();
    } else {
        return {};
    }
}

size_t FollowsClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

std::set<std::string> FollowsClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (left.getTokenType() == TokenType::NAME) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::NAME) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
}

RelationshipType FollowsClause::getRelationshipType() {
    return RelationshipType::FOLLOWS;
}

std::vector<std::pair<std::string, std::string>> FollowsClause::processMapToVectorPair(std::unordered_map<std::string, std::unordered_set<std::string>> results) {
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

std::unordered_set<std::string> FollowsClause::processMapToSetFromFirst(std::unordered_map<std::string, std::unordered_set<std::string>> results) {
    std::unordered_set<std::string> processedResult;
    for (auto entry : results) {
        std::string firstSynonym = entry.first;
        processedResult.insert(firstSynonym);
    }
    return processedResult;
}

std::unordered_set<std::string> FollowsClause::processMapToSetFromSecond(std::unordered_map<std::string, std::unordered_set<std::string>> results) {
    std::unordered_set<std::string> processedResult;
    for (auto entry : results) {
        std::unordered_set<std::string> valuesInRow = entry.second;
        processedResult.insert(valuesInRow.begin(), valuesInRow.end());
    }
    return processedResult;
}

RawResult FollowsClause::evaluateSynonymSynonym() {
    DesignEntity leftType = synonymToDesignEntityMap[left.getValue()];
    DesignEntity rightType = synonymToDesignEntityMap[right.getValue()];
    std::string leftValue = left.getValue();
    std::string rightValue = right.getValue();
    if (leftValue == rightValue) {
        return {false};
    }
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), leftType, rightType);
    std::vector<std::pair<std::string, std::string>> processedMap = FollowsClause::processMapToVectorPair(results); // {{"1", "x"}, {"2", "y"}}
    return {leftValue, rightValue, processedMap};
}

RawResult FollowsClause::evaluateSynonymWildcard() {
    DesignEntity leftType = synonymToDesignEntityMap[left.getValue()];
    DesignEntity rightType = DesignEntity::STMT;
    std::string leftValue = left.getValue();
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), leftType, rightType);
    std::unordered_set<std::string> processedMap = FollowsClause::processMapToSetFromFirst(results);
    return {leftValue, processedMap};
}

RawResult FollowsClause::evaluateSynonymInteger() {
    DesignEntity leftType = synonymToDesignEntityMap[left.getValue()];
    std::string leftValue = left.getValue();
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(getRelationshipType(), leftType, right);
    return {leftValue, results};
}

RawResult FollowsClause::evaluateIntegerSynonym() {
    std::string rightValue = right.getValue();
    DesignEntity rightType = synonymToDesignEntityMap[right.getValue()];
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(getRelationshipType(), left, rightType);
    return {rightValue, results};
}

RawResult FollowsClause::evaluateIntegerWildcard() {
    // Returns boolean
    DesignEntity rightType = DesignEntity::STMT;
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(getRelationshipType(), left, rightType);
    bool booleanResult = !results.empty();
    std::cout << booleanResult << std::endl;
    // {1,2,3} -> boolean result = true
    return {booleanResult};
}

RawResult FollowsClause::evaluateIntegerInteger() {
    // Returns boolean
    bool result = qpsClient.getRelationship(getRelationshipType(), left, right);
    // result = true -> setIsFalseResult(true) -> isFalseResult = false
    return {result};
}

RawResult FollowsClause::evaluateWildcardSynonym() {
    DesignEntity leftType = DesignEntity::STMT;
    DesignEntity rightType = synonymToDesignEntityMap[right.getValue()];
    std::string rightValue = right.getValue();
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), leftType, rightType);
    std::unordered_set<std::string> processedMap = FollowsClause::processMapToSetFromSecond(results);
    return {rightValue, processedMap};
}

RawResult FollowsClause::evaluateWildcardWildcard() {
    DesignEntity stmtType = DesignEntity::STMT;
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), stmtType, stmtType);
    bool booleanResult = !results.empty();
    return {booleanResult};
}

RawResult FollowsClause::evaluateWildcardInteger() {
    DesignEntity leftType = DesignEntity::STMT;
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(getRelationshipType(), leftType, right);
    bool booleanResult = !results.empty();
    return {booleanResult};
}


