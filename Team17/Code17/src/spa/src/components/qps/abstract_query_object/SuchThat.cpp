#include "SuchThat.h"
#include <vector>

SuchThat::SuchThat() {
    this->relationship = TokenType{};
}


SuchThat::SuchThat(TokenType relationship, TokenObject left, TokenObject right) {
    this->relationship = relationship;
    this->left = left;
    this->right = right;
}

// to be amended
TokenType SuchThat::getRelationshipType() {
    return relationship;
}

TokenObject SuchThat::getLeft() {
    return left;
}

TokenObject SuchThat::getRight() {
    return right;
}



