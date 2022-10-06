#ifndef SPA_GROUPEDCLAUSE_H
#define SPA_GROUPEDCLAUSE_H

#include "vector"
#include "memory"
#include "components/qps/query_evaluator/factory/interface/Clause.h"

class GroupedClause {
private:
    std::set<std::string> synonyms;
    std::vector<std::shared_ptr<Clause>> clauses;

public:
    GroupedClause();
    void addClauseToGroup(std::shared_ptr<Clause> clause);
    ResultTable evaluateGroupedClause();
    bool isEmpty();
    std::vector<std::shared_ptr<Clause>> getClauses();
    std::set<std::string> getAllSynonyms();
    bool hasCommonSynonymWithClause(std::shared_ptr<Clause> clause);
};

#endif //SPA_GROUPEDCLAUSE_H
