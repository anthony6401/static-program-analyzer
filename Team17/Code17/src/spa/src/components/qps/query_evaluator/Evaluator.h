#ifndef SPA_EVALUATOR_H
#define SPA_EVALUATOR_H

#include <list>
#include <vector>
#include "components/qps/abstract_query_object/QueryObject.h"

class Evaluator {
public:
    static void evaluateQuery(QueryObject queryObject, std::list<std::string> &results);
};

#endif //SPA_EVALUATOR_H
