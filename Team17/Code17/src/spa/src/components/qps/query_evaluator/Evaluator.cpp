#include "Evaluator.h"
#include <memory>
#include <iostream>
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/factory/ClauseCreator.h"
#include "components/pkb/clients/QPSClient.h"
#include "ClausesDivider.h"

void Evaluator::evaluateQuery(QueryObject queryObject, std::list<std::string> &results, QPSClient qpsClient) {
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap = queryObject.getSynonymToDesignEntityMap();
    Select select = queryObject.getSelect();
    std::shared_ptr<Clause> selectClause = ClauseCreator::createClause(select.getSynonym(), synonymToDesignEntityMap, qpsClient);

    ClauseDivider clausesToEvaluate = extractClausesToEvaluate(queryObject, synonymToDesignEntityMap, qpsClient);

    GroupedClause noSynonymsClauses = clausesToEvaluate.getNoSynonymsPresent();

    std::pair<std::vector<GroupedClause>, std::vector<GroupedClause>> pairBySelect = clausesToEvaluate.divideCommonSynonymGroupsBySelect(selectClause);

    std::vector<GroupedClause> hasSelectSynonymPresent = pairBySelect.first;
    std::vector<GroupedClause> noSelectSynonymPresent = pairBySelect.second;

    RawResult evaluatedResults;
    bool isFalseNoSynonymClauseEvaluation = Evaluator::evaluateNoSynonymClauses(noSynonymsClauses);
    bool isFalseNoSelectSynonymEvaluation = Evaluator::evaluateNoSelectSynonymClauses(noSelectSynonymPresent);

    std::cout << "isFalseNoSynonymClauseEvaluation: " << isFalseNoSynonymClauseEvaluation << std::endl;
    std::cout << "isFalseNoSelectSynonymEvaluation: " << isFalseNoSelectSynonymEvaluation << std::endl;

    if (isFalseNoSynonymClauseEvaluation || isFalseNoSelectSynonymEvaluation) {
        evaluatedResults.setIsFalseResultToTrue();
    } else {
        evaluatedResults = Evaluator::evaluateHasSelectSynonymClauses(hasSelectSynonymPresent, select.getSynonym());
    }

    RawResult selectResults = selectClause->evaluateClause();
    evaluatedResults.combineResult(selectResults);
    Evaluator::populateResults(evaluatedResults, select.getSynonym(), results);
}

void Evaluator::populateResults(RawResult finalResult, std::string selectSynonym, std::list<std::string> &results) {
    if (finalResult.getIsFalseResult()) {
        results.emplace_back("none");
    }

    std::cout << finalResult << std::endl;

    std::unordered_set<std::string> resultsToPopulate = finalResult.getResultsToBePopulated(selectSynonym);

    std::cout << "---------POPULATING-----------" << std::endl;
    for (std::string result : resultsToPopulate) {
        std::cout << result << std::endl;
        results.emplace_back(result);
    }
}

// Returns boolean, check for False or Empty Clauses
bool Evaluator::evaluateNoSynonymClauses(GroupedClause noSynonymsClauses) {
    std::cout << "in evaluate no synonym" << std::endl;
    if (noSynonymsClauses.isEmpty()) {
        std::cout << "no synonym clause" << std::endl;
        return false;
    } else {
        std::vector<std::shared_ptr<Clause>> clauses = noSynonymsClauses.getClauses();
        for (auto c : clauses) {
            RawResult result = c->evaluateClause(); // {false} -> getIsFalseResult -> true
            if (result.getIsFalseResult()) {
                return true;
            }
        }
        return false;
    }
}

// Returns boolean, check for False or Empty Clauses
bool Evaluator::evaluateNoSelectSynonymClauses(std::vector<GroupedClause> noSelectSynonymPresent) {
    std::cout << "in evaluate no select synonym" << std::endl;
    for (GroupedClause gc : noSelectSynonymPresent) {
        RawResult rawResult = gc.evaluateGroupedClause(); // Combined result within a grouped clause
        if (rawResult.getIsFalseResult()) {
            return true;
        }
    }
    return false;
}

// Each grouped clause has connected synonyms, and each group clause is related to Select synonym
// Evaluate each grouped clause in a loop, find common synonyms and combine results
// Combine all grouped clauses and filter values by select synonym
RawResult Evaluator::evaluateHasSelectSynonymClauses(std::vector<GroupedClause> hasSelectSynonymPresent, std::string selectSynonym) {
    std::cout << "in evaluate has select synonym" << std::endl;
    RawResult combinedResultTable;
    for (GroupedClause gc : hasSelectSynonymPresent) {
        std::cout << "in evaluate has select synonym loop" << std::endl;
      RawResult intermediate = gc.evaluateGroupedClause();
      if (intermediate.getIsFalseResult()) {
          combinedResultTable = std::move(intermediate);
          break;
      }
      intermediate.filterBySelectSynonym(selectSynonym);
      combinedResultTable.combineResult(intermediate);
    }
    return combinedResultTable;
}

//BUGGY
RawResult Evaluator::evaluateWithinGroupSelectSynonymClauses(GroupedClause currentGroupedClause) {
    RawResult withinGroupResultTable;
    for (auto c : currentGroupedClause.getClauses()) {
        RawResult result = c->evaluateClause();
        if (result.isEmptyResult() || result.getIsFalseResult()) {
            return withinGroupResultTable;
        }
        // Merge tables
        withinGroupResultTable.combineResult(result);
    }
    return withinGroupResultTable;
}



ClauseDivider Evaluator::extractClausesToEvaluate(QueryObject queryObject, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient) {
    ClauseDivider clauseDivider;
    std::vector<SuchThat> relationships = queryObject.getRelationships();
    std::vector<Pattern> patterns = queryObject.getPattern();
    Select synonym = queryObject.getSelect();

    if (relationships.empty() && patterns.empty()) {
        std::shared_ptr<Clause> selectClauseToEvaluate = ClauseCreator::createClause(synonym, synonymToDesignEntityMap, qpsClient);
        clauseDivider.addClauseToDivider(selectClauseToEvaluate);
    } else {
        for (const auto& r : relationships) {
            std::cout << "create relationship" << std::endl;
            std::shared_ptr<Clause> relationshipClauseToEvaluate = ClauseCreator::createClause(r, synonym, synonymToDesignEntityMap, qpsClient);
            clauseDivider.addClauseToDivider(relationshipClauseToEvaluate);
        }

        for (const auto& p : patterns) {
            std::cout << "create pattern" << std::endl;
            std::shared_ptr<Clause> patternClauseToEvaluate = ClauseCreator::createClause(p, synonym, synonymToDesignEntityMap, qpsClient);
            clauseDivider.addClauseToDivider(patternClauseToEvaluate);
        }
    }
    return clauseDivider;
}