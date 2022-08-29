#include "TokenObject.h"

using namespace qps;

TokenObject::TokenObject(TokenType tokenType, std::string value) {
    this->tokenized_value = value;
    this->tokenized_type = tokenType;
}
