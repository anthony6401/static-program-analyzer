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
// 6) Empty / False clauses

TEST_CASE("Evaluation for No relationship and pattern clauses") {
    PKB* pkb = new PKB();
    auto qpsClient = QPSClient(pkb);
    std::list<std::string> testResults;
    std::vector<SuchThat> relationships {};
    std::vector<Pattern> patterns {};
    Select select = Select( "v");
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap = {{"v", DesignEntity::VARIABLE}};
    QueryObject testQuery = QueryObject(select, relationships, patterns, synonymToDesignEntityMap);
    Evaluator::evaluateQuery(testQuery, testResults, qpsClient);
    std::list<std::string> expectedResults = {"x", "y", "z"};
    REQUIRE(testResults == expectedResults);
}

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
    std::list<std::string> expectedResults = {"x", "y", "z"};
    REQUIRE(testResults == expectedResults);
}

TEST_CASE("Evaluation for single synonym Clause - variable v; Select v such that Modifies(1, v)") {
    PKB* pkb = new PKB();
    auto qpsClient = QPSClient(pkb);
    std::list<std::string> testResults;
    std::vector<SuchThat> relationships {SuchThat(TokenType::MODIFIES, TokenObject(TokenType::INTEGER, "1"),
                                                  TokenObject(TokenType::NAME, "v"))};
    std::vector<Pattern> patterns {};
    Select select = Select( "v");
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap = {{"v", DesignEntity::VARIABLE}};
    QueryObject testQuery = QueryObject(select, relationships, patterns, synonymToDesignEntityMap);
    Evaluator::evaluateQuery(testQuery, testResults, qpsClient);
    std::list<std::string> expectedResults = {"x"};
    REQUIRE(testResults == expectedResults);
}


TEST_CASE("Evaluation for single synonym Clause - assign a; Select a such that Modifies(a, _) pattern a(\"x\",\"y\")") {
    PKB* pkb = new PKB();
    auto qpsClient = QPSClient(pkb);
    std::list<std::string> testResults;
    std::vector<SuchThat> relationships {SuchThat(TokenType::MODIFIES, TokenObject(TokenType::NAME, "a"),
                                                  TokenObject(TokenType::WILDCARD, "_"))};
    std::vector<Pattern> patterns {Pattern("a", TokenObject(TokenType::NAME_WITH_QUOTATION, "x"),
                                           TokenObject(TokenType::NAME_WITH_QUOTATION, "y"))};
    Select select = Select( "a");
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap = {{"a", DesignEntity::ASSIGN}};
    QueryObject testQuery = QueryObject(select, relationships, patterns, synonymToDesignEntityMap);
    Evaluator::evaluateQuery(testQuery, testResults, qpsClient);
    std::list<std::string> expectedResults = {"1", "3"};
    REQUIRE(testResults == expectedResults);
}

// Returns empty clause -> result should be none
TEST_CASE("Evaluation for unrelated to select - assign a; Select a such that Uses (6, v)") {
    PKB* pkb = new PKB();
    auto qpsClient = QPSClient(pkb);
    std::list<std::string> testResults;
    std::vector<SuchThat> relationships {SuchThat(TokenType::USES,
                                                  TokenObject(TokenType::INTEGER, "6"),
                                                  TokenObject(TokenType::NAME, "v"))};
    std::vector<Pattern> patterns {};
    Select select = Select( "a");
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap = {{"a", DesignEntity::ASSIGN}};
    QueryObject testQuery = QueryObject(select, relationships, patterns, synonymToDesignEntityMap);
    Evaluator::evaluateQuery(testQuery, testResults, qpsClient);
    std::list<std::string> expectedResults = {"none"};
    REQUIRE(testResults == expectedResults);
}
