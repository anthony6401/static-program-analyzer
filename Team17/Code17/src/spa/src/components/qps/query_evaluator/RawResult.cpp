#include "RawResult.h"
#include "vector"
#include "string"
#include <map>
#include <initializer_list>

RawResult::RawResult() : resultsList({}), isFalseResult(false), isBooleanResult(false), isEmptyResult(false), synonymsList({}) {}

RawResult::RawResult(const std::string& synonym, const std::unordered_set<std::string>& results) {
    if (results.empty()) {
        setIsEmptyResult();
    }
    synonymsList.emplace_back(synonym);
    for (auto singleResult : results) {
        // {{x}, {y}, {z}}
        resultsList.emplace_back(std::initializer_list<std::string>{singleResult});
    }
}

RawResult::RawResult(std::string leftSynonym, std::string rightSynonym,
                     std::vector<std::pair<std::string, std::string>> results) {
    if (results.empty()) {
        setIsEmptyResult();
    }

    synonymsList.emplace_back(leftSynonym);
    synonymsList.emplace_back(rightSynonym);
    for (auto result : results) {
        // {{1, x}, {3, y}, {5, z}}
        resultsList.emplace_back(std::initializer_list<std::string>{result.first, result.second});
    }
}

bool RawResult::getIsFalseResult() {
    return isFalseResult;
}

bool RawResult::getIsEmptyResult() {
    return isEmptyResult;
}

void RawResult::setIsFalseResult() {
    isFalseResult = true;
}

void RawResult::setIsEmptyResult() {
    isEmptyResult = true;
}

int RawResult::getSynonymCount() {
    return synonymsList.size();
}

bool RawResult::getIsBooleanResult() {
    return isBooleanResult;
}

void RawResult::setIsBooleanResult() {
    isBooleanResult = true;
}





