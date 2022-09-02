#include <vector>
#include "SuchThat.h"
#include "Declaration.h"
#include "Pattern.h"
#include "Select.h"

#ifndef SPA_QUERY_H
#define SPA_QUERY_H

// At most one such that clause and at most one pattern clause in sequence
class QueryObject {
private:
    SuchThat relationship;
    std::vector<Declaration> declarations;
    Pattern pattern;
    Select select;

public:
    QueryObject();
};

#endif //SPA_QUERY_H
