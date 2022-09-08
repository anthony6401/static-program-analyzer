#include "SuchThat.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include <vector>

//SuchThat::SuchThat() {}

SuchThat::SuchThat(TokenType relationship, TokenObject left, TokenObject right) : relationship(relationship), left(left), right(right) {
}

// to be amended
TokenType SuchThat::getRelationshipType() {
    return this->relationship;
}

TokenObject SuchThat::getLeft() {
    return this->left;
}

TokenObject SuchThat::getRight() {
    return this->right;
}



