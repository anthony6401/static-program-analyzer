#ifndef SPA_SUCHTHAT_H
#define SPA_SUCHTHAT_H

#include <vector>
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

using namespace qps;


class SuchThat {
private:
    TokenType relationship;
    TokenObject left;
    TokenObject right;

public:
    SuchThat();
    SuchThat(std::vector<TokenType> relationships, TokenObject left, TokenObject right);
    std::vector<TokenType> getRelationshipType();
    TokenObject getLeft();
    TokenObject getRight();
    bool operator==(const SuchThat& other) const {
        return relationship == other.relationship
            && left == other.left
            && right == other.right;
    }
};

#endif //SPA_SUCHTHAT_H
