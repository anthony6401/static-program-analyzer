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
    void setChilds(std::vector<SimpleToken*> tokens);
    std::vector<SimpleToken*> getChilds();

private:
    std::vector<SimpleToken*> childs;
};