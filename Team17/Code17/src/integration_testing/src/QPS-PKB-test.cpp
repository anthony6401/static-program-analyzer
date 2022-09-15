#include <catch.hpp>
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/Evaluator.h"

// Integration test for QPS and PKB
// Sample source code:

// Populating data in PKB
//PKB::PKB() {}
//auto qpsClient = QPSClient(pkb);



// PQL queries
TEST_CASE("Select all queries") {
    SECTION("Select if statements") {

    }

    SECTION("Select assign statements") {

    }

    SECTION("Select read statements") {

    }

    SECTION("Select print statements") {

    }

    SECTION("Select procedures") {

    }

    SECTION("Select stmt statements") {

    }

    SECTION("Select call statements") {

    }

    SECTION("Select while statements") {

    }

    SECTION("Select variables") {

    }

    SECTION("Select constants") {

    }
}

TEST_CASE("Relationships and patterns") {
    SECTION("No synonym Clause - variable v; Select v such that Modifies(1, _)") {

    }

    SECTION("No synonym Clause - variable v; Select v such that Uses(1, _)") {

    }

    SECTION("Single synonym, has select - variable v; Select v such that Uses(1, v)") {

    }

    SECTION("Single synonym Clause - assign a; Select a such that Modifies(a, _) pattern a(\"x\",\"y\")") {

    }

    SECTION("Single synonym Clause - stmt s; Select s such that Follows(1, s) pattern a(_,_)") {

    }

    SECTION("Single synonym Clause - assign a; Select v such that Modifies(1, v) pattern a(v,_\"x\"_)") {

    }

    SECTION("Multiple common synonym - assign a; variable v; Select v such that Modifies(a, v) pattern a(v, _)\"") {

    }

    SECTION("Single synonym Clause - stmt s; Select s such that Follows*(1, s)") {

    }

    SECTION("Single synonym Clause - stmt s, s1; Select s such that Parent*(s, s1)") {

    }

}


