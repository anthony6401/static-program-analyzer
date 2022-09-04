#include "Pattern.h"

Pattern::Pattern() {}

Pattern::Pattern(std::string synonym, TokenObject left, TokenObject right) : synonym(synonym), left(left), right(right) {}

// to be amended
std::string Pattern::getSynonym() {
    return "TokenType::INTEGER";
}

TokenObject Pattern::getLeft() {
    return TokenObject(TokenType::INTEGER, "");
}

TokenObject Pattern::getRight() {
    return TokenObject(TokenType::INTEGER, "");
}