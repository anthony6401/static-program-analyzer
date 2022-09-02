#pragma once

#include <vector>
#include <string>

enum class TokenType {
    TPROCEDURE,
    TELSE,
    TSTMT,
    TREAD,
    TPRINT,
    TCALL,
    TWHILE,
    TIF,
    TASSIGN,
    TCONDEXPR,
    TVARIABLE,
    TCONSTANT,
    TCLOSE,
    TOPR
};

class SimpleToken {
public:
    SimpleToken(TokenType type, std::vector<std::string> value, int statementNumber);
    TokenType type;
    int statementNumber;
    std::vector<std::string> value;
    void setChildren(std::vector<SimpleToken*> tokens);
    std::vector<SimpleToken*> getChildren();

private:
    std::vector<SimpleToken*> children;

};