#ifndef INC_22S1_CP_SPA_TEAM_17_TOKENOBJECT_H
#define INC_22S1_CP_SPA_TEAM_17_TOKENOBJECT_H

#include <string>
#include "TokenType.h"

using namespace qps;

class TokenObject {
private:
    TokenType tokenType;
    std::string tokenValue;

public:
    TokenObject(TokenType tokenType, std::string value);
    TokenType getTokenType();
    std::string getTokenValue();
};


#endif //INC_22S1_CP_SPA_TEAM_17_TOKENOBJECT_H
