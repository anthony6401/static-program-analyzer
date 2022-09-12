#include "GroupedClause.h"
#include "memory"

GroupedClause::GroupedClause() : synonyms({}), clauses({}) {}

void GroupedClause::addClauseToGroup(std::shared_ptr<Clause> clause) {
    std::set<std::string> synonymsOfClause = clause->getAllSynonyms();
    synonyms.insert(synonymsOfClause.begin(), synonymsOfClause.end());
    clauses.emplace_back(clause);
}

bool GroupedClause::isEmpty() {
    return clauses.empty();
}

bool GroupedClause::hasCommonSynonymWithClause(std::shared_ptr<Clause> clause) {
    std::set<std::string> synonymsOfClause = clause->getAllSynonyms();
    auto synonymsOfClauseIterator = synonymsOfClause.begin();
    auto synonymsIterator = synonyms.begin();
    while (synonymsOfClauseIterator != synonymsOfClause.end() && synonymsIterator != synonyms.end()) {
        if (*synonymsIterator < *synonymsOfClauseIterator) {
            ++synonymsIterator;
        } else if (*synonymsOfClauseIterator < *synonymsIterator) {
            ++synonymsOfClauseIterator;
        } else {
            return true;
        }
    }
    return false;
}

std::vector<std::shared_ptr<Clause>> GroupedClause::getClauses() {
    return clauses;
}

std::set<std::string> GroupedClause::getAllSynonyms() {
    return synonyms;
}
