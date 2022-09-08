#ifndef SPA_EVALUATOR_H
#define SPA_EVALUATOR_H
#include <memory>
#include <list>
#include <vector>
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/pkb/clients/QPSClient.h"

class Evaluator {
public:
    static void evaluateQuery(QueryObject queryObject, std::list<std::string> &results, QPSClient qpsClient);
    static std::vector<std::shared_ptr<Clause>> extractClausesToEvaluate(QueryObject queryObject, std::unordered_map<std::string, TokenType> synonymToDesignEntityMap, QPSClient qpsClient);
};

#endif //SPA_EVALUATOR_H
