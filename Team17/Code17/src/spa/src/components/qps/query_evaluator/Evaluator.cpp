#include "Evaluator.h"
#include <memory>
#include <iostream>
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/factory/ClauseCreator.h"
#include "components/pkb/clients/QPSClient.h"

void Evaluator::evaluateQuery(QueryObject queryObject, std::list<std::string> &results, QPSClient qpsClient) {
    std::vector<std::shared_ptr<Clause>> clausesToEvaluate;
    std::vector<SuchThat> relationships = queryObject.getRelationships();
    std::vector<Pattern> patterns = queryObject.getPattern();
    Select synonym = queryObject.getSelect();
    std::unordered_map<std::string, TokenType> synonymToDesignEntityMap = queryObject.getSynonymToDesignEntityMap();

    // Extract select clause from query object
    if (relationships.empty() && patterns.empty()) {
        // Create a Select Clause Object for evaluation
        // std::cout << "name of synonym is" << synonym.getName();
        std::shared_ptr<Clause> selectClauseToEvaluate = Evaluator::extractSelectClauseToEvaluate(synonym, synonymToDesignEntityMap, qpsClient);
        clausesToEvaluate.push_back(selectClauseToEvaluate);
    }
    // Extract return type of query via Select class and map

    // Evaluate clauses individually, currently only for select clause
    std::unordered_set<std::string> selectClauseResult = Evaluator::evaluateSelectClause(clausesToEvaluate, qpsClient);
    for (auto r : selectClauseResult) {
        results.push_back(r);
    }
    // If any returns no results or false, terminate evaluation and return none as a result
    // Combine results of evaluation and store in query db
}

std::unordered_set<std::string> Evaluator::evaluateSelectClause(std::vector<std::shared_ptr<Clause>> clausesToEvaluate, QPSClient qpsClient) {
    std::unordered_set<std::string> resultOfClause;
    for (auto c : clausesToEvaluate) {
        resultOfClause = c -> evaluateClause();
    }
    return resultOfClause;
};


std::shared_ptr<Clause> Evaluator::extractSelectClauseToEvaluate(Select synonym,
                                                                               std::unordered_map<std::string, TokenType> synonymToDesignEntityMap, QPSClient qpsClient) {
    std::shared_ptr<Clause> selectClauseToEvaluate = ClauseCreator::createClause(synonym, synonymToDesignEntityMap, qpsClient);
    return selectClauseToEvaluate;
}

// Perhaps split extracting different clauses to different methods
//std::vector<std::shared_ptr<Clause>> Evaluator::extractClausesToEvaluate(QueryObject queryObject) {
//    std::vector<std::shared_ptr<Clause>> clausesToEvaluate;
//    std::vector<SuchThat> relationships = queryObject.getRelationships();
//    std::vector<Pattern> patterns = queryObject.getPattern();
//    Select synonym = queryObject.getSelect();
//    std::unordered_map<std::string, TokenType> synonymToDesignEntityMap = queryObject.getSynonymToDesignEntityMap();
//
//    // For Select Clauses
//    if (relationships.empty() && patterns.empty()) {
//        // Create a Select Clause Object for evaluation
//        std::shared_ptr<Clause> clause = ClauseCreator::createClause(synonym, synonymToDesignEntityMap);
//        clausesToEvaluate.push_back(clause);
//    }
//    return clausesToEvaluate;
//}