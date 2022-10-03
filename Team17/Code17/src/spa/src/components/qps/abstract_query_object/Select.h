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
    //To remove
    std::string synonym;

public:
    Select();
    Select(std::string synonym);
    Select(TokenType returnType);
    Select(TokenType returnType, std::vector<TokenObject> returnValues);
    std::string getSynonym();
    TokenType getReturnType();
    std::vector<TokenObject> getReturnValues();
    bool operator==(const Select& other) const {
        return synonym == other.synonym
        && returnValues == other.returnValues &&
        returnType == other.returnType;
    }
};

#endif //SPA_SELECT_H
