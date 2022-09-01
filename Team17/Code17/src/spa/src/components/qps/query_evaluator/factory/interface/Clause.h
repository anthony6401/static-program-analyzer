#ifndef SPA_CLAUSE_H
#define SPA_CLAUSE_H
#include "string"

// Clause interface that will be implemented by various clauses, to override the evaluate() method
class Clause {
public:
    virtual std::string evaluateClause() = 0;
};

#endif //SPA_CLAUSE_H
