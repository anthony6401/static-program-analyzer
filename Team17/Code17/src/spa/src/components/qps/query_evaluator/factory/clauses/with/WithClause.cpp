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
    } else if (leftType == TokenType::ATTRIBUTE && rightType == TokenType::INTEGER) {
        return WithClause::evaluateAttributeInteger();
    } else if (leftType == TokenType::ATTRIBUTE && rightType == TokenType::NAME_WITH_QUOTATION) {
        return WithClause::evaluateAttributeNameQuotes();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::ATTRIBUTE) {
        return WithClause::evaluateIntegerAttribute();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::ATTRIBUTE) {
        return WithClause::evaluateNameQuotesAttribute();
    } else {
        return WithClause::evaluateIntegerOrNameQuotes();
    }
}

ResultTable WithClause::evaluateIntegerOrNameQuotes() {
    std::string leftValue = left.front().getValue();
    std::string rightValue = right.front().getValue();
    if (leftValue == rightValue) {
        return {true};
    } else {
        return {false};
    }
}


ResultTable WithClause::evaluateNameQuotesAttribute() {
    ResultTable resultTable;
    std::string attributeSynonym = right.front().getValue();
    std::string nameQuotesValue = left.front().getValue();
    DesignEntity attributeDesignEntityType = synonymToDesignEntityMap[attributeSynonym];
    std::string attributeName = right.back().getValue();
    bool isAlternativeAttribute = SelectAttributeClause::checkIsAlternateAttributeName(attributeDesignEntityType,
                                                                                       attributeName);

    if (isAlternativeAttribute) {
        // Call PKB API to get pkb statement by name
        std::unordered_set<std::string> attributeResult;
        if (attributeResult.empty()) {
            resultTable.setIsFalseResultToTrue();
            return resultTable;
        } else {
            std::unordered_set<std::string> results;
            results.insert(nameQuotesValue);
            return {attributeSynonym, results};
        }
    } else {
        std::unordered_set<std::string> attributeResult = qpsClient.getAllEntity(attributeDesignEntityType);
        if (attributeResult.find(nameQuotesValue) == attributeResult.end()) {
            resultTable.setIsFalseResultToTrue();
            return resultTable;
        } else {
            std::unordered_set<std::string> results;
            results.insert(nameQuotesValue);
            return {attributeSynonym, results};
        }
    }
}


ResultTable WithClause::evaluateIntegerAttribute() {
    ResultTable resultTable;
    std::string attributeSynonym = right.front().getValue();
    std::string integerValue = left.front().getValue();
    DesignEntity attributeDesignEntityType = synonymToDesignEntityMap[attributeSynonym];
    std::unordered_set<std::string> attributeResult = qpsClient.getAllEntity(attributeDesignEntityType);
    if (attributeResult.find(integerValue) == attributeResult.end()) {
        resultTable.setIsFalseResultToTrue();
        return resultTable;
    } else {
        std::unordered_set<std::string> results;
        results.insert(integerValue);
        return {attributeSynonym, results};
    }
}

ResultTable WithClause::evaluateAttributeNameQuotes() {
    ResultTable resultTable;
    std::string attributeSynonym = left.front().getValue();
    std::string nameQuotesValue = right.front().getValue();
    DesignEntity attributeDesignEntityType = synonymToDesignEntityMap[attributeSynonym];
    std::string attributeName = left.back().getValue();
    bool isAlternativeAttribute = SelectAttributeClause::checkIsAlternateAttributeName(attributeDesignEntityType, attributeName);

    if (isAlternativeAttribute) {
        // Call PKB API to get pkb statement by name
        std::unordered_set<std::string> attributeResult;
        if (attributeResult.empty()) {
            resultTable.setIsFalseResultToTrue();
            return resultTable;
        } else {
            std::unordered_set<std::string> results;
            results.insert(nameQuotesValue);
            return {attributeSynonym, results};
        }
    } else {
        std::unordered_set<std::string> attributeResult = qpsClient.getAllEntity(attributeDesignEntityType);
        if (attributeResult.find(nameQuotesValue) == attributeResult.end()) {
            resultTable.setIsFalseResultToTrue();
            return resultTable;
        } else {
            std::unordered_set<std::string> results;
            results.insert(nameQuotesValue);
            return {attributeSynonym, results};
        }
    }
}

ResultTable WithClause::evaluateAttributeInteger() {
    ResultTable resultTable;
    std::string attributeSynonym = left.front().getValue();
    std::string integerValue = right.front().getValue();
    DesignEntity attributeDesignEntityType = synonymToDesignEntityMap[attributeSynonym];
    std::unordered_set<std::string> attributeResult = qpsClient.getAllEntity(attributeDesignEntityType);
    if (attributeResult.find(integerValue) == attributeResult.end()) {
        resultTable.setIsFalseResultToTrue();
        return resultTable;
    } else {
        std::unordered_set<std::string> results;
        results.insert(integerValue);
        return {attributeSynonym, results};
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
