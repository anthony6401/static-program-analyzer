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
    Select(TokenType returnType, std::string name);
    static TokenType getReturnType();
    static std::string getName();
    bool operator==(const Select& other) const {
        return returnType == other.returnType
            && name == other.name;
    }
};

#endif //SPA_SELECT_H
