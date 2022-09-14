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

TEST_CASE("Evaluation for No synonym Clause - variable v; Select v such that Modifies(1, _)") { // false
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

TEST_CASE("Evaluation for No synonym Clause - variable v; Select v such that Uses(1, _)") { // true
    PKB* pkb = new PKB();
    auto qpsClient = QPSClient(pkb);
    std::list<std::string> testResults;
    std::vector<SuchThat> relationships {SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "1"),
                                                  TokenObject(TokenType::WILDCARD, "_"))};
    std::vector<Pattern> patterns {};
    Select select = Select( "v");
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap = {{"v", DesignEntity::VARIABLE}};
    QueryObject testQuery = QueryObject(select, relationships, patterns, synonymToDesignEntityMap);
    Evaluator::evaluateQuery(testQuery, testResults, qpsClient);

    std::list<std::string> expectedResults = {"x", "y", "z"};
    REQUIRE(testResults == expectedResults);
}

TEST_CASE("Single synonym, has select - variable v; Select v such that Uses(1, v)") { // common synonym
    PKB* pkb = new PKB();
    auto qpsClient = QPSClient(pkb);
    std::list<std::string> testResults;
    std::vector<SuchThat> relationships {SuchThat(TokenType::USES, TokenObject(TokenType::INTEGER, "1"),
                                                  TokenObject(TokenType::NAME, "v"))};
    std::vector<Pattern> patterns {};
    Select select = Select( "v");
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap = {{"v", DesignEntity::VARIABLE}};
    QueryObject testQuery = QueryObject(select, relationships, patterns, synonymToDesignEntityMap);
    Evaluator::evaluateQuery(testQuery, testResults, qpsClient);

    std::list<std::string> expectedResults = {"x"};
    REQUIRE(testResults == expectedResults);
}

TEST_CASE("Evaluation for single synonym Clause - assign a; Select a such that Modifies(a, _) pattern a(\"x\",\"y\")") { // common synonym
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
    // TO CHECK, COMMENT OUT RETURN VARIABLE FROM SELECT CLAUSE AND UNCOMMENT ASSIGN
    // REQUIRE(testResults == expectedResults);
}

TEST_CASE("Evaluation for unrelated to select - assign a; Select a such that Uses (6, v)") { // unrelated to select
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

    std::list<std::string> expectedResults = {"1", "2", "3", "4"};
    // TO CHECK, COMMENT OUT RETURN VARIABLE FROM SELECT CLAUSE AND UNCOMMENT ASSIGN
    //REQUIRE(testResults == expectedResults);
}

TEST_CASE("Evaluation for unrelated to select - assign a, a1; Select a such that Uses (6, v) pattern a1(_, _)") { // unrelated to select
    PKB* pkb = new PKB();
    auto qpsClient = QPSClient(pkb);
    std::list<std::string> testResults;
    std::vector<SuchThat> relationships {SuchThat(TokenType::USES,
                                                  TokenObject(TokenType::INTEGER, "6"),
                                                  TokenObject(TokenType::NAME, "v"))};
    std::vector<Pattern> patterns {Pattern("a1", TokenObject(TokenType::WILDCARD, "_"),
                                           TokenObject(TokenType::WILDCARD, "_"))};
    Select select = Select( "a");
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap = {{"a", DesignEntity::ASSIGN},
                                                                              {"a1", DesignEntity::ASSIGN}};
    QueryObject testQuery = QueryObject(select, relationships, patterns, synonymToDesignEntityMap);
    Evaluator::evaluateQuery(testQuery, testResults, qpsClient);

    std::list<std::string> expectedResults = {"1", "2", "3", "4"};
    // TO CHECK, COMMENT OUT RETURN VARIABLE FROM SELECT CLAUSE AND UNCOMMENT ASSIGN
    //REQUIRE(testResults == expectedResults);
}

