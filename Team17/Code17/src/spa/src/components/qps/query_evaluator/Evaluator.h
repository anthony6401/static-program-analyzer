#ifndef SPA_EVALUATOR_H
#define SPA_EVALUATOR_H

#include <list>
#include <vector>
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"

class Evaluator {
public:
    static void evaluateQuery(QueryObject queryObject, std::list<std::string> &results);
    std::vector<Clause> extractClausesToEvaluate(QueryObject);
};

#endif //SPA_EVALUATOR_H
