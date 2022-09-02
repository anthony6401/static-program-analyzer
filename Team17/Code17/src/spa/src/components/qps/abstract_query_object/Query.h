#include <vector>
#include "Relationship.h"
#include "Declaration.h"

#ifndef SPA_QUERY_H
#define SPA_QUERY_H

// At most one such that clause and at most one pattern clause in sequence
class Query {
private:
    Relationship relationship;
    std::vector<Declaration> declarations;
};

#endif //SPA_QUERY_H
