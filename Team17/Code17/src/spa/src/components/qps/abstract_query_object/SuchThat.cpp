#include "SuchThat.h"

// to be amended
TokenType SuchThat::getRelationshipType() {
    return TokenType::INTEGER;
}

TokenObject SuchThat::getLeft() {
    return TokenObject(TokenType::INTEGER, "");
}

TokenObject SuchThat::getRight() {
    return TokenObject(TokenType::INTEGER, "");
}



