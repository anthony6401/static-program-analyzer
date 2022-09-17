#include "FollowsTClause.h"
#include "iostream"

FollowsTClause::FollowsTClause(TokenObject left, TokenObject right, Select synonym,
                             std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                             QPSClient qpsClient) : left(left), right(right), synonym(synonym),
                                                    synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {}

RawResult FollowsTClause::evaluateClause() {
    TokenType leftType = left.getTokenType();
    TokenType rightType = right.getTokenType();
    if (leftType == TokenType::NAME && rightType == TokenType::NAME) {
        return FollowsTClause::evaluateSynonymSynonym();
    } else if (leftType == TokenType::NAME && rightType == TokenType::WILDCARD) {
        return FollowsTClause::evaluateSynonymWildcard();
    } else if (leftType == TokenType::NAME && rightType == TokenType::INTEGER) {
        return FollowsTClause::evaluateSynonymInteger();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::NAME) {
        return FollowsTClause::evaluateIntegerSynonym();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::WILDCARD) {
        return FollowsTClause::evaluateIntegerWildcard();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::INTEGER) {
        return FollowsTClause::evaluateIntegerInteger();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::NAME) {
        return FollowsTClause::evaluateWildcardSynonym();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::WILDCARD) {
        return FollowsTClause::evaluateWildcardWildcard();
    } else if (leftType == TokenType::WILDCARD && rightType == TokenType::INTEGER) {
        return FollowsTClause::evaluateWildcardInteger();
    } else {
        return {};
    }
}

size_t FollowsTClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (left.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    if (right.getTokenType() == TokenType::NAME) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}

std::set<std::string> FollowsTClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (left.getTokenType() == TokenType::NAME) {
        synonyms.emplace(left.getValue());
    }
    if (right.getTokenType() == TokenType::NAME) {
        synonyms.emplace(right.getValue());
    }
    return synonyms;
}

RelationshipType FollowsTClause::getRelationshipType() {
    return RelationshipType::FOLLOWS_T;
}

std::vector<std::pair<std::string, std::string>> FollowsTClause::processMapToVectorPair(std::unordered_map<std::string, std::unordered_set<std::string>> results) {
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

std::unordered_set<std::string> FollowsTClause::processMapToSet(std::unordered_map<std::string, std::unordered_set<std::string>> results) {
    std::unordered_set<std::string> processedResult;
    for (auto entry : results) {
        std::string firstSynonym = entry.first;
        processedResult.insert(firstSynonym);
    }
    return processedResult;
}

RawResult FollowsTClause::evaluateSynonymSynonym() {
    DesignEntity leftType = synonymToDesignEntityMap[left.getValue()];
    DesignEntity rightType = synonymToDesignEntityMap[right.getValue()];
    std::string leftValue = left.getValue();
    std::string rightValue = right.getValue();
    if (leftValue == rightValue) {
        return {false};
    }
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), leftType, rightType);
    std::vector<std::pair<std::string, std::string>> processedMap = FollowsTClause::processMapToVectorPair(results); // {{"1", "x"}, {"2", "y"}}
    return {leftValue, rightValue, processedMap};
}

RawResult FollowsTClause::evaluateSynonymWildcard() {
    DesignEntity leftType = synonymToDesignEntityMap[left.getValue()];
    DesignEntity rightType = DesignEntity::STMT;
    std::string leftValue = left.getValue();
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), leftType, rightType);
    std::unordered_set<std::string> processedMap = FollowsTClause::processMapToSet(results);
    return {leftValue, processedMap};
}

RawResult FollowsTClause::evaluateSynonymInteger() {
    DesignEntity leftType = synonymToDesignEntityMap[left.getValue()];
    std::string leftValue = left.getValue();
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(getRelationshipType(), leftType, right);
    return {leftValue, results};
}

RawResult FollowsTClause::evaluateIntegerSynonym() {
    std::string rightValue = right.getValue();
    DesignEntity rightType = synonymToDesignEntityMap[right.getValue()];
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(getRelationshipType(), left, rightType);
    return {rightValue, results};
}

RawResult FollowsTClause::evaluateIntegerWildcard() {
    // Returns boolean
    DesignEntity rightType = DesignEntity::STMT;
    std::unordered_set<std::string> results = qpsClient.getRelationshipByFirst(getRelationshipType(), left, rightType);
    bool booleanResult = !results.empty();
    // {1,2,3} -> boolean result = true
    return {booleanResult};
}

RawResult FollowsTClause::evaluateIntegerInteger() {
    // Returns boolean
    bool result = qpsClient.getRelationship(getRelationshipType(), left, right);
    // result = true -> setIsFalseResult(true) -> isFalseResult = false
    return {result};
}

RawResult FollowsTClause::evaluateWildcardSynonym() {
    DesignEntity leftType = DesignEntity::STMT;
    DesignEntity rightType = synonymToDesignEntityMap[right.getValue()];
    std::string rightValue = right.getValue();
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), leftType, rightType);
    std::unordered_set<std::string> processedMap = FollowsTClause::processMapToSet(results);
    return {rightValue, processedMap};
}

RawResult FollowsTClause::evaluateWildcardWildcard() {
    DesignEntity stmtType = DesignEntity::STMT;
    std::unordered_map<std::string, std::unordered_set<std::string>> results = qpsClient.getAllRelationship(getRelationshipType(), stmtType, stmtType);
    bool booleanResult = !results.empty();
    return {booleanResult};
}

RawResult FollowsTClause::evaluateWildcardInteger() {
    DesignEntity leftType = DesignEntity::STMT;
    std::unordered_set<std::string> results = qpsClient.getRelationshipBySecond(getRelationshipType(), leftType, right);
    bool booleanResult = !results.empty();
    return {booleanResult};
}