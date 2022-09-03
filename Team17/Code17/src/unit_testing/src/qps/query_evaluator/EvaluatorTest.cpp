#include <catch.hpp>
#include <list>
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/Evaluator.h"

TEST_CASE("Evaluation for Select Clause - variable v; Select v") {
    std::list<std::string> testResults;
    std::vector<SuchThat> relationships {};
    std::vector<Pattern> patterns {};
    Select select = Select(TokenType::VARIABLE, "v");
    std::unordered_map<std::string, TokenType> synonymToDesignEntityMap = {{"v", TokenType::VARIABLE}};
    QueryObject testQuery = QueryObject();
    Evaluator::evaluateQuery(testQuery, testResults);
    std::list<std::string> expectedResults = {"x", "y", "z"};
    REQUIRE(testResults == expectedResults);
}
