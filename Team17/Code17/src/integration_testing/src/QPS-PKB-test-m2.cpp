#include <catch.hpp>
#include "components/qps/QPS.h"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/Evaluator.h"

// Populating data in PKB
PKB* pkb_m2 = new PKB();
auto qpsClient_m2 = QPSClient(pkb_m2);

// PQL queries
TEST_CASE("Calls queries") {
    SECTION("Calls Test 1") {
        std::string testQuery = "procedure p, p1; \n "
                                "Select p such that Calls(\"First\", \"Second\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"First", "Second", "Third"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls Test 2") {
        std::string testQuery = "procedure p, p1; \n "
                                "Select p1 such that Calls(\"Second\", \"Third\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"First", "Second", "Third"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls Test 3") {
        std::string testQuery = "procedure p, p1; \n "
                                "Select p such that Calls(\"First\", \"Third\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults.empty() == true);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls Test 4") {
        std::string testQuery = "procedure p, p1; \n "
                                "Select p such that Calls(\"Second\", \"First\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults.empty() == true);
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("Calls* queries") {
    SECTION("Calls* Test 1") {
        std::string testQuery = "procedure p, p1; \n "
                                "Select p such that Calls*(\"First\", \"Second\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"First", "Second", "Third"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls* Test 2") {
        std::string testQuery = "procedure p, p1; \n "
                                "Select p1 such that Calls*(\"First\", \"Third\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"First", "Second", "Third"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls* Test 3") {
        std::string testQuery = "procedure p, p1; \n "
                                "Select p such that Calls*(\"Second\", \"First\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults.empty() == true);
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("Next queries") {

}

TEST_CASE("Next* queries") {

}