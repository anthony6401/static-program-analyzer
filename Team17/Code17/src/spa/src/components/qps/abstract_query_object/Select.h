#ifndef SPA_SELECT_H
#define SPA_SELECT_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include <vector>

using namespace qps;

class Select {
private:
    TokenType returnType;
    std::vector<TokenObject> returnValues;

public:
    Select();
    Select(TokenType returnType);
    Select(TokenType returnType, std::vector<TokenObject> returnValues);
    std::string getSynonym();
    TokenType getReturnType();
    std::vector<TokenObject> getReturnValues();
    void setReturnTypeToSynonym();
    bool operator==(const Select& other) const {
        return returnValues == other.returnValues &&
        returnType == other.returnType;
    }
};

#endif //SPA_SELECT_H
