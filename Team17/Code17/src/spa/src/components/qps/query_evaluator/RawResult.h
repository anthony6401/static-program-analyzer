#ifndef SPA_RAWRESULT_H
#define SPA_RAWRESULT_H

#include "unordered_set"
#include "string"

class RawResult {
private:
    bool isFalseResult = false;
    std::unordered_set<std::string> result;

public:
    RawResult();
    RawResult(std::string leftSynonym, std::string rightSynonym, std::string results);
    RawResult(std::unordered_set<std::string> result);
    bool isResultEmpty();
    std::unordered_set<std::string> getResult();
    bool getIsFalseResult();
    void toggleIsFalseResult();
};

#endif //SPA_RAWRESULT_H
