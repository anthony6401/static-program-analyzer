#include "SyntaxChecker.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "models/Entity/DesignEntity.h"
#include <stack>
#include <unordered_map>

#ifndef INC_22S1_CP_SPA_TEAM_17_PATTERN_SYNTAX_CHECKER_H
#define INC_22S1_CP_SPA_TEAM_17_PATTERN_SYNTAX_CHECKER_H

using namespace qps;

class PatternClauseSyntaxChecker : public SyntaxChecker {
private:
    std::stack<TokenType> patternSyntax;
    bool isEntrefToken(TokenType tokenType);

public:
    PatternClauseSyntaxChecker();
    ~PatternClauseSyntaxChecker();
    bool isSyntacticallyCorrect(std::vector<TokenObject> tokenizedClause);
};

#endif //INC_22S1_CP_SPA_TEAM_17_PATTERN_SYNTAX_CHECKER_H