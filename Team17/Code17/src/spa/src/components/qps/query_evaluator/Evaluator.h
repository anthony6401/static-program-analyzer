#ifndef SPA_EVALUATOR_H
#define SPA_EVALUATOR_H

#include <list>
#include <vector>
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"

class Evaluator {
public:
    static void evaluateQuery(QueryObject queryObject, std::list<std::string> &results);
    // std::vector<std::shared_ptr<Clause>> extractClausesToEvaluate(QueryObject queryObject);
    static std::shared_ptr<Clause> extractSelectClauseToEvaluate(Select synonym, std::unordered_map<std::string, TokenType> synonymToDesignEntityMap);
    static std::unordered_set<std::string> evaluateSelectClause(std::vector<std::shared_ptr<Clause>> clausesToEvaluate);
};

#endif //SPA_EVALUATOR_H
