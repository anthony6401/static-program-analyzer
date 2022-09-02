#include "Evaluator.h"
#include "components/qps/abstract_query_object/QueryObject.h"

void Evaluator::evaluateQuery(QueryObject queryObject, std::list<std::string> &results) {
    // Extract synonyms to be returned as a result
    // Extract clauses from abstract query object
    // Evaluate clauses individually
    // If any returns no results or false, terminate evaluation and return none as a result
    // Combine results of evaluation and store in query db
}