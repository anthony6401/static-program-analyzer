#include "ResultTable.h"
#include "vector"
#include "string"
#include "iostream"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include <map>
#include <initializer_list>

ResultTable::ResultTable() : resultsList({}), isFalseResult(false), synonymsList({}) {}

ResultTable::ResultTable(bool pkbBooleanResult) : resultsList({}), synonymsList({}) {
    setIsFalseResult(pkbBooleanResult);
};

ResultTable::ResultTable(const std::string& synonym, const std::unordered_set<std::string>& results) {
    if (results.empty()) {
        setIsFalseResultToTrue();
    }
    synonymsList.emplace_back(synonym);
    for (auto singleResult : results) {
        // {{x}, {y}, {z}}
        std::vector<std::string> resultSublist = {singleResult};
        resultsList.emplace_back(resultSublist);
    }
}

ResultTable::ResultTable(std::string leftSynonym, std::string rightSynonym, std::vector<std::pair<std::string, std::string>> results) {
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
}

bool ResultTable::getIsFalseResult() {
    return isFalseResult;
}

bool ResultTable::isEmptyResult() {
    return resultsList.empty();
}

void ResultTable::setIsFalseResult(bool pkbBooleanResult) {
    isFalseResult = !pkbBooleanResult;
}

void ResultTable::setIsFalseResultToTrue() {
    isFalseResult = true;
}

void ResultTable::setHasAlternativeAttributeNameToTrue() {
    hasAlternativeAttributeName = true;
}

bool ResultTable::getHasAlternativeAttributeName() {
    return hasAlternativeAttributeName;
}

std::unordered_set<std::string> ResultTable::getSynonymResultsToBePopulated(std::string selectSynonym) {
    std::unordered_set<std::string> result({});
    auto iterator = std::find(synonymsList.begin(), synonymsList.end(), selectSynonym);
    if (iterator != synonymsList.cend()) {
        int indexOfSynonym = std::distance(synonymsList.begin(), iterator);
        for (auto resultSublist : resultsList) {
            result.insert(resultSublist[indexOfSynonym]);
        }
    }
    return result;
}

std::unordered_set<std::string> ResultTable::getTupleResultsToBePopulated(std::vector<TokenObject> tuple) {
    std::unordered_set<std::string> result({});
    for (auto resultSublist : resultsList) {
        std::vector<std::string> newResultSublist;
        for (auto tupleObject : tuple) {
            if (tupleObject.getTokenType() == TokenType::NAME) {
                auto iterator = std::find(synonymsList.begin(), synonymsList.end(), tupleObject.getValue());
                int indexOfSynonym = std::distance(synonymsList.begin(), iterator);
                newResultSublist.push_back(resultSublist[indexOfSynonym]);
            } else {
                // ATTRIBUTES
            }
        }
        result.insert(ResultTable::formTupleResultString(newResultSublist));
    }

    return result;
}

std::string ResultTable::formTupleResultString(std::vector<std::string> newResultsList) {
    std::string tupleResultString;
    for (size_t i = 0; i < newResultsList.size(); ++i) {
        tupleResultString += newResultsList[i] + (i != newResultsList.size() - 1 ? " " : "");
    }
    return tupleResultString;
}

void ResultTable::filterBySelectSynonym(std::set<std::string> &&synonyms) {
    std::vector<std::string> newSynonymsList;
    std::vector<std::vector<std::string>> newResultsList;

    std::vector<size_t> indexes; // Index of select synonym
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


// Find common synonyms and merge resultsLists
void ResultTable::combineResult(ResultTable &nextResult) {

    ResultTable::updateHasCommonAttributeName(nextResult);

    if (isFalseResult) {
        return;
    } else {
        if (nextResult.isFalseResult) {
            setIsFalseResultToTrue();
        }
        // find common synonyms, maximum 2 since there are only 2 parameters / pattern takes in 1 synonym at max
        // {x, y} {s, x} -> {0, 1} index pair -> go to resultsList
        std::map<std::string, size_t> synonymToIndexMap = ResultTable::computeSynonymToIndexMap();
        std::vector<std::pair<size_t, size_t>> commonSynonymsIndexPairs = ResultTable::findCommonSynonymsIndexPairs(
                nextResult.synonymsList, synonymToIndexMap);

        // Combining clause groups and combining within clause groups
        if (!commonSynonymsIndexPairs.empty()) {
            std::vector<size_t> notCommonNextSynonymIndex = ResultTable::findNotCommonSynonymsIndex(nextResult.synonymsList, synonymToIndexMap);
            ResultTable::joinResultsListWithCommonSynonym(nextResult, commonSynonymsIndexPairs, notCommonNextSynonymIndex);
        } else {
            ResultTable::joinResultsListWithNoCommonSynonym(nextResult);
        }

        // Joining two results with common synonyms but there are no common results
        if (isEmptyResult() && !synonymsList.empty()) {
            setIsFalseResultToTrue();
        }
    }
}

std::vector<size_t> ResultTable::findNotCommonSynonymsIndex(std::vector<std::string> nextSynonymsList, std::map<std::string, size_t> synonymToIndexMap) {
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

void ResultTable::joinResultsListWithNoCommonSynonym(ResultTable nextResult) {
    std::vector<std::vector<std::string>> newResultsList;
    std::vector<std::vector<std::string>> nextResultsList = nextResult.resultsList;
    synonymsList.insert(synonymsList.end(), nextResult.synonymsList.begin(), nextResult.synonymsList.end());

    if (nextResult.isEmptyResult()) {
        return;
    } else if (isEmptyResult()) {
        resultsList = std::move(nextResult.resultsList);
        return;
    } else {
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
}

void ResultTable::joinResultsListWithCommonSynonym(ResultTable nextResult, std::vector<std::pair<size_t, size_t>> commonSynonymsIndexPairs, std::vector<size_t> notCommonNextSynonymIndex) {
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

std::map<std::string, size_t> ResultTable::computeSynonymToIndexMap() {
    std::map<std::string, size_t> synonymToIndexMap;
    for (size_t i = 0; i < synonymsList.size(); i++) {
        synonymToIndexMap.emplace(synonymsList.at(i), i);
    }
    return synonymToIndexMap;
}


std::vector<std::pair<size_t, size_t>> ResultTable::findCommonSynonymsIndexPairs(std::vector<std::string> nextSynonymsList, std::map<std::string, size_t> synonymToIndexMap) {
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

std::ostream &operator<<(std::ostream &os, const ResultTable &table) {
    for (const auto &attribute : table.synonymsList) {
        os << attribute << "\t";
    }
    os << std::endl;
    os << "_______________________________________________________" << std::endl;

    for (const auto &record : table.resultsList) {
        for (const auto &value : record) {
            os << value << "\t";
        }
        os << std::endl;
    }

    return os;
}




