#include "unordered_map"
#include "syntax_checker/SyntaxChecker.h"
#include "syntax_checker/DeclarationClauseSyntaxChecker.h"
#include "syntax_checker/SelectClauseSyntaxChecker.h"
#include "syntax_checker/SuchThatClauseSyntaxChecker.h"
#include "syntax_checker/PatternClauseSyntaxChecker.h"
#include "syntax_checker/WithClauseSyntaxChecker.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/qps/abstract_query_object/SuchThat.h"
#include "components/qps/abstract_query_object/Pattern.h"
#include "components/qps/abstract_query_object/With.h"
#include "models/Entity/DesignEntity.h"
#include <vector>
#include <tuple>

#ifndef INC_22S1_CP_SPA_TEAM_17_PARSER_H
#define INC_22S1_CP_SPA_TEAM_17_PARSER_H

using namespace qps;

class Parser {
private:
    std::vector<TokenObject> tokenizedQuery;
    std::unordered_map<TokenType, DesignEntity> tokenToDesignEntity = {
        {TokenType::STMT, DesignEntity::STMT},
        {TokenType::READ, DesignEntity::READ},
        {TokenType::PRINT, DesignEntity::PRINT},
        {TokenType::CALL, DesignEntity::CALL},
        {TokenType::WHILE, DesignEntity::WHILE},
        {TokenType::IF, DesignEntity::IF},
        {TokenType::ASSIGN, DesignEntity::ASSIGN},
        {TokenType::VARIABLE, DesignEntity::VARIABLE},
        {TokenType::CONSTANT, DesignEntity::CONSTANT},
        {TokenType::PROCEDURE, DesignEntity::PROCEDURE}
    };
    std::vector<TokenType> relationshipTokens{
        TokenType::MODIFIES, TokenType::USES, TokenType::FOLLOWS,
        TokenType::FOLLOWS_T, TokenType::PARENT, TokenType::PARENT_T,
        TokenType::CALLS, TokenType::CALLS_T, TokenType::NEXT,
        TokenType::NEXT_T, TokenType::AFFECTS, TokenType::AFFECTS_T
    };
    std::vector<TokenType> designEntityTokens{
        TokenType::STMT, TokenType::READ, TokenType::PRINT, TokenType::CALL, 
        TokenType::WHILE, TokenType::IF, TokenType::ASSIGN, 
        TokenType::VARIABLE, TokenType::CONSTANT, TokenType::PROCEDURE
    };
    std::vector<std::vector<TokenObject>> groupQueryIntoClause();
    bool isSyntacticallyCorrect(std::vector<TokenObject> &tokenizedClause, SyntaxChecker* checker);
    std::tuple<int, std::unordered_map<std::string, DesignEntity>> mapSynonymToDesignEntity(std::vector<TokenObject> &declarations);
    Select parseTokensIntoSelectObject(std::vector<TokenObject> &selectTokens);
    std::vector<SuchThat> parseTokensIntoSuchThatObjects(std::vector<TokenObject> &relationshipTokens);
    std::vector<Pattern> parseTokensIntoPatternObjects(std::vector<TokenObject> &patternTokens);
    std::vector<With> parseTokensIntoWithObjects(std::vector<TokenObject> &withTokens);
    bool isRelationshipToken(TokenType token);
    bool isDesignEntityToken(TokenType token);
    std::vector<TokenObject> parseTupleIntoIndividualTokens(std::string tupleValue);
    std::tuple<TokenObject, TokenObject> parseAttributeIntoIndividualTokens(std::string attribute);
    TokenType setTokenTypeOfAttribute(std::string attrName);

public:
    Parser(std::vector<TokenObject> &tokenizedQuery);
    std::vector<TokenObject> getTokenizedQuery();
    QueryObject parse();
};

#endif //INC_22S1_CP_SPA_TEAM_17_PARSER_H
