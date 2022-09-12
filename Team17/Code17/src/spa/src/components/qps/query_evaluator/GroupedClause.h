#ifndef SPA_GROUPEDCLAUSE_H
#define SPA_GROUPEDCLAUSE_H

#include "vector"
#include "components/qps/query_evaluator/factory/interface/Clause.h"

// Represents Groups with common areas in:
// 1. No Synonym
// 2. Common synonyms

class GroupedClause {
private:
    std::unordered_set<std::string> synonyms;
    std::vector<std::shared_ptr<Clause>> clauses;

public:
    GroupedClause();
    void addClauseToGroup(std::shared_ptr<Clause> clause);
    bool isEmpty();
    bool hasCommonSynonymWithClause(std::shared_ptr<Clause> clause);
};

#endif //SPA_GROUPEDCLAUSE_H
