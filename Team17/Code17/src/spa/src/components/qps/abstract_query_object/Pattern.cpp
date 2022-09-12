#include "Pattern.h"

Pattern::Pattern() {}


Pattern::Pattern(std::string synonym, TokenObject left, TokenObject right) {
    this->synonym = synonym;
    this->left = left;
    this->right = right;
}

std::string Pattern::getSynonym() {
    return synonym;
}

TokenObject Pattern::getLeft() {
    return left;
}

TokenObject Pattern::getRight() {
    return right;
}
