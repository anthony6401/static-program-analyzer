#ifndef SPA_SELECT_H
#define SPA_SELECT_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

// Only synonym
class Select {
private:
    TokenType returnType;
    std::string name;

public:
    Select();
    // static TokenType getReturnType();
    std::string getName();
};

#endif //SPA_SELECT_H
