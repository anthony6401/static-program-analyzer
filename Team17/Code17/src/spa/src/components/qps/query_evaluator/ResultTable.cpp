#include "ResultTable.h"
#include "vector"
#include "string"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "./factory/clauses/select/SelectAttributeClause.h"
#include <unordered_map>
#include <initializer_list>
#include "components/qps/query_evaluator/factory/utils/HashFunction.h"

ResultTable::ResultTable() : resultsList({}), isFalseResult(false), synonymsList({}) {}

ResultTable::ResultTable(bool result) : resultsList({}), synonymsList({}) {
    setIsFalseResult(result);
};

ResultTable::ResultTable(const std::string& synonym, const std::unordered_set<std::string>& results) {
    if (results.empty()) {
        setIsFalseResultToTrue();
    }

    synonymsList.emplace_back(synonym);

    for (const auto& singleResult : results) {
        std::vector<std::string> resultSublist = {singleResult};
        resultsList.emplace_back(resultSublist);
    }
}

ResultTable::ResultTable(const std::string& leftSynonym, const std::string& rightSynonym, const std::vector<std::pair<std::string, std::string>>& results) {
    if (results.empty()) {
        setIsFalseResultToTrue();
    }

    synonymsList.emplace_back(leftSynonym);
    synonymsList.emplace_back(rightSynonym);

    for (const auto& pairResult : results) {
        std::vector<std::string> resultSublist = {pairResult.first, pairResult.second};
        resultsList.emplace_back(resultSublist);
    }
}

ResultTable::ResultTable(const std::string& leftSynonym, const std::string& rightSynonym, const std::unordered_set<std::pair<std::string, std::string>, hashFunction>& results) {
    if (results.empty()) {
        setIsFalseResultToTrue();
    }
    synonymsList.emplace_back(leftSynonym);
    synonymsList.emplace_back(rightSynonym);

    for (const auto& pairResult : results) {
        std::vector<std::string> resultSublist = {pairResult.first, pairResult.second};
        resultsList.emplace_back(resultSublist);
    }
}

bool ResultTable::getIsFalseResult() const {
    return isFalseResult;
}

bool ResultTable::isEmptyResult() const {
    return resultsList.empty();
}

void ResultTable::setIsFalseResult(bool result) {
    isFalseResult = !result;
}

void ResultTable::setIsFalseResultToTrue() {
    isFalseResult = true;
}

void ResultTable::setHasAlternativeAttributeNameToTrue() {
    hasAlternativeAttributeName = true;
}

bool ResultTable::getHasAlternativeAttributeName() const {
    return hasAlternativeAttributeName;
}

std::unordered_set<std::string> ResultTable::getSynonymResultsToBePopulated(const std::string& selectSynonym) {
    std::unordered_set<std::string> result({});
    auto iterator = std::find(synonymsList.begin(), synonymsList.end(), selectSynonym);
    if (iterator != synonymsList.cend()) {
        size_t indexOfSynonym = std::distance(synonymsList.begin(), iterator);
        for (auto resultSublist : resultsList) {
            result.insert(resultSublist[indexOfSynonym]);
        }
    }
    return result;
}

void ResultTable::tupleIteratorResultsHandler(std::vector<TokenObject> tuple, size_t index, std::vector<std::string> &resultSublist, std::vector<std::string> &newResultSublist, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient) {
    TokenType tupleObjectType = tuple[index].getTokenType();
    std::string tupleObjectValue = tuple[index].getValue();
    auto iterator = std::find(synonymsList.begin(), synonymsList.end(), tupleObjectValue);
    size_t indexOfSynonym = std::distance(synonymsList.begin(), iterator);
    if (tupleObjectType == TokenType::NAME) {
        newResultSublist.push_back(resultSublist[indexOfSynonym]);
    }

    if (tupleObjectType == TokenType::ATTRIBUTE_SYNONYM) {
        std::string attributeName = tuple[index + 1].getValue();
        DesignEntity returnType = synonymToDesignEntityMap[tuple[index].getValue()];
        if (SelectAttributeClause::checkIsAlternateAttributeName(returnType, attributeName)) {
            DesignEntity entityType = synonymToDesignEntityMap[tupleObjectValue];
            std::string statementNumber = resultSublist[indexOfSynonym];
            std::string alternative = qpsClient.getStatementMapping(statementNumber, entityType);
            newResultSublist.push_back(alternative);
        } else {
            newResultSublist.push_back(resultSublist[indexOfSynonym]);
        }
    }
}

