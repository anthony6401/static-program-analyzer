#include <catch.hpp>
#include <list>
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/Evaluator.h"

TEST_CASE("Syntactically Invalid queries") {
    PKB* pkb = new PKB();
    auto qpsClient = QPSClient(pkb);
    std::list<std::string> testResults;
    QueryObject testQuery = QueryObject();
    Evaluator::evaluateQuery(testQuery, testResults, qpsClient);

    std::list<std::string> expectedResults = {"SyntaxError"};
    REQUIRE(testResults == expectedResults);
}

TEST_CASE("Semantically Invalid queries") {
    PKB* pkb = new PKB();
    auto qpsClient = QPSClient(pkb);
    std::list<std::string> testResults;
    std::vector<SuchThat> relationships = {SuchThat(TokenType::MODIFIES, TokenObject(TokenType::INTEGER, "1"),
                                                  TokenObject(TokenType::WILDCARD, "_"))};
    std::vector<Pattern> patterns {Pattern(TokenType::ASSIGN, "a", TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
                                           TokenObject(TokenType::NAME_WITH_QUOTATION, "y"))};
    Select select = Select(TokenType::SYNONYM, { TokenObject(TokenType::NAME, "v") });
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap = {{"a", DesignEntity::ASSIGN}};

    QueryObject testQuery = QueryObject(select, relationships, patterns, synonymToDesignEntityMap, 2);
    testQuery.setSemanticallyInvalid();
    Evaluator::evaluateQuery(testQuery, testResults, qpsClient);

    std::list<std::string> expectedResults = {"SemanticError"};
    REQUIRE(testResults == expectedResults);
}