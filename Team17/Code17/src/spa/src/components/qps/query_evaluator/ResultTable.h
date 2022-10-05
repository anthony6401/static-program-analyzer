#ifndef SPA_RESULTTABLE_H
#define SPA_RESULTTABLE_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "unordered_set"
#include "string"
#include "vector"
#include "map"
#include "set"

class ResultTable {

private:
    bool isFalseResult = false;
    bool isSynonymResult = false;
    bool isTupleResult = false;
    bool isBooleanResult = false;

public:
    std::vector<std::string> synonymsList;
    std::vector<std::vector<std::string>> resultsList;
    ResultTable();
    ResultTable(bool pkbBooleanResult);
    ResultTable(const std::string &synonym, const std::unordered_set<std::string> &results);
    ResultTable(std::string leftSynonym, std::string rightSynonym,
                std::vector<std::pair<std::string, std::string>> results);
    void filterBySelectSynonym(std::set<std::string> &&synonyms);
    void combineResult(ResultTable &nextResult);
    void updateResultType(ResultTable &nextResult);
    std::map<std::string, size_t> computeSynonymToIndexMap();
    std::pair<std::vector<std::pair<size_t, size_t>>, std::vector<size_t>> getIndexes(std::vector<std::string> nextSynonymsList);
    std::unordered_set<std::string> getSynonymResultsToBePopulated(std::string selectSynonym);
    std::unordered_set<std::string> getTupleResultsToBePopulated(std::vector<TokenObject> tuple);
    std::vector<std::pair<size_t, size_t>> findCommonSynonymsIndexPairs(std::vector<std::string> nextSynonymsList, std::map<std::string, size_t> synonymToIndexMap);
    void joinResultsListWithCommonSynonym(ResultTable nextResult, std::vector<std::pair<size_t, size_t>> commonSynonymsIndexPairs, std::vector<size_t> notCommonNextSynonymIndex);
    void joinResultsListWithNoCommonSynonym(ResultTable nextResult);
    std::vector<size_t> findNotCommonSynonymsIndex(std::vector<std::string> nextSynonymsList, std::map<std::string, size_t> synonymToIndexMap);
    std::string formTupleResultString(std::vector<std::string> newResultsList);
    friend std::ostream &operator<<(std::ostream &os, const ResultTable &table);
    bool getIsSynonymResult();
    void setIsSynonymResult();
    bool getIsTupleResult();
    void setIsTupleResult();
    bool getIsBooleanResult();
    void setIsBooleanResult();
    bool getIsFalseResult();
    void setIsFalseResult(bool pkbBooleanResult);
    void setIsFalseResultToTrue();
    bool isEmptyResult();
    int getSynonymCount();
};

#endif //SPA_RESULTTABLE_H
