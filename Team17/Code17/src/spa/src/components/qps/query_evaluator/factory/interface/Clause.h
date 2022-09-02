#ifndef SPA_CLAUSE_H
#define SPA_CLAUSE_H
#include "string"

// Clause interface that will be implemented by various clauses, to override the evaluateClause() method
class Clause {
public:
    virtual std::vector<std::string> evaluateClause() = 0;
};

#endif //SPA_CLAUSE_H
