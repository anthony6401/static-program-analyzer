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
        NAME_WITH_QUOTATION, // eg. "x", "aa"
        SUBEXPRESSION, // eg. _"x+1"_
        EXPRESSION, // eg. "x+1", "x/y"
        // Symbols
        WILDCARD,
        COMMA,
        OPEN_BRACKET,
        CLOSED_BRACKET,
        QUOTATION_MARK,
        SEMI_COLON,
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
        PROCEDURE,
        // Syntax Types - may be removed in future sprints
        SYNONYM,
        DESIGN_ENTITY,
        RELREF,
        STMTREF,
        ENTREF,
        EXPRESSION_SPEC
    };
}


#endif //INC_22S1_CP_SPA_TEAM_17_TOKENTYPE_H
