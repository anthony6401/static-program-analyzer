#include "SyntaxChecker.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include <stack>

#ifndef INC_22S1_CP_SPA_TEAM_17_WITH_SYNTAX_CHECKER_H
#define INC_22S1_CP_SPA_TEAM_17_WITH_SYNTAX_CHECKER_H

using namespace qps;

class WithClauseSyntaxChecker : public SyntaxChecker {
private:
    std::stack<TokenType> withSyntax;
public:
    WithClauseSyntaxChecker();
    ~WithClauseSyntaxChecker();
    bool isSyntacticallyCorrect(std::vector<TokenObject> tokenizedClause);
};

#endif //INC_22S1_CP_SPA_TEAM_17_WITH_SYNTAX_CHECKER_H