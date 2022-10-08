#ifndef SPA_EVALUATOR_H
#define SPA_EVALUATOR_H
#include <memory>
#include <list>
#include <vector>
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/pkb/clients/QPSClient.h"
#include "GroupedClause.h"
#include "ClausesDivider.h"

class Evaluator {
public:
    static void evaluateQuery(QueryObject queryObject, std::list<std::string> &results, QPSClient qpsClient);
    static ClauseDivider extractClausesToEvaluate(QueryObject queryObject, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    static bool evaluateNoSynonymClauses(GroupedClause noSynonymsClauses);
    static bool evaluateNoSelectSynonymClauses(std::vector<GroupedClause> noSelectSynonymPresent);
    static ResultTable evaluateHasSelectSynonymClauses(std::vector<GroupedClause> hasSelectSynonymPresent, std::shared_ptr<Clause> &selectClause);
    static ResultTable evaluateWithinGroupSelectSynonymClauses(GroupedClause currentGroupedClause);
    static ResultTable combineResultsWithSelect(std::shared_ptr<Clause> &selectClause, ResultTable &evaluatedResults);
    static void populateResults(ResultTable finalResult, std::string selectSynonym, std::list<std::string> &results, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap);
    static void populateResultsList(ResultTable &finalResult, Select select, std::list<std::string> &results, QPSClient qpsClient, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap);
    static std::unordered_set<std::string> joinRawResults(std::vector<ResultTable> rawResultsList, std::string selectSynonym, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    static std::vector<std::string> findCommonSynonyms(std::vector<std::string> firstSynonymList, std::vector<std::string> secSynonymList);
    static int getSelectSynonymIndex(std::vector<std::string> synonymList, std::string selectSynonym);
};

#endif //SPA_EVALUATOR_H
