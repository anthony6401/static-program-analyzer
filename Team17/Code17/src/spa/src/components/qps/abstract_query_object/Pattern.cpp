#include "Pattern.h"

Pattern::Pattern() {}


std::string Pattern::getSynonym() {
    return synonym;
}

TokenObject Pattern::getLeft() {
    return left;
}

TokenObject Pattern::getRight() {
    return right;
}
