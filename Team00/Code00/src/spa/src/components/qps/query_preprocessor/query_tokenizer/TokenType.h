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
        OPEN_INVERTED_COMMA,
        CLOSED_INVERTED_COMMA,
        SEMI_COLON,

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
