#include "Select.h"
#include <vector>
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

Select::Select() : returnType(TokenType()), returnValues(std::vector<TokenObject>()) {}

Select::Select(TokenType returnType) : returnType(returnType), returnValues(std::vector<TokenObject>()) {}

Select::Select(TokenType returnType, std::vector<TokenObject> returnValues) : returnType(returnType), returnValues(returnValues) {}

Select::Select(std::string synonym) : returnType(TokenType()), returnValues(std::vector<TokenObject>()), synonym(synonym) {}

TokenType Select::getReturnType() {
    return returnType;
}

std::vector<TokenObject> Select::getReturnValues() {
    return returnValues;
}

std::string Select::getSynonym() {
    return synonym;
}

