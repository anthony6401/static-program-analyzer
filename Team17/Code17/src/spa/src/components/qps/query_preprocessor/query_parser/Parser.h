#include "string"
#include "unordered_map"
#include "syntax_checker/SyntaxChecker.h"
#include "syntax_checker/DeclarationClauseSyntaxChecker.h"
#include "syntax_checker/SelectClauseSyntaxChecker.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include <vector>

#ifndef INC_22S1_CP_SPA_TEAM_17_PARSER_H
#define INC_22S1_CP_SPA_TEAM_17_PARSER_H

using namespace qps;

class Parser {
private:
    std::vector<TokenObject> tokenizedQuery;
    std::vector<std::vector<TokenObject>> groupQueryIntoClause();
    bool isSyntacticallyCorrect(std::vector<TokenObject> tokenizedClause, SyntaxChecker* checker);
    int getTokenIndex(TokenType token, std::vector<TokenType> tokenTypes);
    std::vector<TokenType> getTokenTypes();

public:
    Parser(std::vector<TokenObject> tokenizedQuery);
    std::string parse();
    std::vector<TokenObject> getTokenizedQuery();
};

#endif //INC_22S1_CP_SPA_TEAM_17_PARSER_H
