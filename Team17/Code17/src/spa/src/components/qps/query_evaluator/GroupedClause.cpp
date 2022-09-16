#include "GroupedClause.h"
#include "memory"

GroupedClause::GroupedClause() : synonyms({}), clauses({}) {}

void GroupedClause::addClauseToGroup(std::shared_ptr<Clause> clause) {
    std::set<std::string> synonymsOfClause = clause -> getAllSynonyms();
    for (std::string synonym : synonymsOfClause) {
        synonyms.insert(synonym);
    }

    clauses.emplace_back(clause);
}

bool GroupedClause::isEmpty() {
    return clauses.empty();
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

RawResult GroupedClause::evaluateGroupedClause() {
    RawResult evaluatedGroupRawResult;
   for (auto c : clauses) {
       RawResult evaluatedClause = c -> evaluateClause();
       if (evaluatedClause.getIsFalseResult()) {
           return evaluatedClause;
       }
       evaluatedGroupRawResult.combineResult(evaluatedClause);
   }
   return evaluatedGroupRawResult;
}

std::vector<std::shared_ptr<Clause>> GroupedClause::getClauses() {
    return clauses;
}

std::set<std::string> GroupedClause::getAllSynonyms() {
    return synonyms;
}
