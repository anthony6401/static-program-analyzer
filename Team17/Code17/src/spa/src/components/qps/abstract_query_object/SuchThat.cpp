#include "SuchThat.h"
#include <vector>

SuchThat::SuchThat() : relationship(TokenType{}) {}

SuchThat::SuchThat(TokenType relationship, TokenObject left, TokenObject right) : relationship(relationship), left(left), right(right) {
}

TokenType SuchThat::getRelationshipType() {
    return relationship;
}

TokenObject SuchThat::getLeft() {
    return left;
}

TokenObject SuchThat::getRight() {
    return right;
}



