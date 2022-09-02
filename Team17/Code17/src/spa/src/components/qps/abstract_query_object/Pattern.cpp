#include "Pattern.h"

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