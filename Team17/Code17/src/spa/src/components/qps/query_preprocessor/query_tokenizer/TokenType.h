#ifndef INC_22S1_CP_SPA_TEAM_17_TOKENTYPE_H
#define INC_22S1_CP_SPA_TEAM_17_TOKENTYPE_H

namespace qps {
    enum class TokenType {
        // Relationships and Clauses
        SELECT,
        SUCH,
        THAT,
        MODIFIES,
        USES,
        FOLLOWS,
        FOLLOWS_T,
        PARENT,
        PARENT_T,
        CALLS,
        CALLS_T,
        NEXT,
        NEXT_T,
        AFFECTS,
        AFFECTS_T,
        PATTERN,
        WITH,
        AND,
        // Return types and specifications
        BOOLEAN,
        TUPLE,
        ATTRIBUTE,
        // Lexical tokens
        NAME,
        INTEGER,
        NAME_WITH_QUOTATION,
        SUBEXPRESSION,
        EXPRESSION,
        // Symbols
        WILDCARD,
        COMMA,
        OPEN_BRACKET,
        CLOSED_BRACKET,
        QUOTATION_MARK,
        SEMI_COLON,
        EQUALS,
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
        EXPRESSION_SPEC,
        RESULT_CL,
        REF,
        ATTRIBUTE_SYNONYM,
        ATTRIBUTE_NAME
    };
}


#endif //INC_22S1_CP_SPA_TEAM_17_TOKENTYPE_H
