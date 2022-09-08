#ifndef SPA_RAWRESULT_H
#define SPA_RAWRESULT_H

#include "unordered_set"
#include "string"

class RawResult {
private:
    bool isFalseResult;
    std::unordered_set<std::string> result;
public:
    RawResult();
    RawResult(std::unordered_set<std::string> result);
    bool getIsFalseResult();
};

#endif //SPA_RAWRESULT_H
