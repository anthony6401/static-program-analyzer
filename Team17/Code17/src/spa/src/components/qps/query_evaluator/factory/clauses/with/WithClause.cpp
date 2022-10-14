#include "WithClause.h"

#include <utility>
#include "../select/SelectAttributeClause.h"
#include "components/qps/query_evaluator/factory/utils/HashFunction.h"
#include "iostream"

WithClause::WithClause(std::vector<TokenObject> left,
                       std::vector<TokenObject> right,
                       std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient) : left(std::move(left)), right(std::move(right)), synonymToDesignEntityMap(std::move(synonymToDesignEntityMap)),
                                                                                                                      qpsClient(qpsClient) {}


ResultTable WithClause::evaluateClause() {
    TokenType leftType = left.front().getTokenType();
    TokenType rightType = right.front().getTokenType();
    if (leftType == TokenType::ATTRIBUTE_SYNONYM && rightType == TokenType::ATTRIBUTE_SYNONYM) {
        return WithClause::evaluateAttributeAttribute();
    } else if (leftType == TokenType::ATTRIBUTE_SYNONYM && rightType == TokenType::INTEGER) {
        return WithClause::evaluateAttributeInteger();
    } else if (leftType == TokenType::ATTRIBUTE_SYNONYM && rightType == TokenType::NAME_WITH_QUOTATION) {
        return WithClause::evaluateAttributeNameQuotes();
    } else if (leftType == TokenType::INTEGER && rightType == TokenType::ATTRIBUTE_SYNONYM) {
        return WithClause::evaluateIntegerAttribute();
    } else if (leftType == TokenType::NAME_WITH_QUOTATION && rightType == TokenType::ATTRIBUTE_SYNONYM) {
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
        std::unordered_set<std::string> attributeResult = qpsClient.getStatementByName(nameQuotesValue, attributeDesignEntityType);
        if (attributeResult.empty()) {
            resultTable.setIsFalseResultToTrue();
            return resultTable;
        } else {
            return {attributeSynonym, attributeResult};
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
        std::unordered_set<std::string> attributeResult = qpsClient.getStatementByName(nameQuotesValue, attributeDesignEntityType);;
        if (attributeResult.empty()) {
            resultTable.setIsFalseResultToTrue();
            return resultTable;
        } else {
            return {attributeSynonym, attributeResult};
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
        pairResult = WithClause::leftAndRightAlternativeAttributeResultsHandler(leftDesignEntityType, rightDesignEntityType);

    } else if (isLeftAlternativeAttribute) {
        pairResult = WithClause::leftAlternativeAttributeResultsHandler(leftDesignEntityType, rightDesignEntityType);
    } else if (isRightAlternativeAttribute) {
        pairResult = WithClause::rightAlternativeAttributeResultsHandler(leftDesignEntityType, rightDesignEntityType);
    } else {
        std::unordered_set<std::string> rightResult = qpsClient.getAllEntity(rightDesignEntityType);
        std::unordered_set<std::string> leftResult = qpsClient.getAllEntity(leftDesignEntityType);
        pairResult = WithClause::findCommonAttributeStatements(leftResult, rightResult);
    }

    if (pairResult.empty()) {
        ResultTable table;
        table.setIsFalseResultToTrue();
        return table;
    }

    return {leftSynonym, rightSynonym, pairResult};
}

std::unordered_set<std::pair<std::string, std::string>, hashFunction> WithClause::rightAlternativeAttributeResultsHandler(DesignEntity leftDesignEntityType, DesignEntity rightDesignEntityType) {
    std::unordered_set<std::pair<std::string, std::string>, hashFunction> pairResult;
    std::unordered_set<std::string> rightNameResult = qpsClient.getAllName(rightDesignEntityType);;
    std::unordered_set<std::string> leftResult = qpsClient.getAllEntity(leftDesignEntityType);
    std::unordered_set<std::string> commonAttributeValues = WithClause::findCommonAttributeValues(rightNameResult, leftResult);
    for (auto commonValue : commonAttributeValues) {
        std::unordered_set<std::string> statementFromNameRight = qpsClient.getStatementByName(commonValue, rightDesignEntityType);
        for (const auto& rightStmt : statementFromNameRight) {
            pairResult.insert(std::make_pair(commonValue, rightStmt));
        }
    }

    return pairResult;
}

std::unordered_set<std::pair<std::string, std::string>, hashFunction> WithClause::leftAlternativeAttributeResultsHandler(DesignEntity leftDesignEntityType, DesignEntity rightDesignEntityType) {
    std::unordered_set<std::pair<std::string, std::string>, hashFunction> pairResult;
    std::unordered_set<std::string> leftNameResult = qpsClient.getAllName(leftDesignEntityType);
    std::unordered_set<std::string> rightResult = qpsClient.getAllEntity(rightDesignEntityType);
    std::unordered_set<std::string> commonAttributeValues = WithClause::findCommonAttributeValues(leftNameResult, rightResult);
    for (auto commonValue : commonAttributeValues) {
        std::unordered_set<std::string> statementFromNameLeft = qpsClient.getStatementByName(commonValue, leftDesignEntityType);
        for (const auto& leftStmt : statementFromNameLeft) {
            pairResult.insert(std::make_pair(leftStmt, commonValue));
        }
    }

    return pairResult;
}


std::unordered_set<std::pair<std::string, std::string>, hashFunction> WithClause::leftAndRightAlternativeAttributeResultsHandler(DesignEntity leftDesignEntityType, DesignEntity rightDesignEntityType) {
    std::unordered_set<std::pair<std::string, std::string>, hashFunction> pairResult;
    std::unordered_set<std::string> leftNameResult = qpsClient.getAllName(leftDesignEntityType);
    std::unordered_set<std::string> rightNameResult = qpsClient.getAllName(rightDesignEntityType);
    std::unordered_set<std::string> commonAttributeValues = WithClause::findCommonAttributeValues(leftNameResult, rightNameResult);
    std::unordered_set<std::string> intersectionLeft;
    std::unordered_set<std::string> intersectionRight;
    for (auto commonValue : commonAttributeValues) {
        std::unordered_set<std::string> statementFromNameLeft = qpsClient.getStatementByName(commonValue, leftDesignEntityType);
        std::unordered_set<std::string> statementFromNameRight = qpsClient.getStatementByName(commonValue, rightDesignEntityType);
        intersectionLeft.insert(statementFromNameLeft.begin(), statementFromNameLeft.end());
        intersectionRight.insert(statementFromNameRight.begin(), statementFromNameRight.end());
    }

    auto it1 = intersectionLeft.begin();
    auto it2 = intersectionRight.begin();
    for (; it1 != intersectionLeft.end() && it2 != intersectionRight.end(); it1++, it2++) {
        pairResult.insert(std::make_pair(*it1, *it2));
    }

    return pairResult;
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

std::unordered_set<std::pair<std::string, std::string>, hashFunction> WithClause::findCommonAttributeStatements(const std::unordered_set<std::string>& leftResult, const std::unordered_set<std::string> rightResult) {
    std::unordered_set<std::pair<std::string, std::string>, hashFunction> commonAttributeStatements;
    for (const auto &statement : leftResult) {
        if (rightResult.find(statement) != rightResult.end()) {
            commonAttributeStatements.insert(std::make_pair(statement, statement));
        }
    }
    return commonAttributeStatements;
}

size_t WithClause::getNumberOfSynonyms() {
    TokenType leftType = left.front().getTokenType();
    TokenType rightType = right.front().getTokenType();
    size_t numberOfSynonyms = 0;
    if (leftType == TokenType::ATTRIBUTE_SYNONYM) {
        numberOfSynonyms++;
    }

    if (rightType == TokenType::ATTRIBUTE_SYNONYM) {
        numberOfSynonyms++;
    }

    return numberOfSynonyms;
}


std::set<std::string> WithClause::getAllSynonyms() {
    TokenType leftType = left.front().getTokenType();
    TokenType rightType = right.front().getTokenType();
    std::set<std::string> synonyms = {};
    if (leftType == TokenType::ATTRIBUTE_SYNONYM) {
        std::string leftSynonym = left.front().getValue();
        synonyms.emplace(leftSynonym);
    }

    if (rightType == TokenType::ATTRIBUTE_SYNONYM) {
        std::string rightSynonym = right.front().getValue();
        synonyms.emplace(rightSynonym);
    }

    return synonyms;
}