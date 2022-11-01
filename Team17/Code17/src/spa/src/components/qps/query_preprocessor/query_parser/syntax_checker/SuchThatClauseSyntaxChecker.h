#include "SyntaxChecker.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include <stack>
#include <tuple>

#ifndef INC_22S1_CP_SPA_TEAM_17_SUCH_THAT_SYNTAX_CHECKER_H
#define INC_22S1_CP_SPA_TEAM_17_SUCH_THAT_SYNTAX_CHECKER_H

using namespace qps;

class SuchThatClauseSyntaxChecker : public SyntaxChecker {
private:
    std::stack<TokenType> suchThatSyntax;
    std::tuple<int, std::vector<TokenObject>> getRelationshipClauseTokens(std::vector<TokenObject> &tokenizedClause, int relrefIndex);
    bool isRelationshipSyntacticallyCorrect(std::vector<TokenObject> &relationshipClauseTokens, TokenType relrefToken);
    bool hasValidRelationshipSyntax(std::vector<TokenObject> &relationshipClauseTokens);
    bool hasValidUsesModifiesSyntax(std::vector<TokenObject> &relationshipClauseTokens);
    bool isSynonymToken(TokenType tokenType);
    void hasEntrefEntrefSyntax();
    void hasStmtrefStmtrefSyntax();
public:
    SuchThatClauseSyntaxChecker();
    ~SuchThatClauseSyntaxChecker();
    bool isSyntacticallyCorrect(std::vector<TokenObject> &tokenizedClause);

};

#endif //INC_22S1_CP_SPA_TEAM_17_SUCH_THAT_SYNTAX_CHECKER_H   
