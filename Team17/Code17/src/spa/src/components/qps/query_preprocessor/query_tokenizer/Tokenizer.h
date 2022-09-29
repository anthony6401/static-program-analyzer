#include "string"
#include "TokenType.h"
#include "unordered_map"
#include "TokenObject.h"
#include "vector"

#ifndef INC_22S1_CP_SPA_TEAM_17_TOKENIZER_H
#define INC_22S1_CP_SPA_TEAM_17_TOKENIZER_H

using namespace qps;

class Tokenizer {
private:
    std::unordered_map<std::string, TokenType> stringToTokenMap;
    bool isName(std::string s);
    bool isInteger(std::string s);
    bool isIdentity(std::string s);
    bool isExpression(std::string s);
    bool isSubExpression(std::string s);
    std::vector<std::string> convertExpressionToCharVector(std::string s);
    bool validateExpression(std::vector<std::string> expressionVector);
    // std::string trimString(const std::string& s);
    // std::vector<std::string> splitQuery(std::string query);

public:
    Tokenizer();
    std::vector<TokenObject> tokenize(std::string query);
};

#endif //INC_22S1_CP_SPA_TEAM_17_TOKENIZER_H
