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
        ResultTable evaluatedResults;
        std::unordered_set<std::string> synonymsInTable{};
        std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap = queryObject.getSynonymToDesignEntityMap();
        Select select = queryObject.getSelect();
        std::shared_ptr<Clause> selectClause = ClauseCreator::createClause(select, synonymsInTable, synonymToDesignEntityMap, qpsClient);
        //std::shared_ptr<Clause> selectClause = ClauseCreator::createClause(select.getSynonym(), synonymToDesignEntityMap, qpsClient);
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
            evaluatedResults = Evaluator::evaluateHasSelectSynonymClauses(hasSelectSynonymPresent, selectClause);
        }

        synonymsInTable = {evaluatedResults.synonymsList.begin(), evaluatedResults.synonymsList.end()};

        selectClause = ClauseCreator::createClause(select, synonymsInTable, synonymToDesignEntityMap, qpsClient);
        ResultTable selectTable = selectClause -> evaluateClause();
        evaluatedResults.combineResult(selectTable);
        Evaluator::populateResultsList(evaluatedResults, select, results);
    }
}

void Evaluator::populateResultsList(ResultTable &evaluatedResults, Select select, std::list<std::string> &results) {
    bool isBooleanResult = evaluatedResults.getIsBooleanResult();
    bool isSynonymResult = evaluatedResults.getIsSynonymResult();
    bool isTupleResult = evaluatedResults.getIsTupleResult();
    // bool isAttributeResult = finalResult.getIsAttributeResult();
    if (isBooleanResult) {
        if (evaluatedResults.getIsFalseResult()) {
            results.emplace_back("FALSE");
        } else {
            results.emplace_back("TRUE");
        }
    } else if (isSynonymResult) {
        if (evaluatedResults.getIsFalseResult()) {
            // Return empty result
            return;
        } else {
            std::string selectSynonym = select.getReturnValues().front().getValue();
            std::unordered_set<std::string> resultsToPopulate = evaluatedResults.getSynonymResultsToBePopulated(selectSynonym);
            for (std::string result : resultsToPopulate) {
                results.emplace_back(result);
            }
        }
    } else if (isTupleResult) {
        std::vector<TokenObject> tuple = select.getReturnValues();
        std::unordered_set<std::string> resultsToPopulate = evaluatedResults.getTupleResultsToBePopulated(tuple);
        for (std::string result : resultsToPopulate) {
            results.emplace_back(result);
        }
    } else {
        // Attribute result
    }

}

void Evaluator::populateResults(ResultTable finalResult, std::string selectSynonym, std::list<std::string> &results) {
    if (finalResult.getIsFalseResult()) {
        // Return empty result
        return;
    }

    std::unordered_set<std::string> resultsToPopulate = finalResult.getSynonymResultsToBePopulated(selectSynonym);
    for (std::string result : resultsToPopulate) {
        results.emplace_back(result);
    }
}

//ResultTable Evaluator::combineResultsWithSelect(std::shared_ptr<Clause> &selectClause, ResultTable &evaluatedResults) {
//    // Synonym, Tuple or Boolean
//    std::cout << "IN COMBINE RESULTS WITH SELECT METHOD" << std::endl;
//    ResultTable selectResults = selectClause -> evaluateClause();
//    evaluatedResults.combineResult(selectResults);
//    std::cout << "test " << evaluatedResults.getIsSynonymResult() << std::endl;
//    std::cout << "evaluatedResults are: " << evaluatedResults.resultsList.empty() << std::endl;
//    return evaluatedResults;
//}

// Returns boolean, check for False or Empty Clauses
bool Evaluator::evaluateNoSynonymClauses(GroupedClause noSynonymsClauses) {
    if (noSynonymsClauses.isEmpty()) {
        return false;
    } else {
        std::vector<std::shared_ptr<Clause>> clauses = noSynonymsClauses.getClauses();
        for (auto c : clauses) {
            ResultTable result = c -> evaluateClause(); // {false} -> getIsFalseResult -> true
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
        ResultTable result = gc.evaluateGroupedClause(); // Combined result within a grouped clause
        if (result.getIsFalseResult()) {
            return true;
        }
    }
    return false;
}

// Each grouped clause has connected synonyms, and each group clause is related to Select synonym
// Evaluate each grouped clause in a loop, find common synonyms and combine results
// Combine all grouped clauses and filter values by select synonym
ResultTable Evaluator::evaluateHasSelectSynonymClauses(std::vector<GroupedClause> hasSelectSynonymPresent, std::shared_ptr<Clause> &selectClause) {
    ResultTable combinedResultTable;
    for (GroupedClause gc : hasSelectSynonymPresent) {
        ResultTable intermediate = gc.evaluateGroupedClause();
        if (intermediate.getIsFalseResult()) {
            combinedResultTable = std::move(intermediate);
            break;
        }
        intermediate.filterBySelectSynonym(selectClause -> getAllSynonyms());
        combinedResultTable.combineResult(intermediate);
    }
    return combinedResultTable;
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
            std::shared_ptr<Clause> relationshipClauseToEvaluate = ClauseCreator::createClause(r, synonymToDesignEntityMap, qpsClient);
            clauseDivider.addClauseToDivider(relationshipClauseToEvaluate);
        }

        for (const auto& p : patterns) {
            std::shared_ptr<Clause> patternClauseToEvaluate = ClauseCreator::createClause(p, synonymToDesignEntityMap, qpsClient);
            clauseDivider.addClauseToDivider(patternClauseToEvaluate);
        }
    }
    return clauseDivider;
}



ResultTable Evaluator::evaluateWithinGroupSelectSynonymClauses(GroupedClause currentGroupedClause) {
    ResultTable withinGroupResultTable;
    for (auto c : currentGroupedClause.getClauses()) {
        ResultTable result = c->evaluateClause();
        if (result.isEmptyResult() || result.getIsFalseResult()) {
            return withinGroupResultTable;
        }
        // Merge tables
        withinGroupResultTable.combineResult(result);
    }
    return withinGroupResultTable;
}
