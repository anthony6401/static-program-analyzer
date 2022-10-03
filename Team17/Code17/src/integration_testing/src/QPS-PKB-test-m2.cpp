#include <catch.hpp>
#include "components/qps/QPS.h"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/Evaluator.h"

// Populating data in PKB
PKB* pkb_m2 = new PKB();
auto qpsClient_m2 = QPSClient(pkb_m2);

// PQL queries
TEST_CASE("Calls queries") {
    SECTION("Calls") {
        std::string testQuery = "if ifs; Select ifs";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"8"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("Calls* queries") {

}

TEST_CASE("Next queries") {

}

TEST_CASE("Next* queries") {

}