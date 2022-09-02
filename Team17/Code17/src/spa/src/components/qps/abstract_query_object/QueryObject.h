#include <vector>
#include "SuchThat.h"
#include "Declaration.h"
#include "Pattern.h"
#include "Select.h"

#ifndef SPA_QUERY_H
#define SPA_QUERY_H

// At most one such that clause and at most one pattern clause in sequence for now
class QueryObject {
private:
    std::vector<SuchThat> relationships;
    std::vector<Declaration> declarations;
    std::vector<Pattern> patterns;
    Select select;

public:
    QueryObject();
    QueryObject(std::vector<SuchThat> relationships,
                std::vector<Declaration> declarations, std::vector<Pattern> patterns, Select select);
    std::vector<SuchThat> getRelationships();
    std::vector<Declaration> getDeclarations();
    std::vector<Pattern> getPattern();
    Select getSelect();
};

#endif //SPA_QUERY_H
