#ifndef INC_22S1_CP_SPA_TEAM_17_TOKENTYPE_H
#define INC_22S1_CP_SPA_TEAM_17_TOKENTYPE_H

namespace qps {
    enum class TokenType {
        // Relationships and Clauses
        MODIFIES,
        USES,
        FOLLOWS,
        FOLLOWS_T,
        PARENT,
        PARENT_T,
        PATTERN,
        SELECT,
        SUCH,
        THAT,
        // Lexical tokens
        NAME,
        INTEGER,
        IDENTITY, // eg. "x", "aa"
        SUBEXPRESSION, // eg. _"x+1"_
        EXPRESSION, // eg. "x+1", "x/y"
        // Symbols
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
        // Design entities
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
