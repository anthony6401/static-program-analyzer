#include "SyntaxChecker.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include <stack>

#ifndef INC_22S1_CP_SPA_TEAM_17_SELECT_SYNTAX_CHECKER_H
#define INC_22S1_CP_SPA_TEAM_17_SELECT_SYNTAX_CHECKER_H

using namespace qps;

class SelectClauseSyntaxChecker : public SyntaxChecker {
private:
    std::stack<TokenType> selectSyntax;
    bool isSynonymToken(TokenType tokenType);
public:
    SelectClauseSyntaxChecker();
    ~SelectClauseSyntaxChecker();
    bool isSyntacticallyCorrect(std::vector<TokenObject> tokenizedClause);
};

#endif //INC_22S1_CP_SPA_TEAM_17_SELECT_SYNTAX_CHECKER_H