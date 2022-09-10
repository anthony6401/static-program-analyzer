#include "RawResult.h"

RawResult::RawResult() : result(std::unordered_set<std::string>()), isFalseResult(false) {}

RawResult::RawResult(std::unordered_set<std::string> result) {
    this->result = result;
}

bool RawResult::getIsFalseResult() {
    return isFalseResult;
}

std::unordered_set<std::string> RawResult::getResult() {
    return result;
}

bool RawResult::isResultEmpty() {
    return result.empty();
}

void RawResult::toggleIsFalseResult() {
    isFalseResult = !isFalseResult;
}

RawResult::RawResult(std::string leftSynonym, std::string rightSynonym, std::string results) {

}
