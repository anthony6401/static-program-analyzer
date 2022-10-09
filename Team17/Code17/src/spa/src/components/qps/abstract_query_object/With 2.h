#ifndef SPA_WITH_H
#define SPA_WITH_H

#include <vector>
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

using namespace qps;


class With {
private:
    TokenType leftType;
    TokenType rightType;
    std::vector<TokenObject> left;
    std::vector<TokenObject> right;

public:
    With();
    With(TokenType leftType, TokenType rightType, std::vector<TokenObject> left, std::vector<TokenObject> right);
    TokenType getLeftType();
    TokenType getRightType();
    std::vector<TokenObject> getLeft();
    std::vector<TokenObject> getRight();
    bool operator==(const With& other) const {
        return leftType == other.leftType
            && rightType == other.rightType
            && left == other.left
            && right == other.right;
    }
};

#endif //SPA_WITH_H
