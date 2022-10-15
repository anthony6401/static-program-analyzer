#include "Select.h"

Select::Select() : returnType(TokenType()), returnValues(std::vector<TokenObject>()) {}

Select::Select(TokenType returnType) : returnType(returnType), returnValues(std::vector<TokenObject>()) {}

Select::Select(TokenType returnType, std::vector<TokenObject> returnValues) : returnType(returnType), returnValues(returnValues) {}

TokenType Select::getReturnType() {
    return returnType;
}

std::vector<TokenObject> Select::getReturnValues() {
    return returnValues;
}

void Select::setReturnTypeToSynonym() {
    this->returnType = TokenType::SYNONYM;
}
