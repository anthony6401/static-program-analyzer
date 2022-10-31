#include "Evaluator.h"
#include <memory>
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/factory/ClauseCreator.h"
#include "components/pkb/clients/QPSClient.h"
#include "ClausesDivider.h"
#include "optimizer//ClauseGroupSorter.h"
#include <algorithm>

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
        clausesToEvaluate.divideConnectedSynonymGroupsBySelect(selectClause);

        GroupedClause noSynonymsClauses = clausesToEvaluate.getNoSynonymsPresent();
        bool isFalseNoSynonymClauseEvaluation = Evaluator::evaluateNoSynonymClauses(noSynonymsClauses);

        std::vector<GroupedClause> noSelectSynonymPresent = clausesToEvaluate.getSelectSynonymNotPresentGroups();
        bool isFalseNoSelectSynonymEvaluation = Evaluator::evaluateNoSelectSynonymClauses(noSelectSynonymPresent);

        if (isFalseNoSynonymClauseEvaluation || isFalseNoSelectSynonymEvaluation) {
            evaluatedResults.setIsFalseResultToTrue();
        } else {
            std::vector<GroupedClause> hasSelectSynonymPresent = clausesToEvaluate.getSelectSynonymPresentGroups();
            evaluatedResults = Evaluator::evaluateHasSelectSynonymClauses(hasSelectSynonymPresent, selectClause);
            synonymsInTable = {evaluatedResults.synonymsList.begin(), evaluatedResults.synonymsList.end()};
            selectClause = ClauseCreator::createClause(select, synonymsInTable, synonymToDesignEntityMap, qpsClient);
            Evaluator::combineResultsWithSelect(selectClause, evaluatedResults);
        }

        Evaluator::populateResultsList(evaluatedResults, select, results, qpsClient, synonymToDesignEntityMap);
    }
}

void Evaluator::combineResultsWithSelect(std::shared_ptr<Clause> &selectClause, ResultTable &evaluatedResults) {
    ResultTable selectTable = selectClause -> evaluateClause();
    evaluatedResults.combineResult(selectTable);
}



void Evaluator::populateResultsList(ResultTable &evaluatedResults, Select select, std::list<std::string> &results, QPSClient qpsClient, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap) {
    std::string selectSynonym = select.getReturnValues().front().getValue();
    TokenType returnType = select.getReturnType();

    if (returnType == TokenType::SYNONYM) {
        if (evaluatedResults.getIsFalseResult()) {
            return;
        } else {
            std::unordered_set<std::string> resultsToPopulate = evaluatedResults.getSynonymResultsToBePopulated(selectSynonym);
            for (const std::string& result : resultsToPopulate) {
                results.emplace_back(result);
            }
        }
    }

    if (returnType == TokenType::BOOLEAN) {
        if (evaluatedResults.getIsFalseResult()) {
            results.emplace_back("FALSE");
        } else {
            results.emplace_back("TRUE");
        }
    }

    if (returnType == TokenType::TUPLE) {
        if (evaluatedResults.getIsFalseResult()) {
            return;
        }
        std::vector<TokenObject> tuple = select.getReturnValues();
        std::unordered_set<std::string> resultsToPopulate = evaluatedResults.getTupleResultsToBePopulated(tuple, synonymToDesignEntityMap, qpsClient);
        for (const std::string& result : resultsToPopulate) {
            results.emplace_back(result);
        }
    }

    if (returnType == TokenType::ATTRIBUTE) {
        if (evaluatedResults.getIsFalseResult()) {
            return;
        }
        populateAttributesResultsList(evaluatedResults, select, results, qpsClient, synonymToDesignEntityMap);
    }
}

void Evaluator::populateAttributesResultsList(ResultTable &evaluatedResults, Select select, std::list<std::string> &results, QPSClient qpsClient, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap) {
    std::string selectSynonym = select.getReturnValues().front().getValue();
    std::unordered_set<std::string> resultsToPopulate = evaluatedResults.getSynonymResultsToBePopulated(selectSynonym);
    bool hasAlternativeAttributeName = evaluatedResults.getHasAlternativeAttributeName();
    std::string selectSynonymValue = select.getReturnValues().front().getValue();
    DesignEntity entityType = synonymToDesignEntityMap[selectSynonymValue];
    if (hasAlternativeAttributeName) {
        std::unordered_set<std::string> alternativeAttributeValueSet;
        for (auto statementNumber : resultsToPopulate) {
            std::string alternative = qpsClient.getStatementMapping(statementNumber, entityType);
            alternativeAttributeValueSet.insert(alternative);
        }

        for (const auto& alternativeAttribute : alternativeAttributeValueSet) {
            results.emplace_back(alternativeAttribute);
        }

    } else {
        for (const std::string& result : resultsToPopulate) {
            results.emplace_back(result);
        }
    }
}


bool Evaluator::evaluateNoSynonymClauses(GroupedClause noSynonymsClauses) {
    if (noSynonymsClauses.isEmpty()) {
        return false;
    }

    std::vector<std::shared_ptr<Clause>> clauses = noSynonymsClauses.getClauses();
    for (auto &c : clauses) {
        ResultTable result = c -> evaluateClause();
        if (result.getIsFalseResult()) {
            return true;
        }
    }
    return false;

}

bool Evaluator::evaluateNoSelectSynonymClauses(std::vector<GroupedClause> noSelectSynonymPresent) {

    std::sort(noSelectSynonymPresent.begin(), noSelectSynonymPresent.end(), ClauseGroupSorter());

    for (GroupedClause gc : noSelectSynonymPresent) {
        ResultTable result = gc.evaluateGroupedClause();
        if (result.getIsFalseResult()) {
            return true;
        }
    }
    return false;
}

ResultTable Evaluator::evaluateHasSelectSynonymClauses(std::vector<GroupedClause> hasSelectSynonymPresent, std::shared_ptr<Clause> &selectClause) {

    std::sort(hasSelectSynonymPresent.begin(), hasSelectSynonymPresent.end(), ClauseGroupSorter());

    ResultTable combinedResultTable;
    for (GroupedClause &gc : hasSelectSynonymPresent) {
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
    std::vector<With> withs = queryObject.getWith();

    for (const auto& w : withs) {
        std::shared_ptr<Clause> withClauseToEvaluate = ClauseCreator::createClause(w, synonymToDesignEntityMap, qpsClient);
        clauseDivider.addClauseToDivider(withClauseToEvaluate);
    }

    for (const auto& p : patterns) {
        std::shared_ptr<Clause> patternClauseToEvaluate = ClauseCreator::createClause(p, synonymToDesignEntityMap, qpsClient);
        clauseDivider.addClauseToDivider(patternClauseToEvaluate);
    }

    for (const auto& r : relationships) {
        std::shared_ptr<Clause> relationshipClauseToEvaluate = ClauseCreator::createClause(r, synonymToDesignEntityMap, qpsClient);
        clauseDivider.addClauseToDivider(relationshipClauseToEvaluate);
    }

    return clauseDivider;
}
