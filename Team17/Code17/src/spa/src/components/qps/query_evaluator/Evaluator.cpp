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
        if (evaluatedResult.getIsFalseResult() || evaluatedResult.isEmptyResult()) {
            results.emplace_back("none");
            isNoneResult = true;
            break;
        }
        evaluatedResultsList.push_back(evaluatedResult);
    }

    // Results are not empty or is true
    if (!isNoneResult) {
        // join Raw results
        std::unordered_set<std::string> joinedRawResults = joinRawResults(
                evaluatedResultsList, queryObject.getSelect().getSynonym(), synonymToDesignEntityMap, qpsClient);
        // emplace results from joinedRawResults
    }
}

// Assuming maximum of 2 clauses
std::vector<std::string> Evaluator::findCommonSynonyms(std::vector<std::string> firstSynonymList, std::vector<std::string> secSynonymList) {
    std::vector<std::string> commonSynonyms;
    std::vector<std::string> smallerList = firstSynonymList.size() < secSynonymList.size() ? firstSynonymList : secSynonymList;
    std::vector<std::string> largerList = firstSynonymList.size() >= secSynonymList.size() ? firstSynonymList : secSynonymList;
    std::unordered_set<std::string> convertedList(largerList.begin(), largerList.end());
    for (std::string synonym : smallerList) {
        if (convertedList.count(synonym)) {
            commonSynonyms.push_back(synonym);
        }
    }
    return commonSynonyms;
}

int Evaluator::getSelectSynonymIndex(std::vector<std::string> synonymList, std::string selectSynonym) {
    int index;
    auto it = find(synonymList.begin(), synonymList.end(), selectSynonym);
    index = it - synonymList.begin();
    return index;
}

std::unordered_set<std::string> mergeCommonSynonymValues(std::vector<std::string> firstList, std::vector<std::string> secondList) {

}

// Might be boolean result, {{x}, {y}..} or {{1. x}, {2, y}..}
// {{x}, {y}, {z}} -> {x, y, z}
std::unordered_set<std::string> Evaluator::joinRawResults(std::vector<RawResult> rawResultsList, std::string selectSynonym, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient) {
    std::unordered_set<std::string> joinedResults;
    // Single clause or Select clause query
    if (rawResultsList.size() == 1) {
        std::vector<std::vector<std::string>> results = rawResultsList.front().resultsList;

        // No synonyms clauses
        if (rawResultsList.front().getIsBooleanResult()) {
            // True result, fetch all select synonym design entity
            std::shared_ptr<Clause> selectAllClause = ClauseCreator::createClause(selectSynonym, synonymToDesignEntityMap, qpsClient);
            RawResult selectAllResult = selectAllClause->evaluateClause();
            for (auto singleValue : selectAllResult.resultsList) {
                joinedResults.insert(singleValue.front());
            }
            return joinedResults;
        }
        // Select synonym present
        if (find(rawResultsList.front().synonymsList.begin(),
                 rawResultsList.front().synonymsList.end(), selectSynonym) != rawResultsList.front().synonymsList.end()) {
            // 1 Synonym present, {{x}, {y}...}
            if (rawResultsList.front().getSynonymCount() == 1) {
                if (rawResultsList.front().synonymsList.front() == selectSynonym) {
                    for (auto singleValue : results) {
                        joinedResults.insert(singleValue.front());
                    }
                }
                return joinedResults;
            }
            // 2 synonyms present, {{1, y}, {2, x}}
            if (rawResultsList.front().getSynonymCount() == 2) {
                // Get index of select synonym from synonymList, 0 or 1
                int indexOfSelectSynonym = Evaluator::getSelectSynonymIndex(rawResultsList.front().synonymsList, selectSynonym);
                for (auto result: results) {
                    joinedResults.insert(result.at(indexOfSelectSynonym));
                }
                return joinedResults;
            }
        }
        // Select synonym not present, check for empty result or false clause
        // Not empty, fetch all select synonym design entity
        if (!rawResultsList.front().isEmptyResult()) {
            std::shared_ptr<Clause> selectAllClause = ClauseCreator::createClause(selectSynonym, synonymToDesignEntityMap, qpsClient);
            RawResult selectAllResult = selectAllClause->evaluateClause();
            for (auto singleValue : selectAllResult.resultsList) {
                joinedResults.insert(singleValue.front());
            }
            return joinedResults;
        }
    // Multi-clause queries
    } else {
        RawResult firstClauseResults = rawResultsList.front();
        RawResult secondClauseResults = rawResultsList.back();
        bool isSelectFoundInFirst = find(firstClauseResults.synonymsList.begin(),
                                         firstClauseResults.synonymsList.end(), selectSynonym) != firstClauseResults.synonymsList.end();
        bool isSelectFoundInSecond = find(secondClauseResults.synonymsList.begin(),
                                          secondClauseResults.synonymsList.end(), selectSynonym) != secondClauseResults.synonymsList.end();
        std::vector<std::string> commonSynonyms = Evaluator::findCommonSynonyms(
                firstClauseResults.synonymsList, secondClauseResults.synonymsList);
        // No Synonym clauses, Both boolean true
        if (firstClauseResults.getIsBooleanResult() && secondClauseResults.getIsBooleanResult()) {
            std::shared_ptr<Clause> selectAllClause = ClauseCreator::createClause(
                    selectSynonym, synonymToDesignEntityMap, qpsClient);
            RawResult selectAllResult = selectAllClause->evaluateClause();
            for (auto singleValue : selectAllResult.resultsList) {
                joinedResults.insert(singleValue.front());
            }
            return joinedResults;
        }
        // Select synonym not found in both clauses
        if (!isSelectFoundInFirst && !isSelectFoundInSecond) {
            std::shared_ptr<Clause> selectAllClause = ClauseCreator::createClause(
                    selectSynonym, synonymToDesignEntityMap, qpsClient);
            RawResult selectAllResult = selectAllClause->evaluateClause();
            for (auto singleValue : selectAllResult.resultsList) {
                joinedResults.insert(singleValue.front());
            }
            return joinedResults;
        }

        // Select synonym only present in one clause
        if (isSelectFoundInFirst && !isSelectFoundInSecond) {
            if (!commonSynonyms.empty()) {
                for (auto c : commonSynonyms) {
                    if (firstClauseResults.getIsSingleConstraints()) {
                        if (secondClauseResults.getIsSingleConstraints()) {

                        }
                    } else {

                    }


                }
            }
        }

//        if (!isSelectFoundInFirst && isSelectFoundInSecond) {
//            if (!commonSynonyms.empty()) {
//                for (auto c : commonSynonyms) {
//                    if ()
//
//                }
//            }
//        }

        // 1 Synonym present, {{x}, {y}...}
        // 2 synonyms present, {{1, y}, {2, x}}


        // Select synonym present in both clauses

        // no synonym clauses -> evaluate select / select not present in both -> evaluate select
        // Select present in first
            // check if second has results
            // check for common synonyms
            // return corresponding select based on synonyms present
        // Select present in second
        // check if first has results
        // check for common synonyms
        // return corresponding select based on synonyms present

        //
    }

    return joinedResults;
}



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

