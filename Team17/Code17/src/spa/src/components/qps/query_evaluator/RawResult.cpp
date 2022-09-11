#include "RawResult.h"
#include "vector"
#include "string"
#include <map>
#include <initializer_list>

RawResult::RawResult() : resultsList({}), isFalseResult(false), synonymsList({}) {}

RawResult::RawResult(const std::string& synonym, const std::unordered_set<std::string>& results) {
    if (results.empty()) {
        setIsEmptyResult();
    }
    synonymsList.emplace_back(synonym);
    for (auto result : results) {
        resultsList.emplace_back(std::initializer_list<std::string>{result});
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





