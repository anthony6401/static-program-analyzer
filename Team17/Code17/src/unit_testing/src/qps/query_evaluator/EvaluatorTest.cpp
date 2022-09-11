#include <catch.hpp>
#include <list>
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/Evaluator.h"


//TEST_CASE("Evaluation for Select Clause - variable v; Select v") {
//    PKB* pkb = new PKB();
//    auto qpsClient = QPSClient(pkb);
//    std::list<std::string> testResults;
//    std::vector<SuchThat> relationships {};
//    std::vector<Pattern> patterns {};
//    Select select = Select( "v");
//    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap = {{"v", DesignEntity::VARIABLE}};
//    QueryObject testQuery = QueryObject(select, relationships, patterns, synonymToDesignEntityMap);
//    Evaluator::evaluateQuery(testQuery, testResults, qpsClient);
//    std::list<std::string> expectedResults = {"none"};
//    REQUIRE(testResults == expectedResults);
//}
//
//TEST_CASE("Evaluator for ModifiesS Relationship Clause - variable v; Select v such that Modifies (6, v)") {
//    PKB* pkb = new PKB();
//    auto qpsClient = QPSClient(pkb);
//    std::list<std::string> testResults;
//    std::vector<SuchThat> relationships {SuchThat(TokenType::MODIFIES,
//                                                  TokenObject(TokenType::INTEGER, "6"),
//                                                  TokenObject(TokenType::NAME, "v"))};
//    std::vector<Pattern> patterns {};
//    Select select = Select( "v");
//    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap = {{"v", DesignEntity::VARIABLE}};
//    QueryObject testQuery = QueryObject(select, relationships, patterns, synonymToDesignEntityMap);
//    Evaluator::evaluateQuery(testQuery, testResults, qpsClient);
//    std::list<std::string> expectedResults = {"z", "x", "y"};
//    REQUIRE(testResults == expectedResults);
//}
