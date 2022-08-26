#ifndef INC_22S1_CP_SPA_TEAM_17_TOKENTYPE_H
#define INC_22S1_CP_SPA_TEAM_17_TOKENTYPE_H

namespace qps {
    enum class TokenType {
        SELECT,
        SUCH,
        THAT,

        MODIFIES,
        USES,

        NAME,
        INTEGER,

        UNDERSCORE,
        COMMA,
        OPEN_BRACKET,
        CLOSED_BRACKET,
        QUOTATION_MARK,
        SEMI_COLON,
        PLUS,
        MINUS,
        DIVIDE,
        MULTIPLY,
        PERCENTAGE,

        STMT,
        READ,
        PRINT,
        CALL,
        WHILE,
        IF,
        ASSIGN,
        VARIABLE,
        CONSTANT,
        PROCEDURE
    };
}


#endif //INC_22S1_CP_SPA_TEAM_17_TOKENTYPE_H
