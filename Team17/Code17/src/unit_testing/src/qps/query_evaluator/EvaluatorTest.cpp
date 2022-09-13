#include <catch.hpp>
#include <list>
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/Evaluator.h"

// Test cases should cover Single Clause and MultiClause queries:
// 1) No synonym clauses
// 2) Synonym clauses - no common synonym
// 3) Synonym clauses - common synonym
// 4) Synonym clauses - has Select synonym
// 5) Synonym clauses - does not have Select Synonym

TEST_CASE("Evaluation for No synonym Clause - variable v; Select v such that Modifies(1, _)") {
    PKB* pkb = new PKB();
    auto qpsClient = QPSClient(pkb);
    std::list<std::string> testResults;
    std::vector<SuchThat> relationships {SuchThat(TokenType::MODIFIES, TokenObject(TokenType::INTEGER, "1"),
                                                  TokenObject(TokenType::WILDCARD, "_"))};
    std::vector<Pattern> patterns {};
    Select select = Select( "v");
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap = {{"v", DesignEntity::VARIABLE}};
    QueryObject testQuery = QueryObject(select, relationships, patterns, synonymToDesignEntityMap);
    Evaluator::evaluateQuery(testQuery, testResults, qpsClient);
    std::list<std::string> expectedResults = {"none"};
    REQUIRE(testResults == expectedResults);
}

TEST_CASE("Evaluation for No synonym Clause - variable v; Select v such that Follows(1, 2)") {
    PKB* pkb = new PKB();
    auto qpsClient = QPSClient(pkb);
    std::list<std::string> testResults;
    std::vector<SuchThat> relationships {SuchThat(TokenType::FOLLOWS, TokenObject(TokenType::INTEGER, "1"),
                                                  TokenObject(TokenType::INTEGER, "2"))};
    std::vector<Pattern> patterns {};
    Select select = Select( "v");
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap = {{"v", DesignEntity::VARIABLE}};
    QueryObject testQuery = QueryObject(select, relationships, patterns, synonymToDesignEntityMap);
    Evaluator::evaluateQuery(testQuery, testResults, qpsClient);
    std::list<std::string> expectedResults = {"none"};
    REQUIRE(testResults == expectedResults);
}

TEST_CASE("Evaluator for ModifiesS Relationship Clause - variable v; Select v such that Modifies (6, v)") {
    PKB* pkb = new PKB();
    auto qpsClient = QPSClient(pkb);
    std::list<std::string> testResults;
    std::vector<SuchThat> relationships {SuchThat(TokenType::MODIFIES,
                                                  TokenObject(TokenType::INTEGER, "6"),
                                                  TokenObject(TokenType::NAME, "v"))};
    std::vector<Pattern> patterns {};
    Select select = Select( "v");
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap = {{"v", DesignEntity::VARIABLE}};
    QueryObject testQuery = QueryObject(select, relationships, patterns, synonymToDesignEntityMap);
    Evaluator::evaluateQuery(testQuery, testResults, qpsClient);
    std::list<std::string> expectedResults = {"z", "x", "y"};
    REQUIRE(testResults == expectedResults);
}
