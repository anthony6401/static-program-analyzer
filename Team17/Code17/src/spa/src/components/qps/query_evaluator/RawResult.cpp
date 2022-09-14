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
        resultsList.emplace_back(std::initializer_list<std::string>{singleResult});
    }
    setIsBooleanResult();
}

RawResult::RawResult(std::string leftSynonym, std::string rightSynonym,
                     std::vector<std::pair<std::string, std::string>> results) {
    if (results.empty()) {
        setIsFalseResultToTrue();
    }
    synonymsList.emplace_back(leftSynonym);
    synonymsList.emplace_back(rightSynonym);
    for (auto result : results) {
        // {{1, x}, {3, y}, {5, z}}
        resultsList.emplace_back(std::initializer_list<std::string>{result.first, result.second});
    }
    setIsBooleanResult();
}

std::unordered_set<std::string> RawResult::getResultsToBePopulated(std::string selectSynonym) {
    std::unordered_set<std::string> result({});
    auto itr = std::find(synonymsList.begin(), synonymsList.end(), selectSynonym);
    if (itr!=synonymsList.cend()) {
        int index = std::distance(synonymsList.begin(), itr);
        for (auto row : resultsList) {
            result.insert(row[index]);
        }
    }
    return result;
}

void RawResult::filterBySelectSynonym(std::string selectSynonym) {
    std::vector<std::string> newSynonymsList;
    std::vector<size_t> indexes; // Index of select synonym
    for (size_t i = 0; i < synonymsList.size(); i++) {
        std::string currentSynonym = synonymsList.at(i);
        if (currentSynonym == selectSynonym) {
            indexes.emplace_back(i);
            newSynonymsList.emplace_back(currentSynonym);
        }
    }

    std::vector<std::vector<std::string>> newResultsList;
    for (auto resultsSublist : resultsList) {
        std::vector<std::string> newResultSublist;
        for (size_t i : indexes) {
            newResultSublist.emplace_back(resultsSublist.at(i));
        }
        newResultsList.emplace_back(newResultSublist);
    }
    synonymsList = std::move(newSynonymsList);
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
    std::vector<std::pair<size_t, size_t>> commonSynonymsIndexPairs = RawResult::findCommonSynonymsIndexPairs(
            nextResult.synonymsList);
    // Combining clause groups and combining within clause groups
    if (commonSynonymsIndexPairs.empty()) {
        RawResult::joinResultsListWithNoCommonSynonym(nextResult);
    } else {
        RawResult::joinResultsListWithCommonSynonym(nextResult, commonSynonymsIndexPairs);
    }

    // Merging two tables with common attributes but there are no common results
    if (isEmptyResult() && !synonymsList.empty()) {
        setIsFalseResultToTrue();
    }
}

void RawResult::joinResultsListWithNoCommonSynonym(RawResult nextResult) {
    synonymsList.insert(synonymsList.end(), nextResult.synonymsList.begin(), nextResult.synonymsList.end());
    if (nextResult.isEmptyResult()) {
        return;
    }

    if (isEmptyResult()) {
        resultsList = std::move(nextResult.resultsList);
        return;
    }

    std::vector<std::vector<std::string>> newResultsList;
    for (auto resultPair : resultsList) {
        for (auto nextResultPair : nextResult.resultsList) {
            auto newPair = resultPair;
            newPair.reserve(resultPair.size() + nextResultPair.size());
            newPair.insert(newPair.end(), nextResultPair.begin(), nextResultPair.end());
            newResultsList.emplace_back(newPair);
        }
    }
    resultsList = std::move(newResultsList);
}

void RawResult::joinResultsListWithCommonSynonym(RawResult nextResult, std::vector<std::pair<size_t, size_t>> commonSynonymsIndexPairs) {
    std::vector<size_t> notCommonNextSynonymIndex = RawResult::findNotCommonSynonymsIndex(nextResult.synonymsList);
    for (size_t i : notCommonNextSynonymIndex) {
        synonymsList.emplace_back(nextResult.synonymsList.at(i));
    }
    // Joining Results List
    std::vector<std::vector<std::string>> newResultsList;
    for (auto resultPair : resultsList) { // v is of maximum of size 2
        for (auto nextResultPair : nextResult.resultsList) {
            bool isMatch = true;
            for (auto commonIndexPair : commonSynonymsIndexPairs) {
                if (resultPair.at(commonIndexPair.first)!=nextResultPair.at(commonIndexPair.second)) {
                    isMatch = false;
                    break;
                }
            }

            if (isMatch) {
                auto newPair = resultPair;
                for (auto i : notCommonNextSynonymIndex) {
                    newPair.emplace_back(nextResultPair.at(i));
                }
                newResultsList.emplace_back(newPair);
            }
        }
    }
    resultsList = std::move(newResultsList);
}

std::vector<size_t> RawResult::findNotCommonSynonymsIndex(std::vector<std::string> nextSynonymsList) {
    std::vector<size_t> nextSynonymsIndexes;
    std::map<std::string, size_t> synonymToIndexMap;

    for (size_t i = 0; i < synonymsList.size(); ++i) {
        synonymToIndexMap.emplace(synonymsList.at(i), i);
    }
    for (size_t i = 0; i < nextSynonymsList.size(); ++i) {
        auto it = synonymToIndexMap.find(nextSynonymsList.at(i));
        if (it==synonymToIndexMap.end()) {
            nextSynonymsIndexes.emplace_back(i);
        }
    }
    return nextSynonymsIndexes;
}

std::vector<std::pair<size_t, size_t>> RawResult::findCommonSynonymsIndexPairs(std::vector<std::string> nextSynonymsList) {
    std::vector<std::pair<size_t, size_t>> indexPairs;
    std::map<std::string, size_t> synonymToIndexMap;
    // Create synonyms to index map for easier query
    for (size_t i = 0; i < synonymsList.size(); ++i) {
        synonymToIndexMap.emplace(synonymsList.at(i), i);
    }
    for (size_t i = 0; i < nextSynonymsList.size(); ++i) {
        auto it = synonymToIndexMap.find(nextSynonymsList.at(i));
        if (it!=synonymToIndexMap.end()) {
            indexPairs.emplace_back(it->second, i);
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

void RawResult::setIsBooleanResult() {
    isBooleanResult = false;
}

bool RawResult::getIsSynonymResult() {
    return isSynonymResult;
}

void RawResult::setIsSynonymResult() {
    isSynonymResult = true;
}


std::ostream &operator<<(std::ostream &os, const RawResult &result) {
    for (const auto syn : result.synonymsList) {
        os << syn << "\t";
    }
    os << std::endl;
    os << "_______________________________________________________" << std::endl;

    for (const auto &record : result.resultsList) {
        for (const auto &value : record) {
            os << value << "\t";
        }
        os << std::endl;
    }

    return os;
}





