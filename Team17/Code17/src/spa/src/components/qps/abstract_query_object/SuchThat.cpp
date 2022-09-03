#include "SuchThat.h"
#include <vector>

SuchThat::SuchThat() {}


SuchThat::SuchThat(TokenType relationship, TokenObject left, TokenObject right) : relationship(relationship), left(left), right(right) {
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



