#ifndef SPA_SUCHTHAT_H
#define SPA_SUCHTHAT_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

class SuchThat {
private:
    TokenType relationship;
    TokenObject left;
    TokenObject right;

public:
    SuchThat();
    static TokenType getRelationshipType();
    static TokenObject getLeft();
    static TokenObject getRight();
};

#endif //SPA_SUCHTHAT_H
