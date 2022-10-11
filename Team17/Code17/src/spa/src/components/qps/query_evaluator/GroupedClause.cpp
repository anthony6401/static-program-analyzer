#include "GroupedClause.h"
#include "memory"
#include "iostream"

GroupedClause::GroupedClause() : synonyms({}), clauses({}) {}

std::vector<std::shared_ptr<Clause>> GroupedClause::getClauses() {
    return clauses;
}

std::set<std::string> GroupedClause::getAllSynonyms() {
    return synonyms;
}


bool GroupedClause::hasCommonSynonymWithClause(std::shared_ptr<Clause> &clause) {
    std::set<std::string> synonymsOfClause = clause -> getAllSynonyms();
    for (const auto& s : synonymsOfClause) {
        for (const auto& sgc : synonyms) {
            if (s == sgc) {
                return true;
            }
        }
    }
    return false;
}

void GroupedClause::addClauseToGroup(std::shared_ptr<Clause> &clause) {
    std::set<std::string> synonymsOfClause = clause -> getAllSynonyms();
    for (const std::string& synonym : synonymsOfClause) {
        synonyms.insert(synonym);
    }

    clauses.emplace_back(clause);
}

bool GroupedClause::isEmpty() {
    return clauses.empty();
}

ResultTable GroupedClause::evaluateGroupedClause() {
    ResultTable evaluatedGroupRawResult;
    for (const auto& c : clauses) {
        ResultTable evaluatedClause = c -> evaluateClause();
        if (evaluatedClause.getIsFalseResult()) {
            return evaluatedClause;
        }
        evaluatedGroupRawResult.combineResult(evaluatedClause);
    }
    return evaluatedGroupRawResult;
}

void GroupedClause::mergeGroupedClause(GroupedClause &clause_group) {
    auto other_synonyms = clause_group.getAllSynonyms();
    auto other_clauses = clause_group.getClauses();

    synonyms.insert(other_synonyms.begin(), other_synonyms.end());
    clauses.insert(clauses.end(), other_clauses.begin(), other_clauses.end());
}


bool GroupedClause::isConnected(GroupedClause &clause_group) {
    // find common element
    auto other_synonyms = clause_group.getAllSynonyms();
    auto synonyms_it = synonyms.begin();
    auto other_it = other_synonyms.begin();
    while (synonyms_it!=synonyms.end() && other_it!=other_synonyms.end()) {
        if (*synonyms_it < *other_it) {
            ++synonyms_it;
        } else if (*other_it < *synonyms_it) {
            ++other_it;
        } else {
            return true;
        }
    }
    return false;
}
