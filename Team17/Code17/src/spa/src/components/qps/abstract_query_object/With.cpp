#include "With.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include <vector>

With::With() : leftType(TokenType{}), rightType(TokenType{}), left(std::vector<TokenObject>()), right(std::vector<TokenObject>()) {}

With::With(TokenType leftType, TokenType rightType, std::vector<TokenObject> left, std::vector<TokenObject> right) : leftType(leftType), rightType(rightType), left(left), right(right) {
}

TokenType With::getLeftType() {
    return leftType;
}

TokenType With::getRightType() {
    return rightType;
}

std::vector<TokenObject> With::getLeft() {
    return left;
}

std::vector<TokenObject> With::getRight() {
    return right;
}

