#include "TokenObject.h"

using namespace qps;

TokenObject::TokenObject(TokenType tokenType, std::string value) {
    this->tokenType = tokenType;
    this->tokenValue = value;
}

TokenType TokenObject::getTokenType() {
    return this->tokenType;
}

std::string TokenObject::getValue() {
    return this->tokenValue;
}
