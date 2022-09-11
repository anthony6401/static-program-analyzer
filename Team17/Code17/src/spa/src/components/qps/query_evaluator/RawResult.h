#ifndef SPA_RAWRESULT_H
#define SPA_RAWRESULT_H

#include "unordered_set"
#include "string"
#include "vector"

class RawResult {

private:
    //  Query results returns false
    bool isFalseResult = false;
    bool isBooleanResult = false;
    // Query results is empty
    bool isEmptyResult = false;

public:
    std::vector<std::string> synonymsList;
    std::vector<std::vector<std::string>> resultsList;

    RawResult();
    RawResult(const std::string &synonym, const std::unordered_set<std::string> &results);
    RawResult(std::string leftSynonym, std::string rightSynonym,
              std::vector<std::pair<std::string, std::string>> results);
    bool getIsFalseResult();
    void setIsFalseResult();
    bool getIsEmptyResult();
    void setIsEmptyResult();
    bool getIsBooleanResult();
    void setIsBooleanResult();
    int getSynonymCount();

};

#endif //SPA_RAWRESULT_H
