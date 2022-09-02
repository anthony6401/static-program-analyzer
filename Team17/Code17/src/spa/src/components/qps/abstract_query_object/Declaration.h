#ifndef SPA_DECLARATION_H
#define SPA_DECLARATION_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

class Declaration {
private:
    TokenType entity;
    std::string name;

public:
    Declaration();
    TokenType getEntityType();
    std::string getName();
};

#endif //SPA_DECLARATION_H
