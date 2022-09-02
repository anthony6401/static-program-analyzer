#include "Evaluator.h"
#include "components/qps/abstract_query_object/QueryObject.h"

void Evaluator::evaluateQuery(QueryObject queryObject, std::list<std::string> &results) {
    // Extract synonyms to be returned as a result
    // Extract clauses from abstract query object
    // Evaluate clauses individually
    // If any returns no results or false, terminate evaluation and return none as a result
    // Combine results of evaluation and store in query db
}

//std::vector<Clause> extractClausesToEvaluate(QueryObject queryObject) {
//    std::vector<Clause> clausesToEvaluate;
//    std::vector<SuchThat> relationships = queryObject.getRelationships();
//    std::vector<Pattern> patterns = queryObject.getPattern();
//    if (!relationships.empty()) {
//        // Create relationships
//        for (SuchThat r : relationships) {
//            Clause clause
//        }
//    }
//
//    if (!queryObject.getPattern().empty()) {
//        // Create patterns
//    }
//    return clausesToEvaluate;
//}