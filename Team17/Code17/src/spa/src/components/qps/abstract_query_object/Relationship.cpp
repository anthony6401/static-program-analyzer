#include "Relationship.h"

// to be amended
TokenType Relationship::getRelationshipType() {
    return TokenType::INTEGER;
}

TokenObject Relationship::getLeft() {
    return TokenObject(TokenType::INTEGER, "");
}

TokenObject Relationship::getRight() {
    return TokenObject(TokenType::INTEGER, "");
}



