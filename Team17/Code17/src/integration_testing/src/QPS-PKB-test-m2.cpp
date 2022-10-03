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
        std::string testQuery = "procedure p; \n "
                                "Select p such that Calls(p, _)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"First", "Second"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls Test 3") {
        std::string testQuery = "procedure p; \n "
                                "Select p such that Calls(p, \"Third\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"Second"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls Test 4") {
        std::string testQuery = "procedure p, p1; \n "
                                "Select p such that Calls(\"Third\", _)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults.empty() == true);
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("Calls* queries") {
    SECTION("Calls* Test 1") {
        std::string testQuery = "procedure p; \n "
                                "Select p such that Calls*(_, _)";
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
                                "Select p1 such that Calls*(p, p1)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"Second", "Third"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("Next queries") {
    SECTION("Next Test 1") {
        std::string testQuery = "procedure p; \n "
                                "Select p such that Next(2, 3)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"First", "Second", "Third"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Next Test 2") {
        std::string testQuery = "procedure p; \n "
                                "Select p such that Next(8, 9)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults.empty() == true);
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("Next* queries") {
    SECTION("Next* Test 1") {
        std::string testQuery = "procedure p; \n "
                                "Select p such that Next*(1, 2)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"First", "Second", "Third"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Next* Test 2") {
        std::string testQuery = "procedure p; \n "
                                "Select p such that Next*(5, 2)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults.empty() == true);
        REQUIRE(testResults == expectedResults);
    }
}