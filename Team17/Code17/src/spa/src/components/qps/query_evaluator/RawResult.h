#ifndef SPA_RAWRESULT_H
#define SPA_RAWRESULT_H

#include "unordered_set"
#include "string"
#include "vector"

class RawResult {

private:
    //  Query results returns false
    bool isFalseResult = false;
    bool isBooleanResult = true;
    bool isSynonymResult = false;


public:
    std::vector<std::string> synonymsList;
    std::vector<std::vector<std::string>> resultsList;

    RawResult();
    RawResult(bool pkbBooleanResult);
    RawResult(const std::string &synonym, const std::unordered_set<std::string> &results);
    RawResult(std::string leftSynonym, std::string rightSynonym,
              std::vector<std::pair<std::string, std::string>> results);
    void filterBySelectSynonym(std::string synonym);
    void combineResult(RawResult nextResult);
    std::unordered_set<std::string> getResultsToBePopulated(std::string selectSynonym);
    std::vector<std::pair<size_t, size_t>> findCommonSynonymsIndexPairs(std::vector<std::string> nextSynonymsList);
    void joinResultsListWithCommonSynonym(RawResult nextResult, std::vector<std::pair<size_t, size_t>> commonSynonymsIndexPairs);
    void joinResultsListWithNoCommonSynonym(RawResult nextResult);
    std::vector<size_t> findNotCommonSynonymsIndex(std::vector<std::string> nextSynonymsList);
    friend std::ostream &operator<<(std::ostream &os, const RawResult &table);
    bool getIsSynonymResult();
    void setIsSynonymResult();
    bool getIsFalseResult();
    void setIsFalseResult(bool pkbBooleanResult);
    void setIsFalseResultToTrue();
    bool isEmptyResult();
    bool getIsBooleanResult();
    void setIsBooleanResult();
    int getSynonymCount();

};

#endif //SPA_RAWRESULT_H