TEST_CASE("Evaluation for synonym and boolean clauses - assign a; Select v such that Uses (1, \"x\") pattern a(v, \"x\")") {
    PKB* pkb = new PKB();
    auto qpsClient = QPSClient(pkb);
    std::list<std::string> testResults;
    std::vector<SuchThat> relationships {SuchThat(TokenType::USES,
                                                  TokenObject(TokenType::INTEGER, "1"),
                                                  TokenObject(TokenType::NAME_WITH_QUOTATION, "x"))};
    std::vector<Pattern> patterns {Pattern("a", TokenObject(TokenType::NAME, "v"),
                                           TokenObject(TokenType::NAME_WITH_QUOTATION, "x"))};
    Select select = Select( "v");
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap = {{"a", DesignEntity::ASSIGN},
                                                                              {"v", DesignEntity::VARIABLE}};
    QueryObject testQuery = QueryObject(select, relationships, patterns, synonymToDesignEntityMap);
    Evaluator::evaluateQuery(testQuery, testResults, qpsClient);
    std::list<std::string> expectedResults = {"x"};
    REQUIRE(testResults == expectedResults);
}



TEST_CASE("Evaluation for multiple common synonym - assign a; variable v; Select a such that Modifies(a, v) pattern a(v, _)") { // common synonym
    PKB* pkb = new PKB();
    auto qpsClient = QPSClient(pkb);
    std::list<std::string> testResults;
    std::vector<SuchThat> relationships {SuchThat(TokenType::MODIFIES, TokenObject(TokenType::NAME, "a"),
                                                  TokenObject(TokenType::NAME, "v"))};
    std::vector<Pattern> patterns {Pattern("a", TokenObject(TokenType::NAME, "v"),
                                           TokenObject(TokenType::WILDCARD, "_"))};
    Select select = Select( "a");
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap = {{"a", DesignEntity::ASSIGN},
                                                                              {"v", DesignEntity::VARIABLE}};
    QueryObject testQuery = QueryObject(select, relationships, patterns, synonymToDesignEntityMap);
    Evaluator::evaluateQuery(testQuery, testResults, qpsClient);
    std::list<std::string> expectedResults = {"2", "1"};
    REQUIRE(testResults == expectedResults);
}

TEST_CASE("Evaluation for multiple common synonym - assign a; variable v; Select v such that Modifies(a, v) pattern a(v, _)") { // common synonym
    PKB *pkb = new PKB();
    auto qpsClient = QPSClient(pkb);
    std::list<std::string> testResults;
    std::vector<SuchThat> relationships{SuchThat(TokenType::MODIFIES, TokenObject(TokenType::NAME, "a"),
                                                 TokenObject(TokenType::NAME, "v"))};
    std::vector<Pattern> patterns{Pattern("a", TokenObject(TokenType::NAME, "v"),
                                          TokenObject(TokenType::WILDCARD, "_"))};
    Select select = Select("v");
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap = {{"a", DesignEntity::ASSIGN},
                                                                              {"v", DesignEntity::VARIABLE}};
    QueryObject testQuery = QueryObject(select, relationships, patterns, synonymToDesignEntityMap);
    Evaluator::evaluateQuery(testQuery, testResults, qpsClient);
    std::list<std::string> expectedResults = {"y", "x"};
    REQUIRE(testResults == expectedResults);
}


TEST_CASE("Evaluation for 2 empty clauses - assign a; variable v; Select a such that Follows*(1, v) pattern a(_, \"x\")") {
    PKB* pkb = new PKB();
    auto qpsClient = QPSClient(pkb);
    std::list<std::string> testResults;
    std::vector<SuchThat> relationships {SuchThat(TokenType::FOLLOWS_T, TokenObject(TokenType::INTEGER, "1"),
                                                  TokenObject(TokenType::NAME, "v"))};
    std::vector<Pattern> patterns {Pattern("a", TokenObject(TokenType::WILDCARD, "_"),
                                           TokenObject(TokenType::NAME_WITH_QUOTATION, "x"))};
    Select select = Select( "a");
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap = {{"a", DesignEntity::ASSIGN},
                                                                              {"v", DesignEntity::VARIABLE}};
    QueryObject testQuery = QueryObject(select, relationships, patterns, synonymToDesignEntityMap);
    Evaluator::evaluateQuery(testQuery, testResults, qpsClient);
    std::list<std::string> expectedResults = {"none"};
    REQUIRE(testResults == expectedResults);
}
