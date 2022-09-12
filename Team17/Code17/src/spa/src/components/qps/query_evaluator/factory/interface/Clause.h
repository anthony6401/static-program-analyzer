#ifndef SPA_CLAUSE_H
#define SPA_CLAUSE_H
#include <string>
#include <set>
#include <list>
#include "components/qps/query_evaluator/RawResult.h"

class Clause {
public:
    virtual RawResult evaluateClause() = 0;
    virtual size_t getNumberOfSynonyms() = 0;
    virtual std::set<std::string> getAllSynonyms() = 0;
};

#endif //SPA_CLAUSE_H
