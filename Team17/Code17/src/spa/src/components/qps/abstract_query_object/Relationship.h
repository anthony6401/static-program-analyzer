#ifndef SPA_RELATIONSHIP_H
#define SPA_RELATIONSHIP_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

class Relationship {
private:
    TokenType relationship;
    TokenObject left;
    TokenObject right;

public:
    static TokenType getRelationshipType();
    static TokenObject getLeft();
    static TokenObject getRight();
};

#endif //SPA_RELATIONSHIP_H
