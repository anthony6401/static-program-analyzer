#ifndef INC_22S1_CP_SPA_TEAM_17_TOKENOBJECT_H
#define INC_22S1_CP_SPA_TEAM_17_TOKENOBJECT_H

#include <string>
#include "TokenType.h"

using namespace qps;

class TokenObject {
private:
    qps::TokenType tokenType;
    std::string tokenValue;

public:
    TokenObject();
    TokenObject(qps::TokenType tokenType, std::string value);
    qps::TokenType getTokenType();
    std::string getValue();
    bool operator==(const TokenObject &other) const {
        return tokenType == other.tokenType && tokenValue == other.tokenValue;
    }

};


#endif //INC_22S1_CP_SPA_TEAM_17_TOKENOBJECT_H
