#include <catch.hpp>
#include <list>
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/Evaluator.h"

TEST_CASE("Evaluation for Select Clause - variable v; Select v") {
    std::list<std::string> testResults;
    std::vector<SuchThat> relationships {};
    std::vector<Pattern> patterns {};
    Select select = Select( "v");
    PKB* pkb = new PKB();
    auto qpsClient = QPSClient(pkb);
    std::unordered_map<std::string, TokenType> synonymToDesignEntityMap = {{"v", TokenType::VARIABLE}};
    QueryObject testQuery = QueryObject(select, relationships, patterns, synonymToDesignEntityMap);
    Evaluator::evaluateQuery(testQuery, testResults, qpsClient);
    std::list<std::string> expectedResults = {"none"};
    REQUIRE(testResults == expectedResults);
}
