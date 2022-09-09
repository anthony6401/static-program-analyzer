#include "Evaluator.h"
#include <memory>
#include <iostream>
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/factory/ClauseCreator.h"
#include "components/pkb/clients/QPSClient.h"

void Evaluator::evaluateQuery(QueryObject queryObject, std::list<std::string> &results, QPSClient qpsClient) {
    std::unordered_map<std::string, TokenType> synonymToDesignEntityMap = queryObject.getSynonymToDesignEntityMap();
    std::vector<std::shared_ptr<Clause>> clausesToEvaluate = extractClausesToEvaluate(queryObject, synonymToDesignEntityMap, qpsClient);
    std::vector<RawResult> evaluatedResultsList;
    bool isNoneResult = false;
    // Select, Relationship, Pattern or Relationship and Pattern
    for (auto clause : clausesToEvaluate) {
        RawResult evaluatedResult = clause->evaluateClause();
        // If any returns no results or false, terminate evaluation and return none as a result
        if (evaluatedResult.getIsFalseResult() || evaluatedResult.isResultEmpty()) {
            results.emplace_back("none");
            isNoneResult = true;
            break;
        }
        evaluatedResultsList.push_back(evaluatedResult);
    }

    if (!isNoneResult) {
        std::unordered_set<std::string> joinedResults = Evaluator::joinEvaluatedResults(evaluatedResultsList);
        for (std::string s : joinedResults) {
            results.push_back(s);
        }
    }
    // Combine results of evaluation and store in query db
}

std::unordered_set<std::string> Evaluator::joinEvaluatedResults(std::vector<RawResult> evaluatedResultsList) {
    std::unordered_set<std::string> firstResult = evaluatedResultsList.front().getResult();
    if (evaluatedResultsList.size() == 1) {
        return firstResult;
    } else {
        std::unordered_set<std::string> joinedResults = {};
        std::unordered_set<std::string> secondResult = evaluatedResultsList.back().getResult();
        std::unordered_set<std::string> smallerResult = (firstResult.size() < secondResult.size()) ? firstResult : secondResult;
        std::unordered_set<std::string> largerResult = (firstResult.size() >= secondResult.size()) ? firstResult : secondResult;
        for (std::string s : smallerResult) {
            if (largerResult.find(s) != largerResult.end()) {
                joinedResults.insert(s);
            }
        }
        return joinedResults;
    }
}


std::vector<std::shared_ptr<Clause>> Evaluator::extractClausesToEvaluate(QueryObject queryObject, std::unordered_map<std::string, TokenType> synonymToDesignEntityMap, QPSClient qpsClient) {
    std::vector<std::shared_ptr<Clause>> clausesToEvaluate;
    std::vector<SuchThat> relationships = queryObject.getRelationships();
    std::vector<Pattern> patterns = queryObject.getPattern();
    Select synonym = queryObject.getSelect();

    if (relationships.empty() && patterns.empty()) {
        std::shared_ptr<Clause> selectClauseToEvaluate = ClauseCreator::createClause(synonym, synonymToDesignEntityMap, qpsClient);
        clausesToEvaluate.push_back(selectClauseToEvaluate);
        return clausesToEvaluate;
    } else {
        for (const auto& r : relationships) {
            std::shared_ptr<Clause> relationshipClauseToEvaluate = ClauseCreator::createClause(r, synonym, synonymToDesignEntityMap, qpsClient);
            clausesToEvaluate.push_back(relationshipClauseToEvaluate);
        }

        for (const auto& p : patterns) {
            std::shared_ptr<Clause> patternClauseToEvaluate = ClauseCreator::createClause(p, synonym, synonymToDesignEntityMap, qpsClient);
            clausesToEvaluate.push_back(patternClauseToEvaluate);
        }
        return clausesToEvaluate;
    }
}


//std::unordered_set<std::string> Evaluator::evaluateSelectClause(std::vector<std::shared_ptr<Clause>> clausesToEvaluate) {
//    std::unordered_set<std::string> resultOfClause;
//    for (auto c : clausesToEvaluate) {
//        resultOfClause = c -> evaluateClause();
//    }
//    return resultOfClause;
//};
//
//std::shared_ptr<Clause> Evaluator::extractSelectClause(Select synonym, std::unordered_map<std::string, TokenType> synonymToDesignEntityMap, QPSClient qpsClient) {
//    std::shared_ptr<Clause> selectClauseToEvaluate = ClauseCreator::createClause(synonym, synonymToDesignEntityMap, qpsClient);
//    return selectClauseToEvaluate;
//}
//