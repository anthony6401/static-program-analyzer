#include "Pattern.h"

Pattern::Pattern() {}

Pattern::Pattern(std::string synonym, TokenObject left, TokenObject right) : synonym(synonym), left(left), right(right) {}

std::string Pattern::getSynonym() {
    return synonym;
}

TokenObject Pattern::getLeft() {
    return left;
}

TokenObject Pattern::getRight() {
    return right;
}