std::unordered_set<std::string> ResultTable::getTupleResultsToBePopulated(std::vector<TokenObject> tuple, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient) {
    std::unordered_set<std::string> result({});
    for (auto &resultSublist : resultsList) {
        std::vector<std::string> newResultSublist;
        for (size_t i = 0; i < tuple.size(); i++) {
            tupleIteratorResultsHandler(tuple, i, resultSublist, newResultSublist, synonymToDesignEntityMap, qpsClient);
        }

        result.insert(ResultTable::formTupleResultString(newResultSublist));
    }

    return result;
}


std::string ResultTable::formTupleResultString(std::vector<std::string> newResultsList) {
    std::string tupleResultString;
    size_t newResultsListSize = newResultsList.size();
    for (size_t i = 0; i < newResultsListSize; ++i) {
        std::string delimiter = i != newResultsListSize - 1 ? " " : "";
        tupleResultString += newResultsList[i] + delimiter;
    }
    return tupleResultString;
}

void ResultTable::filterBySelectSynonym(std::set<std::string> &&synonyms) {
    std::vector<std::string> newSynonymsList;
    std::vector<std::vector<std::string>> newResultsList;

    std::vector<size_t> indexes;
    for (size_t i = 0; i < synonymsList.size(); i++) {
        if (synonyms.find(synonymsList.at(i))!=synonyms.end()) {
            indexes.emplace_back(i);
            newSynonymsList.emplace_back(synonymsList.at(i));
        }
    }
    synonymsList = std::move(newSynonymsList);

    for (auto resultsSublist : resultsList) {
        std::vector<std::string> newResultSublist;
        for (size_t i : indexes) {
            newResultSublist.emplace_back(resultsSublist.at(i));
        }
        newResultsList.emplace_back(newResultSublist);
    }
    resultsList = std::move(newResultsList);
}

void ResultTable::updateHasCommonAttributeName(ResultTable &nextResult) {
    if (nextResult.getHasAlternativeAttributeName()) {
        setHasAlternativeAttributeNameToTrue();
    }
}


void ResultTable::combineResult(ResultTable &nextResult) {
    ResultTable::updateHasCommonAttributeName(nextResult);
    if (isFalseResult) {
        return;
    } else {
        if (nextResult.isFalseResult) {
            setIsFalseResultToTrue();
            return;
        }

        std::map<std::string, size_t> synonymToIndexMap = ResultTable::computeSynonymToIndexMap();
        std::vector<std::pair<size_t, size_t>> commonSynonymsIndexPairs = ResultTable::findCommonSynonymsIndexPairs(
                nextResult.synonymsList, synonymToIndexMap);

        if (!commonSynonymsIndexPairs.empty()) {
            std::vector<size_t> notCommonNextSynonymIndex = ResultTable::findNotCommonSynonymsIndex(nextResult.synonymsList, synonymToIndexMap);
            ResultTable::joinResultsListWithCommonSynonym(nextResult, commonSynonymsIndexPairs, notCommonNextSynonymIndex);
        } else {
            ResultTable::joinResultsListWithNoCommonSynonym(nextResult);
        }

        if (isEmptyResult() && !synonymsList.empty()) {
            setIsFalseResultToTrue();
        }
    }
}

std::vector<size_t> ResultTable::findNotCommonSynonymsIndex(std::vector<std::string> nextSynonymsList, std::map<std::string, size_t> synonymToIndexMap) {
    std::vector<size_t> nextSynonymsIndexes;
    for (size_t i = 0; i < nextSynonymsList.size(); i++) {
        auto it = synonymToIndexMap.find(nextSynonymsList.at(i));
        if (it == synonymToIndexMap.end()) {
            nextSynonymsIndexes.emplace_back(i);
        }
    }
    return nextSynonymsIndexes;
}

