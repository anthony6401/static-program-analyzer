#include "string"
#include "TokenType.h"
#include "unordered_map"
#include "TokenObject.h"
#include "vector"

#ifndef INC_22S1_CP_SPA_TEAM_17_TOKENIZER_H
#define INC_22S1_CP_SPA_TEAM_17_TOKENIZER_H

#include <unordered_set>

using namespace qps;

class Tokenizer {
private:
    std::unordered_map<std::string, TokenType> stringToTokenMap;
    bool isName(std::string s);
    bool isInteger(std::string s);
    bool isIdentity(std::string s);
    bool isSubExpression(std::string s);
    bool isExpression(std::string s);
    bool isValidAttribute(std::string s);
    bool isTuple(std::string s);
    std::vector<std::string> convertExpressionToStringVector(const std::string& s);
    bool validateExpression(std::vector<std::string> expressionVector);
    void symbolsFoundHandler(std::string &temp, std::vector<std::string> &expressionTokens, bool &isInvalidExpression);
    void characterInExpressionHandler(char character, std::string &temp, std::vector<std::string> &expressionTokens, bool &isInvalidExpression);
public:
    Tokenizer();
    std::vector<TokenObject> tokenize(std::string query);
};

#endif //INC_22S1_CP_SPA_TEAM_17_TOKENIZER_H
