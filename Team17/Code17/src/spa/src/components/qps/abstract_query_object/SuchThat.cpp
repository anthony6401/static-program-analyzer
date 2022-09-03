#include "SuchThat.h"
#include <vector>

SuchThat::SuchThat() {}


SuchThat::SuchThat(TokenType relationship, TokenObject left, TokenObject right) : relationship(relationship), left(left), right(right) {
}

// to be amended
std::vector<TokenType> SuchThat::getRelationshipType() {
    return this->relationship;
}

TokenObject SuchThat::getLeft() {
    return this->left;
}

TokenObject SuchThat::getRight() {
    return this->right;
}



