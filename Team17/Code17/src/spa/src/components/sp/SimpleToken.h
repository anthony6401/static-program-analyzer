#pragma once

#include <vector>
#include <string>

enum class TokenType {
    TPROCEDURE,
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
    SimpleToken(TokenType type, std::string value, int statementNumber);
    TokenType type;
    std::string value;
    int statementNumber;
    void setChildren(std::vector<SimpleToken*> tokens);
    std::vector<SimpleToken*> getChildren();

private:
    std::vector<SimpleToken*> children;

};