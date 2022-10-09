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
        // std::cout << "evaluated results aft combining: " << evaluatedResults.getHasAlternativeAttributeName() << std::endl;
        Evaluator::populateResultsList(evaluatedResults, select, results, qpsClient, synonymToDesignEntityMap);
    }
}



void Evaluator::populateResultsList(ResultTable &evaluatedResults, Select select, std::list<std::string> &results, QPSClient qpsClient, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap) {
    std::string selectSynonym = select.getReturnValues().front().getValue();
    TokenType returnType = select.getReturnType();
    if (returnType == TokenType::BOOLEAN) {
        if (evaluatedResults.getIsFalseResult()) {
            results.emplace_back("FALSE");
        } else {
            results.emplace_back("TRUE");
        }
    }

    if (returnType == TokenType::SYNONYM) {
        if (evaluatedResults.getIsFalseResult()) {
            return;
        } else {
            std::unordered_set<std::string> resultsToPopulate = evaluatedResults.getSynonymResultsToBePopulated(selectSynonym);
            for (std::string result : resultsToPopulate) {
                results.emplace_back(result);
            }
        }
    }

    if (returnType == TokenType::TUPLE) {
        std::vector<TokenObject> tuple = select.getReturnValues();
        std::unordered_set<std::string> resultsToPopulate = evaluatedResults.getTupleResultsToBePopulated(tuple, synonymToDesignEntityMap);
        for (std::string result : resultsToPopulate) {
            results.emplace_back(result);
        }
    }

    if (returnType == TokenType::ATTRIBUTE) {
        std::unordered_set<std::string> resultsToPopulate = evaluatedResults.getSynonymResultsToBePopulated(selectSynonym);
        bool hasAlternativeAttributeName = evaluatedResults.getHasAlternativeAttributeName();
        std::string selectSynonymValue = select.getReturnValues().front().getValue();
        DesignEntity entityType = synonymToDesignEntityMap[selectSynonymValue];
        if (hasAlternativeAttributeName) {
            std::unordered_set<std::string> alternativeAttributeValueSet;
            // call pkb api
            for (auto statementNumber : resultsToPopulate) {
                std::string alternative = qpsClient.getStatementMapping(statementNumber, entityType);
                alternativeAttributeValueSet.insert(alternative);
            }

            for (const auto& alternativeAttribute : alternativeAttributeValueSet) {
                results.emplace_back(alternativeAttribute);
            }

        } else {
            for (std::string result : resultsToPopulate) {
                results.emplace_back(result);
            }
        }
    }
}

// Returns boolean, check for False or Empty Clauses
bool Evaluator::evaluateNoSynonymClauses(GroupedClause noSynonymsClauses) {
    if (noSynonymsClauses.isEmpty()) {
        return false;
    } else {
        std::vector<std::shared_ptr<Clause>> clauses = noSynonymsClauses.getClauses();
        for (auto c : clauses) {
            ResultTable result = c -> evaluateClause();
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

    for (const auto& r : relationships) {
        std::shared_ptr<Clause> relationshipClauseToEvaluate = ClauseCreator::createClause(r, synonymToDesignEntityMap, qpsClient);
        clauseDivider.addClauseToDivider(relationshipClauseToEvaluate);
    }

    for (const auto& p : patterns) {
        std::shared_ptr<Clause> patternClauseToEvaluate = ClauseCreator::createClause(p, synonymToDesignEntityMap, qpsClient);
        clauseDivider.addClauseToDivider(patternClauseToEvaluate);
    }

    return clauseDivider;
}
