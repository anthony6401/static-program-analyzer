#include "WithClause.h"
#include "../select//SelectAttributeClause.h"
#include "components/qps/query_evaluator/factory/utils/HashFunction.h"

WithClause::WithClause(qps::TokenType leftType, qps::TokenType rightType, std::vector<TokenObject> left,
                       std::vector<TokenObject> right,
                       std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient) : leftType(leftType), rightType(rightType), left(left), right(right), synonymToDesignEntityMap(synonymToDesignEntityMap),
                                                                                                                      qpsClient(qpsClient) {}


ResultTable WithClause::evaluateClause() {
    if (leftType == TokenType::ATTRIBUTE && rightType == TokenType::ATTRIBUTE) {
        return WithClause::evaluateAttributeAttribute();
    }
}

ResultTable WithClause::evaluateAttributeAttribute() {
    std::string leftSynonym = left.front().getValue();
    std::string rightSynonym = right.front().getValue();
    DesignEntity leftDesignEntityType = synonymToDesignEntityMap[leftSynonym];
    DesignEntity rightDesignEntityType = synonymToDesignEntityMap[rightSynonym];
    std::string leftAttributeName = left.back().getValue();
    std::string rightAttributeName = right.back().getValue();
    bool isLeftAlternativeAttribute = SelectAttributeClause::checkIsAlternateAttributeName(leftDesignEntityType, leftAttributeName);
    bool isRightAlternativeAttribute = SelectAttributeClause::checkIsAlternateAttributeName(rightDesignEntityType, rightAttributeName);
    std::unordered_set<std::pair<std::string, std::string>, hashFunction> pairResult;

    if (isLeftAlternativeAttribute && isRightAlternativeAttribute) {
        // Call PKB API to get all names
        std::unordered_set<std::string> leftNameResult;
        std::unordered_set<std::string> rightNameResult;
        std::unordered_set<std::string> commonAttributeValues = WithClause::findCommonAttributeValues(leftNameResult, rightNameResult);

        for (auto commonValue : commonAttributeValues) {
            // Call PKB API to get back statement by name
            std::string statementFromNameLeft;
            std::string statementFromNameRight;
            pairResult.insert(std::make_pair(statementFromNameLeft, statementFromNameRight));
        }
    } else if (isLeftAlternativeAttribute) {
        // Call PKB API to get all names
        std::unordered_set<std::string> leftNameResult;
        std::unordered_set<std::string> rightResult = qpsClient.getAllEntity(rightDesignEntityType);
        std::unordered_set<std::string> commonAttributeValues = WithClause::findCommonAttributeValues(leftNameResult, rightResult);
        for (auto commonValue : commonAttributeValues) {
            // Call PKB API to get back statement by name
            std::string statementFromNameLeft;
            for (auto result : rightResult) {
                pairResult.insert(std::make_pair(statementFromNameLeft, result));
            }
        }
    } else if (isRightAlternativeAttribute) {
        // Call PKB API to get all names
        std::unordered_set<std::string> rightNameResult;
        std::unordered_set<std::string> leftResult = qpsClient.getAllEntity(leftDesignEntityType);
        std::unordered_set<std::string> commonAttributeValues = WithClause::findCommonAttributeValues(rightNameResult, leftResult);
        for (auto commonValue : commonAttributeValues) {
            // Call PKB API to get back statement by name
            std::string statementFromNameRight;
            for (auto result : leftResult) {
                pairResult.insert(std::make_pair(result, statementFromNameRight));
            }
        }
    } else {
        std::unordered_set<std::string> rightResult = qpsClient.getAllEntity(rightDesignEntityType);
        std::unordered_set<std::string> leftResult = qpsClient.getAllEntity(leftDesignEntityType);
        pairResult = WithClause::findCommonAttributeStatements(leftResult, rightResult);
    }

    return {leftSynonym, rightSynonym, pairResult};
}

std::unordered_set<std::string> WithClause::findCommonAttributeValues(std::unordered_set<std::string> leftNameResult, std::unordered_set<std::string> rightNameResult) {
    std::unordered_set<std::string> commonAttributeNames;
    for (auto &name : leftNameResult) {
        if (rightNameResult.find(name) != rightNameResult.end()) {
            commonAttributeNames.insert(name);
        }
    }
    return commonAttributeNames;
}

std::unordered_set<std::pair<std::string, std::string>, hashFunction> WithClause::findCommonAttributeStatements(std::unordered_set<std::string> leftResult, std::unordered_set<std::string> rightResult) {
    std::unordered_set<std::pair<std::string, std::string>, hashFunction> commonAttributeStatements;
    for (const auto &statement : leftResult) {
        if (rightResult.find(statement) != rightResult.end()) {
            commonAttributeStatements.insert(std::make_pair(statement, statement));
        }
    }
}

size_t WithClause::getNumberOfSynonyms() {
    size_t numberOfSynonyms = 0;
    if (leftType == TokenType::ATTRIBUTE) {
        numberOfSynonyms++;
    }

    if (rightType == TokenType::ATTRIBUTE) {
        numberOfSynonyms++;
    }
    return numberOfSynonyms;
}


std::set<std::string> WithClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    if (leftType == TokenType::ATTRIBUTE) {
        std::string leftSynonym = left.front().getValue();
        synonyms.emplace(leftSynonym);
    }

    if (rightType == TokenType::ATTRIBUTE) {
        std::string rightSynonym = right.front().getValue();
        synonyms.emplace(rightSynonym);
    }
    return synonyms;
}
