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
        NAME_WITH_QUOTATION,
// Special symbols
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
        PROCEDURE,
        // Syntax Types - may be removed in future sprints
        DECLARATION,
        SYNONYM,
        DESIGN_ENTITY,
        RELREF,
        STMTREF,
        ENTREF
    };
}


#endif //INC_22S1_CP_SPA_TEAM_17_TOKENTYPE_H
