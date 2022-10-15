#ifndef SPA_RESULTTABLE_H
#define SPA_RESULTTABLE_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "unordered_set"
#include "string"
#include "vector"
#include "unordered_map"
#include "map"
#include "set"
#include "../../../models/Entity/DesignEntity.h"
#include "components/pkb/clients/QPSClient.h"
#include "components/qps/query_evaluator/factory/utils/HashFunction.h"

class ResultTable {

private:
    bool isFalseResult = false;
    bool hasAlternativeAttributeName = false;
public:
    std::vector<std::string> synonymsList;
    std::vector<std::vector<std::string>> resultsList;
    ResultTable();
    ResultTable(bool result);
    ResultTable(const std::string &synonym, const std::unordered_set<std::string> &results);
    ResultTable(const std::string& leftSynonym, const std::string& rightSynonym,
                const std::vector<std::pair<std::string, std::string>>& results);
    ResultTable(const std::string& leftSynonym, const std::string& rightSynonym, const std::unordered_set<std::pair<std::string, std::string>, hashFunction>& results);
    void filterBySelectSynonym(std::set<std::string> &&synonyms);
    void combineResult(ResultTable &nextResult);
    std::map<std::string, size_t> computeSynonymToIndexMap();
    std::unordered_set<std::string> getSynonymResultsToBePopulated(const std::string& selectSynonym);
    std::unordered_set<std::string> getTupleResultsToBePopulated(std::vector<TokenObject> tuple, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    void tupleIteratorResultsHandler(std::vector<TokenObject> tuple, size_t index, std::vector<std::string> &resultSublist, std::vector<std::string> &newResultSublist, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    void joinResultSublistListWithCommonSynonym(std::vector<std::vector<std::string>> &nextResultsList, std::vector<std::vector<std::string>> &newResultsList,
                                                const std::vector<std::pair<size_t, size_t>>& commonSynonymsIndexPairs, std::vector<std::string> &resultSublist, const std::vector<size_t>& notCommonNextSynonymIndex);
    void updateResultsListsFromCommonSynonymsIndexPairs(std::vector<std::vector<std::string>> &nextResultsList, std::vector<std::string> &resultSublist, std::vector<std::string> &nextResultSublist,
                                                        const std::vector<std::pair<size_t, size_t>>& commonSynonymsIndexPairs, bool &isCommon);
    std::vector<std::pair<size_t, size_t>> findCommonSynonymsIndexPairs(std::vector<std::string> nextSynonymsList, std::map<std::string, size_t> synonymToIndexMap);
    void joinResultsListWithCommonSynonym(ResultTable nextResult, const std::vector<std::pair<size_t, size_t>>& commonSynonymsIndexPairs, const std::vector<size_t>& notCommonNextSynonymIndex);
    void joinResultsListWithNoCommonSynonym(ResultTable nextResult);
    std::vector<size_t> findNotCommonSynonymsIndex(std::vector<std::string> nextSynonymsList, std::map<std::string, size_t> synonymToIndexMap);
    std::string formTupleResultString(std::vector<std::string> newResultsList);
    [[nodiscard]] bool getIsFalseResult() const;
    void setIsFalseResult(bool pkbBooleanResult);
    void setIsFalseResultToTrue();
    void setHasAlternativeAttributeNameToTrue();
    void updateHasCommonAttributeName(ResultTable &nextResult);
    [[nodiscard]] bool getHasAlternativeAttributeName() const;
    [[nodiscard]] bool isEmptyResult() const;
};

#endif //SPA_RESULTTABLE_H
