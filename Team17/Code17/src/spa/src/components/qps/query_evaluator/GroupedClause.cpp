#include "GroupedClause.h"
#include "memory"

GroupedClause::GroupedClause() : synonyms({}), clauses({}) {}

std::vector<std::shared_ptr<Clause>> GroupedClause::getClauses() {
    return clauses;
}

std::set<std::string> GroupedClause::getAllSynonyms() {
    return synonyms;
}


bool GroupedClause::hasCommonSynonymWithClause(std::shared_ptr<Clause> clause) {
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

void GroupedClause::addClauseToGroup(std::shared_ptr<Clause> clause) {
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


