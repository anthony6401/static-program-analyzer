#include "Evaluator.h"
#include <memory>
#include <iostream>
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/factory/ClauseCreator.h"
#include "components/pkb/clients/QPSClient.h"
#include "ClausesDivider.h"

void Evaluator::evaluateQuery(QueryObject queryObject, std::list<std::string> &results, QPSClient qpsClient) {
    if (!queryObject.isSyntacticallyCorrect()) {
        results.emplace_back("SyntaxError");
    } else if (!queryObject.isSemanticallyValid()) {
        results.emplace_back("SemanticError");
    } else {
        RawResult evaluatedResults;
        std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap = queryObject.getSynonymToDesignEntityMap();
        Select select = queryObject.getSelect();
        std::shared_ptr<Clause> selectClause = ClauseCreator::createClause(select.getSynonym(), synonymToDesignEntityMap, qpsClient);

        ClauseDivider clausesToEvaluate = extractClausesToEvaluate(queryObject, synonymToDesignEntityMap, qpsClient);
        clausesToEvaluate.divideCommonSynonymGroupsBySelect(selectClause);
        GroupedClause noSynonymsClauses = clausesToEvaluate.getNoSynonymsPresent();
        std::vector<GroupedClause> hasSelectSynonymPresent = clausesToEvaluate.getSelectSynonymPresentGroups();
        std::vector<GroupedClause> noSelectSynonymPresent = clausesToEvaluate.getSelectSynonymNotPresentGroups();

        bool isFalseNoSynonymClauseEvaluation = Evaluator::evaluateNoSynonymClauses(noSynonymsClauses);
        bool isFalseNoSelectSynonymEvaluation = Evaluator::evaluateNoSelectSynonymClauses(noSelectSynonymPresent);

        if (isFalseNoSynonymClauseEvaluation || isFalseNoSelectSynonymEvaluation) {
            evaluatedResults.setIsFalseResultToTrue();
        } else {
            evaluatedResults = Evaluator::evaluateHasSelectSynonymClauses(hasSelectSynonymPresent, select.getSynonym());
        }

        // For unrelated to select synonyms, if both tables are true/not empty, return all results
        RawResult finalResultTable = Evaluator::combineResultsWithSelect(selectClause, evaluatedResults);
        Evaluator::populateResults(finalResultTable, select.getSynonym(), results);
    }
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
            std::shared_ptr<Clause> relationshipClauseToEvaluate = ClauseCreator::createClause(r, synonym, synonymToDesignEntityMap, qpsClient);
            clauseDivider.addClauseToDivider(relationshipClauseToEvaluate);
        }

        for (const auto& p : patterns) {
            std::shared_ptr<Clause> patternClauseToEvaluate = ClauseCreator::createClause(p, synonym, synonymToDesignEntityMap, qpsClient);
            clauseDivider.addClauseToDivider(patternClauseToEvaluate);
        }
    }
    return clauseDivider;
}

RawResult Evaluator::combineResultsWithSelect(std::shared_ptr<Clause> selectClause, RawResult evaluatedResults) {
    RawResult selectResults = selectClause -> evaluateClause();
    evaluatedResults.combineResult(selectResults);
    return evaluatedResults;
}

void Evaluator::populateResults(RawResult finalResult, std::string selectSynonym, std::list<std::string> &results) {
    if (finalResult.getIsFalseResult()) {
        // Return empty result
        return;
    }

    std::unordered_set<std::string> resultsToPopulate = finalResult.getResultsToBePopulated(selectSynonym);
    for (std::string result : resultsToPopulate) {
        results.emplace_back(result);
    }
}

// Returns boolean, check for False or Empty Clauses
bool Evaluator::evaluateNoSynonymClauses(GroupedClause noSynonymsClauses) {
    if (noSynonymsClauses.isEmpty()) {
        return false;
    } else {
        std::vector<std::shared_ptr<Clause>> clauses = noSynonymsClauses.getClauses();
        for (auto c : clauses) {
            RawResult result = c -> evaluateClause(); // {false} -> getIsFalseResult -> true
            if (result.getIsFalseResult()) {
                return true;
            }
        }
        return false;
    }
}

// Returns boolean, check for False or Empty Clauses
bool Evaluator::evaluateNoSelectSynonymClauses(std::vector<GroupedClause> noSelectSynonymPresent) {
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
    RawResult combinedResultTable;
    for (GroupedClause gc : hasSelectSynonymPresent) {
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
