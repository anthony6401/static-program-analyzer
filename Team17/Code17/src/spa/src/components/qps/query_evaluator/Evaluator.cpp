#include "Evaluator.h"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/factory/ClauseCreator.h"

void Evaluator::evaluateQuery(QueryObject queryObject, std::list<std::string> &results) {
    // Extract return type of query via Select class and map
    // Extract synonyms to be returned as a result
    // Extract clauses from abstract query object
    // Evaluate clauses individually
    // If any returns no results or false, terminate evaluation and return none as a result
    // Combine results of evaluation and store in query db
}

std::vector<std::shared_ptr<Clause>> extractClausesToEvaluate(QueryObject queryObject) {
    std::vector<std::shared_ptr<Clause>> clausesToEvaluate;
    std::vector<SuchThat> relationships = queryObject.getRelationships();
    std::vector<Pattern> patterns = queryObject.getPattern();
    Select synonym = queryObject.getSelect();
    std::unordered_map<std::string, TokenType> synonymToDesignEntityMap = queryObject.getSynonymToDesignEntityMap();

    // For Select Clauses
    if (relationships.empty() && patterns.empty()) {
        // Create a Select Clause Object for evaluation
        std::shared_ptr<Clause> clause = ClauseCreator::createClause(synonym, synonymToDesignEntityMap);
        clausesToEvaluate.push_back(clause);
    }
    return clausesToEvaluate;
}