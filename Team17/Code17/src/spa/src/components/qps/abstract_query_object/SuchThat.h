#ifndef SPA_SUCHTHAT_H
#define SPA_SUCHTHAT_H

#include <vector>
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

class SuchThat {
private:
    TokenType relationship;
    TokenObject left;
    TokenObject right;

public:
    SuchThat();
    SuchThat(TokenType relationship, TokenObject left, TokenObject right);
    TokenType getRelationshipType();
    TokenObject getLeft();
    TokenObject getRight();
};

#endif //SPA_SUCHTHAT_H
