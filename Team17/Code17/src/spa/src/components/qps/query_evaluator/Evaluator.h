#ifndef SPA_EVALUATOR_H
#define SPA_EVALUATOR_H
#include <memory>
#include <list>
#include <vector>
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/pkb/clients/QPSClient.h"
#include "GroupedClause.h"

class Evaluator {
public:
    static void evaluateQuery(QueryObject queryObject, std::list<std::string> &results, QPSClient qpsClient);
    static std::vector<std::shared_ptr<Clause>> extractClausesToEvaluate(QueryObject queryObject, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    static bool evaluateNoSynonymClauses(GroupedClause noSynonymsClauses);
    static bool evaluateNoSelectSynonymClauses(std::vector<GroupedClause> noSelectSynonymPresent);
    static RawResult evaluateHasSelectSynonymClauses(std::vector<GroupedClause> hasSelectSynonymPresent, std::string selectSynonym);
    static RawResult evaluateWithinGroupSelectSynonymClauses(GroupedClause currentGroupedClause);
    static std::unordered_set<std::string> joinRawResults(std::vector<RawResult> rawResultsList, std::string selectSynonym, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    static std::vector<std::string> findCommonSynonyms(std::vector<std::string> firstSynonymList, std::vector<std::string> secSynonymList);
    static int getSelectSynonymIndex(std::vector<std::string> synonymList, std::string selectSynonym);
};

#endif //SPA_EVALUATOR_H
