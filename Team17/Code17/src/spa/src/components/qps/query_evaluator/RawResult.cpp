#include "RawResult.h"

RawResult::RawResult() : result(std::unordered_set<std::string>()), isFalseResult(false) {}

RawResult::RawResult(std::unordered_set<std::string> result) {
    this->result = result;
}

bool RawResult::getIsFalseResult() {
    return isFalseResult;
}