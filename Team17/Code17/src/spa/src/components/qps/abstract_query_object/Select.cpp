#include "Select.h"

#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

TokenType Select::getReturnType() {
    return TokenType::INTEGER;
}

std::string Select::getName() {
    return "";
}