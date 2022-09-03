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
    SimpleToken(TokenType type, std::string value,
        int statementNumber, void (*parseFunction)(SimpleToken&, std::vector<std::string>&));
    TokenType type;
    int statementNumber;
    void (*parseFunction)(SimpleToken&, std::vector<std::string>&);
    std::string value;
    void setChildren(std::vector<SimpleToken*> tokens);
    std::vector<SimpleToken*> getChildren();

private:
    std::vector<SimpleToken*> children;

};