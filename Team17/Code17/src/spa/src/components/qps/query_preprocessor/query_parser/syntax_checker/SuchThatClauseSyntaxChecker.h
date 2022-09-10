#include "SyntaxChecker.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include <stack>

#ifndef INC_22S1_CP_SPA_TEAM_17_SUCH_THAT_SYNTAX_CHECKER_H
#define INC_22S1_CP_SPA_TEAM_17_SUCH_THAT_SYNTAX_CHECKER_H

using namespace qps;

class SuchThatClauseSyntaxChecker : public SyntaxChecker {
private:
    std::stack<TokenType> suchThatSyntax;
public:
    SuchThatClauseSyntaxChecker();
    ~SuchThatClauseSyntaxChecker();
    bool isSyntacticallyCorrect(std::vector<TokenObject> tokenizedClause);

    //{TokenType::FOLLOWS, std::vector<TokenType>{TokenType::FOLLOWS, TokenType::OPEN_BRACKET, TokenType::STMT_STMT_PARAMS, TokenType::CLOSED_BRACKET}},
    //{ TokenType::FOLLOWS_T, std::vector<TokenType>{TokenType::FOLLOWS_T, TokenType::OPEN_BRACKET, TokenType::STMT_STMT_PARAMS, TokenType::CLOSED_BRACKET} },
    //{ TokenType::PARENT, std::vector<TokenType>{TokenType::PARENT, TokenType::OPEN_BRACKET, TokenType::STMT_STMT_PARAMS, TokenType::CLOSED_BRACKET} },
    //{ TokenType::PARENT_T, std::vector<TokenType>{TokenType::PARENT_T, TokenType::OPEN_BRACKET, TokenType::STMT_STMT_PARAMS, TokenType::CLOSED_BRACKET} },
    //{ TokenType::USES, std::vector<TokenType>{TokenType::SYNONYM, TokenType::WILDCARD, TokenType::INTEGER} },
    //{ TokenType::MODIFIES, std::vector<TokenType>{TokenType::SYNONYM, TokenType::WILDCARD, TokenType::INTEGER} },
};

#endif //INC_22S1_CP_SPA_TEAM_17_SUCH_THAT_SYNTAX_CHECKER_H   
