#pragma once

#include <vector>
#include <string>

enum class TokenType {
    tProcedure,
    tStmt,
    tRead,
    tPrint,
    tCall,
    tWhile,
    tIf,
    tAssign,
    tCondExpr,
    tVariable,
    tConstant
};

class SimpleToken {
    public:
        SimpleToken(TokenType type, std::string value);
        TokenType type;
        std::string value;
        int statementNumber;
        void setChilds(std::vector<SimpleToken*> tokens);
        std::vector<SimpleToken*> getChilds();

    private:
        std::vector<SimpleToken*> childs;
};
