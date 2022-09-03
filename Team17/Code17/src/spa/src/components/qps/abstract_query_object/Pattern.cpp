#include "Pattern.h"

Pattern::Pattern() {}

Pattern::Pattern(std::string name, TokenObject left, TokenObject right) : name(name), left(left), right(right) {}

// to be amended
std::string Pattern::getName() {
    return "TokenType::INTEGER";
}

TokenObject Pattern::getLeft() {
    return TokenObject(TokenType::INTEGER, "");
}

TokenObject Pattern::getRight() {
    return TokenObject(TokenType::INTEGER, "");
}