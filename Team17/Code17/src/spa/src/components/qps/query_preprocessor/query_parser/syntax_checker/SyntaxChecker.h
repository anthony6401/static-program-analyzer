#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "unordered_map"
#include <vector>
#include <algorithm>

#ifndef INC_22S1_CP_SPA_TEAM_17_SYNTAX_CHECKER_H
#define INC_22S1_CP_SPA_TEAM_17_SYNTAX_CHECKER_H

using namespace qps;

class SyntaxChecker {
protected:
    virtual ~SyntaxChecker() = default;
    std::unordered_map<TokenType, std::vector<TokenType>>  generalSyntax = {
        {TokenType::DESIGN_ENTITY, std::vector<TokenType>{TokenType::STMT, TokenType::READ, TokenType::PRINT, TokenType::CALL, TokenType::WHILE, TokenType::IF, TokenType::ASSIGN, TokenType::VARIABLE, TokenType::CONSTANT, TokenType::PROCEDURE}},
        {TokenType::RESULT_CL, std::vector<TokenType>{TokenType::BOOLEAN, TokenType::TUPLE, TokenType::ATTRIBUTE, TokenType::SYNONYM}},
        {TokenType::RELREF, std::vector<TokenType>{TokenType::MODIFIES, TokenType::USES, TokenType::FOLLOWS, TokenType::FOLLOWS_T, TokenType::PARENT, TokenType::PARENT_T, TokenType::CALLS, TokenType::CALLS_T, TokenType::NEXT, TokenType::NEXT_T, TokenType::AFFECTS, TokenType::AFFECTS_T}},
        {TokenType::STMTREF, std::vector<TokenType>{TokenType::INTEGER, TokenType::WILDCARD, TokenType::SYNONYM}},
        {TokenType::ENTREF, std::vector<TokenType>{TokenType::NAME_WITH_QUOTATION, TokenType::WILDCARD, TokenType::SYNONYM}},
        {TokenType::REF, std::vector<TokenType>{TokenType::ATTRIBUTE, TokenType::INTEGER, TokenType::NAME_WITH_QUOTATION}},
        {TokenType::EXPRESSION_SPEC, std::vector<TokenType>{ TokenType::NAME_WITH_QUOTATION, TokenType::SUBEXPRESSION, TokenType::EXPRESSION, TokenType::WILDCARD}},
        {TokenType::SYNONYM, std::vector<TokenType>{TokenType::SELECT, TokenType::SUCH, TokenType::THAT, TokenType::MODIFIES, TokenType::USES, TokenType::FOLLOWS, TokenType::PARENT, TokenType::CALLS, TokenType::NEXT, TokenType::AFFECTS, TokenType::PATTERN, TokenType::WITH, TokenType::AND, TokenType::BOOLEAN, TokenType::NAME, TokenType::STMT, TokenType::READ, TokenType::PRINT, TokenType::CALL, TokenType::WHILE, TokenType::IF, TokenType::ASSIGN, TokenType::VARIABLE, TokenType::CONSTANT, TokenType::PROCEDURE}}

    };

public:
    virtual bool isSyntacticallyCorrect(std::vector<TokenObject> &tokenizedClause) = 0;
};

#endif //INC_22S1_CP_SPA_TEAM_17_SYNTAX_CHECKER_H