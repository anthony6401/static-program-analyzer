#include "string"
#include "unordered_map"
#include "syntax_checker/SyntaxChecker.h"
#include "syntax_checker/DeclarationClauseSyntaxChecker.h"
#include "syntax_checker/SelectClauseSyntaxChecker.h"
#include "syntax_checker/SuchThatClauseSyntaxChecker.h"
#include "syntax_checker/PatternClauseSyntaxChecker.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/abstract_query_object/Declaration.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/qps/abstract_query_object/SuchThat.h"
#include "components/qps/abstract_query_object/Pattern.h"
#include "models/Entity/DesignEntity.h"
#include <vector>

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
    std::vector<std::vector<TokenObject>> groupQueryIntoClause();
    bool isSyntacticallyCorrect(std::vector<TokenObject> tokenizedClause, SyntaxChecker* checker);
    Select parseTokensIntoSelectObject(std::vector<TokenObject> selectTokens, std::unordered_map<std::string, DesignEntity> mappedSynonyms);
    std::vector<SuchThat> parseTokensIntoSuchThatObjects(std::vector<TokenObject> relationshipTokens, std::unordered_map<std::string, DesignEntity> mappedSynonyms);
    std::vector<Pattern> parseTokensIntoPatternObjects(std::vector<TokenObject> patternTokens, std::unordered_map<std::string, DesignEntity> mappedSynonyms);
    std::unordered_map<std::string, DesignEntity> mapSynonymToDesignEntity(std::vector<TokenObject> declarations);
    bool isRelationshipToken(TokenType token);
    bool isDesignEntityToken(TokenType token);

public:
    Parser(std::vector<TokenObject> tokenizedQuery);
    QueryObject parse();
    std::vector<TokenObject> getTokenizedQuery();

};

#endif //INC_22S1_CP_SPA_TEAM_17_PARSER_H
