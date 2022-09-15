#include "RawResult.h"
#include "vector"
#include "string"
#include "iostream"
#include <map>
#include <initializer_list>

RawResult::RawResult() : resultsList({}), isFalseResult(false), isBooleanResult(true), synonymsList({}) {}

RawResult::RawResult(bool pkbBooleanResult) : resultsList({}), isBooleanResult(true), synonymsList({}) {
    setIsFalseResult(pkbBooleanResult);
};

RawResult::RawResult(const std::string& synonym, const std::unordered_set<std::string>& results) {
    if (results.empty()) {
        setIsFalseResultToTrue();
    }
    synonymsList.emplace_back(synonym);
    for (auto singleResult : results) {
        // {{x}, {y}, {z}}
        std::vector<std::string> resultSublist = {singleResult};
        resultsList.emplace_back(resultSublist);
    }
    setIsBooleanResultToFalse();
}

RawResult::RawResult(std::string leftSynonym, std::string rightSynonym, std::vector<std::pair<std::string, std::string>> results) {
    if (results.empty()) {
        setIsFalseResultToTrue();
    }
    synonymsList.emplace_back(leftSynonym);
    synonymsList.emplace_back(rightSynonym);
    for (auto pairResult : results) {
        // {{1, x}, {3, y}, {5, z}}
        std::vector<std::string> resultSublist = {pairResult.first, pairResult.second};
        resultsList.emplace_back(resultSublist);
    }
    setIsBooleanResultToFalse();
}

std::unordered_set<std::string> RawResult::getResultsToBePopulated(std::string selectSynonym) {
    std::unordered_set<std::string> result({});
    auto iterator = std::find(synonymsList.begin(), synonymsList.end(), selectSynonym);
    if (iterator != synonymsList.cend()) {
        int index = std::distance(synonymsList.begin(), iterator);
        for (auto row : resultsList) {
            result.insert(row[index]);
        }
    }
    return result;
}

