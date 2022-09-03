#include "Select.h"

#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

Select::Select() {
    this->returnType = TokenType::WILDCARD;
}

Select::Select(TokenType returnType, std::string name) {
    this->returnType = returnType;
    this->name = name;
}

TokenType Select::getReturnType() {
    return this->returnType;
}

std::string Select::getName() {
    return this->name;
}