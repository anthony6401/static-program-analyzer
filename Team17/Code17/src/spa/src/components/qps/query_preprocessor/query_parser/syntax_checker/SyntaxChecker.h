#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "unordered_map"
#include <vector>

#ifndef INC_22S1_CP_SPA_TEAM_17_SYNTAX_CHECKER_H
#define INC_22S1_CP_SPA_TEAM_17_SYNTAX_CHECKER_H

using namespace qps;

class SyntaxChecker {
protected:
    virtual ~SyntaxChecker() = default;
    std::unordered_map<TokenType, std::vector<TokenType>>  generalSyntax = {
        {TokenType::DESIGN_ENTITY, std::vector<TokenType>{TokenType::STMT, TokenType::READ, TokenType::PRINT, TokenType::CALL, TokenType::WHILE, TokenType::IF, TokenType::ASSIGN, TokenType::VARIABLE, TokenType::CONSTANT, TokenType::PROCEDURE}},
        {TokenType::RELREF, std::vector<TokenType>{TokenType::FOLLOWS, TokenType::FOLLOWS_T, TokenType::PARENT, TokenType::PARENT_T, TokenType::USES, TokenType::MODIFIES}},
        {TokenType::STMTREF, std::vector<TokenType>{TokenType::SYNONYM, TokenType::WILDCARD, TokenType::INTEGER}},
        {TokenType::ENTREF, std::vector<TokenType>{TokenType::SYNONYM, TokenType::WILDCARD, TokenType::NAME_WITH_QUOTATION}},
        {TokenType::SYNONYM, std::vector<TokenType>{TokenType::NAME}}

        // add for each rs type

    };
public:
    virtual bool isSyntacticallyCorrect(std::vector<TokenObject> tokenizedClause) = 0;
};

#endif //INC_22S1_CP_SPA_TEAM_17_SYNTAX_CHECKER_H