void ResultTable::joinResultsListWithNoCommonSynonym(ResultTable nextResult) {
    std::vector<std::vector<std::string>> newResultsList;
    std::vector<std::vector<std::string>> nextResultsList = nextResult.resultsList;
    synonymsList.insert(synonymsList.end(), nextResult.synonymsList.begin(), nextResult.synonymsList.end());

    if (isEmptyResult()) {
        resultsList = std::move(nextResult.resultsList);
        return;
    }

    if (nextResult.isEmptyResult()) {
        return;
    }

    for (auto resultSublist : resultsList) {
        for (auto nextResultSublist : nextResultsList) {
            std::vector<std::string> newSublist;
            newSublist.reserve(resultSublist.size() + nextResultSublist.size());
            newSublist.insert(newSublist.end(), resultSublist.begin(), resultSublist.end());
            newSublist.insert(newSublist.end(), nextResultSublist.begin(), nextResultSublist.end());
            newResultsList.emplace_back(newSublist);
        }
    }
    resultsList = std::move(newResultsList);

}

void ResultTable::updateResultsListsFromCommonSynonymsIndexPairs(std::vector<std::vector<std::string>> &nextResultsList, std::vector<std::string> &resultSublist,
                                                                 std::vector<std::string> &nextResultSublist, const std::vector<std::pair<size_t, size_t>>& commonSynonymsIndexPairs, bool &isCommon) {
    for (auto commonIndexPair : commonSynonymsIndexPairs) {
        std::string resultSublistValue = resultSublist.at(commonIndexPair.first);
        std::string nextResultSublistValue = nextResultSublist.at(commonIndexPair.second);
        if (resultSublistValue != nextResultSublistValue) {
            isCommon = false;
            break;
        }
    }
}

void ResultTable::joinResultSublistListWithCommonSynonym(std::vector<std::vector<std::string>> &nextResultsList, std::vector<std::vector<std::string>> &newResultsList,
                                                         const std::vector<std::pair<size_t, size_t>>& commonSynonymsIndexPairs, std::vector<std::string> &resultSublist, const std::vector<size_t>& notCommonNextSynonymIndex) {
    for (auto nextResultSublist : nextResultsList) {
        bool isCommon = true;
        updateResultsListsFromCommonSynonymsIndexPairs(nextResultsList, resultSublist, nextResultSublist, commonSynonymsIndexPairs, isCommon);
        if (isCommon) {
            auto newResultSublist = resultSublist;
            for (auto i : notCommonNextSynonymIndex) {
                newResultSublist.emplace_back(nextResultSublist.at(i));
            }
            newResultsList.emplace_back(newResultSublist);
        }
    }
}

void ResultTable::joinResultsListWithCommonSynonym(ResultTable nextResult, const std::vector<std::pair<size_t, size_t>>& commonSynonymsIndexPairs, const std::vector<size_t>& notCommonNextSynonymIndex) {
    for (size_t i : notCommonNextSynonymIndex) {
        synonymsList.emplace_back(nextResult.synonymsList.at(i));
    }

    std::vector<std::vector<std::string>> newResultsList;
    std::vector<std::vector<std::string>> nextResultsList = nextResult.resultsList;
    for (auto resultSublist : resultsList) {
        joinResultSublistListWithCommonSynonym(nextResultsList, newResultsList, commonSynonymsIndexPairs, resultSublist, notCommonNextSynonymIndex);
    }
    resultsList = std::move(newResultsList);
}

std::map<std::string, size_t> ResultTable::computeSynonymToIndexMap() {
    std::map<std::string, size_t> synonymToIndexMap;
    for (size_t i = 0; i < synonymsList.size(); i++) {
        synonymToIndexMap.emplace(synonymsList.at(i), i);
    }
    return synonymToIndexMap;
}


std::vector<std::pair<size_t, size_t>> ResultTable::findCommonSynonymsIndexPairs(std::vector<std::string> nextSynonymsList, std::map<std::string, size_t> synonymToIndexMap) {
    std::vector<std::pair<size_t, size_t>> indexPairs;
    for (size_t i = 0; i < nextSynonymsList.size(); i++) {
        auto it = synonymToIndexMap.find(nextSynonymsList.at(i));
        if (it != synonymToIndexMap.end()) {
            indexPairs.emplace_back(it -> second, i);
        }
    }
    return indexPairs;
}

