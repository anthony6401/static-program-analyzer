#ifndef SPA_RAWRESULT_H
#define SPA_RAWRESULT_H

#include "unordered_set"
#include "string"
#include "vector"

class RawResult {

private:
    //  Query results returns false
    bool isFalseResult = false;
    // No synonym queries
    bool isBooleanResult = false;
    bool isSynonymResult = false;
    bool isSingleConstraints = false;

public:
    std::vector<std::string> synonymsList;
    std::vector<std::vector<std::string>> resultsList;

    RawResult();
    RawResult(const std::string &synonym, const std::unordered_set<std::string> &results);
    RawResult(std::string leftSynonym, std::string rightSynonym,
              std::vector<std::pair<std::string, std::string>> results);
    bool getIsSynonymResult();
    void setIsSynonymResult();
    bool getIsFalseResult();
    void setIsFalseResult();
    bool isEmptyResult();
    bool getIsBooleanResult();
    void setIsBooleanResult();
    int getSynonymCount();
    bool getIsSingleConstraints();
    void setIsSingleConstraints();

};

#endif //SPA_RAWRESULT_H
