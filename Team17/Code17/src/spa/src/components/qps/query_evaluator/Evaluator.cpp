#include "Evaluator.h"
#include <memory>
#include <iostream>
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/factory/ClauseCreator.h"
#include "components/pkb/clients/QPSClient.h"

void Evaluator::evaluateQuery(QueryObject queryObject, std::list<std::string> &results, QPSClient qpsClient) {
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap = queryObject.getSynonymToDesignEntityMap();
    std::vector<std::shared_ptr<Clause>> clausesToEvaluate = extractClausesToEvaluate(queryObject, synonymToDesignEntityMap, qpsClient);
    std::vector<RawResult> evaluatedResultsList;
    bool isNoneResult = false;
    // evaluate results to get RawResult
    // check for false clause or empty results and populate none
    // Check for syntax or semantic errors
    // join rawresults to return synonym return type

    for (auto clause : clausesToEvaluate) {
        RawResult evaluatedResult = clause->evaluateClause();
        if (evaluatedResult.getIsFalseResult() || evaluatedResult.getIsEmptyResult()) {
            results.emplace_back("none");
            isNoneResult = true;
            break;
        }
        evaluatedResultsList.push_back(evaluatedResult);
    }

    if (!isNoneResult) {
        // join Raw results
    }
}

std::unordered_set<std::string> Evaluator::joinRawResults(std::vector<RawResult> rawResultsList) {
    std::unordered_set<std::string> joinedResults;
    // Single clause or Select clause query
    if (rawResultsList.size() == 1) {
        std::vector<std::vector<std::string>> results = rawResultsList.front().resultsList;
        // {{x}, {y}, {z}} -> {x, y, z}
        for (auto singleValue : results) {
            joinedResults.insert(singleValue.front());
        }
    } else { // Multi clause queries
        // find all common synonyms
        std::vector<std::string> commonSynonyms;
        // take note of return synonym
    }

    return std::unordered_set<std::string>();
}


//std::unordered_set<std::string> Evaluator::joinEvaluatedResults(std::vector<RawResult> evaluatedResultsList) {
//    std::unordered_set<std::string> firstResult = evaluatedResultsList.front().getResult();
//    if (evaluatedResultsList.size() == 1) {
//        return firstResult;
//    } else {
//        std::unordered_set<std::string> joinedResults = {};
//        std::unordered_set<std::string> secondResult = evaluatedResultsList.back().getResult();
//        std::unordered_set<std::string> smallerResult = (firstResult.size() < secondResult.size()) ? firstResult : secondResult;
//        std::unordered_set<std::string> largerResult = (firstResult.size() >= secondResult.size()) ? firstResult : secondResult;
//        for (std::string s : smallerResult) {
//            if (largerResult.find(s) != largerResult.end()) {
//                joinedResults.insert(s);
//            }
//        }
//        return joinedResults;
//    }
//}


std::vector<std::shared_ptr<Clause>> Evaluator::extractClausesToEvaluate(QueryObject queryObject, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient) {
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

