#include "Select.h"

#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

Select::Select() {}

Select::Select(std::string synonym) {
    this->synonym = synonym;
}

std::string Select::getSynonym() {
    return synonym;
}

