#ifndef SPA_DECLARATION_H
#define SPA_DECLARATION_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

// Implementing as hashmap, since look up for entity type is O(1)
// Class is currently unused
class Declaration {
private:
    TokenType entity;
    std::string name;

public:
    Declaration(TokenType entity, std::string name);
    TokenType getEntityType();
    std::string getName();
};

#endif //SPA_DECLARATION_H