void RawResult::filterBySelectSynonym(std::string selectSynonym) {
    std::vector<std::string> newSynonymsList;
    std::vector<std::vector<std::string>> newResultsList;

    std::vector<size_t> indexes; // Index of select synonym
    for (size_t i = 0; i < synonymsList.size(); i++) {
        std::string currentSynonym = synonymsList.at(i);
        if (currentSynonym == selectSynonym) {
            indexes.emplace_back(i);
            newSynonymsList.emplace_back(currentSynonym);
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

// Find common synonyms and merge resultsLists
void RawResult::combineResult(RawResult nextResult) {
    if (isFalseResult) {
        return;
    }

    if (nextResult.isFalseResult || nextResult.isEmptyResult()) {
        setIsFalseResultToTrue();
    }
    // find common synonyms, maximum 2 since there are only 2 parameters / pattern takes in 1 synonym at max
    // {x, y} {s, x} -> {0, 1} index pair -> go to resultsList
    std::map<std::string, size_t> synonymToIndexMap = RawResult::computeSynonymToIndexMap();
    std::vector<std::pair<size_t, size_t>> commonSynonymsIndexPairs = RawResult::findCommonSynonymsIndexPairs(
            nextResult.synonymsList, synonymToIndexMap);

    // Combining clause groups and combining within clause groups
    if (!commonSynonymsIndexPairs.empty()) {
        std::vector<size_t> notCommonNextSynonymIndex = RawResult::findNotCommonSynonymsIndex(nextResult.synonymsList, synonymToIndexMap);
        RawResult::joinResultsListWithCommonSynonym(nextResult, commonSynonymsIndexPairs, notCommonNextSynonymIndex);
    } else {
        RawResult::joinResultsListWithNoCommonSynonym(nextResult);
    }

    // Joining two results with common synonyms but there are no common results
    if (isEmptyResult() && !synonymsList.empty()) {
        setIsFalseResultToTrue();
    }
}

void RawResult::joinResultsListWithNoCommonSynonym(RawResult nextResult) {
    std::vector<std::vector<std::string>> newResultsList;
    std::vector<std::vector<std::string>> nextResultsList = nextResult.resultsList;
    synonymsList.insert(synonymsList.end(), nextResult.synonymsList.begin(), nextResult.synonymsList.end());

    if (nextResult.isEmptyResult()) {
        return;
    }

    if (isEmptyResult()) {
        resultsList = std::move(nextResult.resultsList);
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

void RawResult::joinResultsListWithCommonSynonym(RawResult nextResult, std::vector<std::pair<size_t, size_t>> commonSynonymsIndexPairs, std::vector<size_t> notCommonNextSynonymIndex) {
    for (size_t i : notCommonNextSynonymIndex) {
        synonymsList.emplace_back(nextResult.synonymsList.at(i));
    }
    // Joining Results List
    std::vector<std::vector<std::string>> newResultsList;
    std::vector<std::vector<std::string>> nextResultsList = nextResult.resultsList;
    for (auto resultSublist : resultsList) {
        for (auto nextResultSublist : nextResultsList) {
            bool isCommon = true;
            for (auto commonIndexPair : commonSynonymsIndexPairs) {
                std::string resultSublistValue = resultSublist.at(commonIndexPair.first);
                std::string nextResultSublistValue = nextResultSublist.at(commonIndexPair.second);
                if (resultSublistValue != nextResultSublistValue) {
                    isCommon = false;
                    break;
                }
            }

            if (isCommon) {
                auto newResultSublist = resultSublist;
                for (auto i : notCommonNextSynonymIndex) {
                    newResultSublist.emplace_back(nextResultSublist.at(i));
                }
                newResultsList.emplace_back(newResultSublist);
            }
        }
    }
    resultsList = std::move(newResultsList);
}

std::map<std::string, size_t> RawResult::computeSynonymToIndexMap() {
    std::map<std::string, size_t> synonymToIndexMap;
    for (size_t i = 0; i < synonymsList.size(); i++) {
        synonymToIndexMap.emplace(synonymsList.at(i), i);
    }
    return synonymToIndexMap;
}


std::vector<size_t> RawResult::findNotCommonSynonymsIndex(std::vector<std::string> nextSynonymsList, std::map<std::string, size_t> synonymToIndexMap) {
    std::vector<size_t> nextSynonymsIndexes;
    for (size_t i = 0; i < nextSynonymsList.size(); i++) {
        auto it = synonymToIndexMap.find(nextSynonymsList.at(i));
        // No common synonyms
        if (it == synonymToIndexMap.end()) {
            nextSynonymsIndexes.emplace_back(i);
        }
    }
    return nextSynonymsIndexes;
}

std::vector<std::pair<size_t, size_t>> RawResult::findCommonSynonymsIndexPairs(std::vector<std::string> nextSynonymsList, std::map<std::string, size_t> synonymToIndexMap) {
    std::vector<std::pair<size_t, size_t>> indexPairs; // Common synonyms between both raw results
    for (size_t i = 0; i < nextSynonymsList.size(); i++) {
        auto it = synonymToIndexMap.find(nextSynonymsList.at(i));
        // Common synonym
        if (it != synonymToIndexMap.end()) {
            indexPairs.emplace_back(it -> second, i);
        }
    }
    return indexPairs;
}

bool RawResult::getIsFalseResult() {
    return isFalseResult;
}

bool RawResult::isEmptyResult() {
    return resultsList.empty();
}

void RawResult::setIsFalseResult(bool pkbBooleanResult) {
    isFalseResult = !pkbBooleanResult;
}

void RawResult::setIsFalseResultToTrue() {
    isFalseResult = true;
}

int RawResult::getSynonymCount() {
    return synonymsList.size();
}

bool RawResult::getIsBooleanResult() {
    return isBooleanResult;
}

void RawResult::setIsBooleanResultToFalse() {
    isBooleanResult = false;
}

bool RawResult::getIsSynonymResult() {
    return isSynonymResult;
}

void RawResult::setIsSynonymResult() {
    isSynonymResult = true;
}






