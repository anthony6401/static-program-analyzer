#include "string"
#include "TokenType.h"
#include "unordered_map"
#include "TokenObject.h"

#ifndef INC_22S1_CP_SPA_TEAM_17_TOKENIZER_H
#define INC_22S1_CP_SPA_TEAM_17_TOKENIZER_H

using namespace qps;

class Tokenizer {
private:
    std::string query;
    std::unordered_map<std::string, TokenType> stringToTokenMap;
    std::vector<TokenObject> tokenize();
    bool isName(std::string s);
    bool isInteger(std::string s);

public:
    Tokenizer(std::string query);
};

#endif //INC_22S1_CP_SPA_TEAM_17_TOKENIZER_H
