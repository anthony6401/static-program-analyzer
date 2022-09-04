#include "string"
#include "unordered_map"
#include "syntax_checker/SyntaxChecker.h"
#include "syntax_checker/DeclarationClauseSyntaxChecker.h"
#include "syntax_checker/SelectClauseSyntaxChecker.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/abstract_query_object/Declaration.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/qps/abstract_query_object/SuchThat.h"
#include "components/qps/abstract_query_object/Pattern.h"
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
    std::vector<TokenType> getTokenTypes(std::vector<TokenObject> tokenObjects);
    std::vector<Declaration> parseTokensIntoDeclarationObjects(std::unordered_map<std::string, TokenType> mappedSynonyms);
    Select parseTokensIntoSelectObject(std::vector<TokenObject> selectTokens, std::unordered_map<std::string, TokenType> mappedSynonyms);
    std::vector<SuchThat> parseTokensIntoSuchThatObjects();
    std::vector<Pattern> parseTokensIntoPatternObjects();
    std::unordered_map<std::string, TokenType> mapSynonymToDesignEntity(std::vector<TokenObject> declarations);

public:
    Parser(std::vector<TokenObject> tokenizedQuery);
    QueryObject parse();
    std::vector<TokenObject> getTokenizedQuery();
};

#endif //INC_22S1_CP_SPA_TEAM_17_PARSER_H
