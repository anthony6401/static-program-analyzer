#ifndef SPA_DECLARATION_H
#define SPA_DECLARATION_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

class Declaration {
private:
    qps::TokenType entity;
    std::string name;

public:
    Declaration(qps::TokenType entity, std::string name);
    qps::TokenType getEntityType();
    std::string getName();
    bool operator==(const Declaration& other) const {
        return entity == other.entity
            && name == other.name;
    }
};

#endif //SPA_DECLARATION_H
