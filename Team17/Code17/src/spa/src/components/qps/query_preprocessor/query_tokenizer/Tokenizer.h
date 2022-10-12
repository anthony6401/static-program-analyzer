#include "string"
#include "TokenType.h"
#include "unordered_map"
#include "TokenObject.h"
#include "vector"
#include <unordered_set>
#include <stack>

#ifndef INC_22S1_CP_SPA_TEAM_17_TOKENIZER_H
#define INC_22S1_CP_SPA_TEAM_17_TOKENIZER_H



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
    bool isValidTuple(std::string &currString, std::string &currValue);
    void validateTupleValueHandler(std::string &currString, std::string &currValue, size_t commaIndex, bool &returnFalse);
    std::vector<std::string> convertExpressionToStringVector(const std::string& s);
    bool validateExpression(std::vector<std::string> expressionVector);
    void symbolsFoundHandler(std::string &temp, std::vector<std::string> &expressionTokens, bool &isInvalidExpression);
    void characterInExpressionHandler(char character, std::string &temp, std::vector<std::string> &expressionTokens, bool &isInvalidExpression);
    void nonBracketInExpressionVectorHandler(std::string &string, std::string &prev, bool &isPrevName, bool &isPrevInteger, std::stack<std::string> &expressionStack, bool &returnFalse);
    void stringInExpressionVectorHandler(std::string &string, std::string &prev, bool &isPrevName, bool &isPrevInteger, std::stack<std::string> &expressionStack, bool &returnFalse);
public:
    Tokenizer();
    std::vector<TokenObject> tokenize(std::string query);
};

#endif //INC_22S1_CP_SPA_TEAM_17_TOKENIZER_H
