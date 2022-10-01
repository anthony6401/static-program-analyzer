#include <catch.hpp>
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/Evaluator.h"
#include "models/Entity/Entity.h"
#include "models/Entity/AssignEntity.h"
#include "models/Entity/IfEntity.h"
#include "models/Entity/WhileEntity.h"
#include "models/Entity/ProcedureEntity.h"
#include "models/Entity/ConstantEntity.h"
#include "models/Entity/VariableEntity.h"
#include "models/Relationship/Relationship.h"
#include "models/Relationship/UsesRelationship.h"
#include "models/Relationship/ModifyRelationship.h"
#include "models/Relationship/FollowsRelationship.h"
#include "models/Relationship/FollowsTRelationship.h"
#include "models/Relationship/ParentRelationship.h"
#include "models/Relationship/ParentTRelationship.h"
#include "models/Pattern/Pattern.h"
#include "models/Pattern/AssignPattern.h"
#include "components/qps/QPS.h"
#include <iostream>

// Integration test for QPS and PKB

// Populating data in PKB
PKB* pkb = new PKB();
auto qpsClient = QPSClient(pkb);

// Stmt Entity
Entity* stmt1 = new AssignEntity("1");
Entity* stmt2 = new AssignEntity("2");
Entity* stmt3 = new AssignEntity("3");
Entity* stmt4 = new WhileEntity("4");
Entity* stmt5 = new AssignEntity("5");
Entity* stmt6 = new AssignEntity("6");
Entity* stmt7 = new AssignEntity("7");
Entity* stmt8 = new IfEntity("8");
Entity* stmt9 = new AssignEntity("9");
Entity* stmt10 = new AssignEntity("10");
Entity* stmt11 = new AssignEntity("11");
Entity* stmt12 = new AssignEntity("12");

// Proc Entity
Entity* proc1 = new ProcedureEntity("computeCentroid");

// Variable Entity
Entity* variableCount = new VariableEntity("count");
Entity* variableCenX = new VariableEntity("cenX");
Entity* variableCenY = new VariableEntity("cenY");
Entity* variableFlag = new VariableEntity("flag");
Entity* variableNormSq = new VariableEntity("normSq");
Entity* variableX = new VariableEntity("x");
Entity* variableY = new VariableEntity("y");

// Constant Entity
Entity* constant1 = new ConstantEntity("0");
Entity* constant2 = new ConstantEntity("1");

// Follows Relationship
Relationship* followsRelationship1 = new FollowsRelationship(stmt1, stmt2);
Relationship* followsRelationship2 = new FollowsRelationship(stmt2, stmt3);
Relationship* followsRelationship3 = new FollowsRelationship(stmt3, stmt4);
Relationship* followsRelationship4 = new FollowsRelationship(stmt4, stmt8);
Relationship* followsRelationship5 = new FollowsRelationship(stmt8, stmt12);
Relationship* followsRelationship6 = new FollowsRelationship(stmt5, stmt6);
Relationship* followsRelationship7 = new FollowsRelationship(stmt6, stmt7);
Relationship* followsRelationship8 = new FollowsRelationship(stmt10, stmt11);

// FollowsT Relationship
Relationship* followsTRelationship1 = new FollowsTRelationship(stmt1, stmt2);
Relationship* followsTRelationship2 = new FollowsTRelationship(stmt1, stmt3);
Relationship* followsTRelationship3 = new FollowsTRelationship(stmt1, stmt4);
Relationship* followsTRelationship4 = new FollowsTRelationship(stmt1, stmt8);
Relationship* followsTRelationship5 = new FollowsTRelationship(stmt1, stmt12);
Relationship* followsTRelationship6 = new FollowsTRelationship(stmt2, stmt3);
Relationship* followsTRelationship7 = new FollowsTRelationship(stmt2, stmt4);
Relationship* followsTRelationship8 = new FollowsTRelationship(stmt2, stmt8);
Relationship* followsTRelationship9 = new FollowsTRelationship(stmt2, stmt12);
Relationship* followsTRelationship10 = new FollowsTRelationship(stmt3, stmt4);
Relationship* followsTRelationship11 = new FollowsTRelationship(stmt3, stmt8);
Relationship* followsTRelationship12 = new FollowsTRelationship(stmt3, stmt12);
Relationship* followsTRelationship13 = new FollowsTRelationship(stmt4, stmt8);
Relationship* followsTRelationship14 = new FollowsTRelationship(stmt4, stmt12);
Relationship* followsTRelationship15 = new FollowsTRelationship(stmt8, stmt12);
Relationship* followsTRelationship16 = new FollowsTRelationship(stmt5, stmt6);
Relationship* followsTRelationship17 = new FollowsTRelationship(stmt5, stmt7);
Relationship* followsTRelationship18 = new FollowsTRelationship(stmt6, stmt7);
Relationship* followsTRelationship19 = new FollowsTRelationship(stmt10, stmt11);

// Parent Relationship
Relationship* parentRelationship1 = new ParentRelationship(stmt4, stmt5);
Relationship* parentRelationship2 = new ParentRelationship(stmt4, stmt6);
Relationship* parentRelationship3 = new ParentRelationship(stmt4, stmt7);
Relationship* parentRelationship4 = new ParentRelationship(stmt8, stmt9);
Relationship* parentRelationship5 = new ParentRelationship(stmt8, stmt10);
Relationship* parentRelationship6 = new ParentRelationship(stmt8, stmt11);

// ParentT Relationship
Relationship* parentTRelationship1 = new ParentTRelationship(stmt4, stmt5);
Relationship* parentTRelationship2 = new ParentTRelationship(stmt4, stmt6);
Relationship* parentTRelationship3 = new ParentTRelationship(stmt4, stmt7);
Relationship* parentTRelationship4 = new ParentTRelationship(stmt8, stmt9);
Relationship* parentTRelationship5 = new ParentTRelationship(stmt8, stmt10);
Relationship* parentTRelationship6 = new ParentTRelationship(stmt8, stmt11);

// Uses Relationship
Relationship* usesRelationship1 = new UsesRelationship(proc1, variableX);
Relationship* usesRelationship2 = new UsesRelationship(proc1, variableY);
Relationship* usesRelationship3 = new UsesRelationship(proc1, variableCount);
Relationship* usesRelationship4 = new UsesRelationship(proc1, variableCenX);
Relationship* usesRelationship5 = new UsesRelationship(proc1, variableCenY);
Relationship* usesRelationship6 = new UsesRelationship(stmt4, variableX);
Relationship* usesRelationship7 = new UsesRelationship(stmt4, variableY);
Relationship* usesRelationship8 = new UsesRelationship(stmt5, variableCount);
Relationship* usesRelationship9 = new UsesRelationship(stmt6, variableCenX);
Relationship* usesRelationship10 = new UsesRelationship(stmt6, variableX);
Relationship* usesRelationship11 = new UsesRelationship(stmt7, variableCenY);
Relationship* usesRelationship12 = new UsesRelationship(stmt7, variableY);
Relationship* usesRelationship13 = new UsesRelationship(stmt8, variableCount);
Relationship* usesRelationship14 = new UsesRelationship(stmt10, variableCenX);
Relationship* usesRelationship15 = new UsesRelationship(stmt10, variableCount);
Relationship* usesRelationship16 = new UsesRelationship(stmt11, variableCenY);
Relationship* usesRelationship17 = new UsesRelationship(stmt11, variableCount);
Relationship* usesRelationship18 = new UsesRelationship(stmt12, variableCenX);
Relationship* usesRelationship19 = new UsesRelationship(stmt12, variableCenY);

// Modify Relationship
Relationship* modifyRelationship1 = new ModifyRelationship(proc1, variableCount);
Relationship* modifyRelationship2 = new ModifyRelationship(proc1, variableCenX);
Relationship* modifyRelationship3 = new ModifyRelationship(proc1, variableCenY);
Relationship* modifyRelationship4 = new ModifyRelationship(proc1, variableFlag);
Relationship* modifyRelationship5 = new ModifyRelationship(proc1, variableNormSq);
Relationship* modifyRelationship6 = new ModifyRelationship(stmt1, variableCount);
Relationship* modifyRelationship7 = new ModifyRelationship(stmt2, variableCenX);
Relationship* modifyRelationship8 = new ModifyRelationship(stmt3, variableCenY);
Relationship* modifyRelationship9 = new ModifyRelationship(stmt5, variableCount);
Relationship* modifyRelationship10 = new ModifyRelationship(stmt6, variableCenX);
Relationship* modifyRelationship11 = new ModifyRelationship(stmt7, variableCenY);
Relationship* modifyRelationship12 = new ModifyRelationship(stmt9, variableFlag);
Relationship* modifyRelationship13 = new ModifyRelationship(stmt10, variableCenX);
Relationship* modifyRelationship14 = new ModifyRelationship(stmt11, variableCenY);
Relationship* modifyRelationship15 = new ModifyRelationship(stmt12, variableNormSq);

// Assign Pattern

kb::Pattern* assignPattern1 = new AssignPattern("1", "count", "0");
kb::Pattern* assignPattern2 = new AssignPattern("2", "cenX", "0");
kb::Pattern* assignPattern3 = new AssignPattern("3", "cenY", "0");
kb::Pattern* assignPattern4 = new AssignPattern("5", "count", "count+1");
kb::Pattern* assignPattern5 = new AssignPattern("6", "cenX", "cenX+x");
kb::Pattern* assignPattern6 = new AssignPattern("7", "cenY", "cenY+y");
kb::Pattern* assignPattern7 = new AssignPattern("9", "flag", "1");
kb::Pattern* assignPattern8 = new AssignPattern("10", "cenX", "cenX/count");
kb::Pattern* assignPattern9 = new AssignPattern("11", "cenY", "cenY/count");
kb::Pattern* assignPattern10 = new AssignPattern("12", "normSq", "cenX*cenX+cenY*cenY");

int initPKB() {
    pkb->storeConstant(constant1);
    pkb->storeConstant(constant2);

    pkb->storeRelationship(followsRelationship1);
    pkb->storeRelationship(followsRelationship2);
    pkb->storeRelationship(followsRelationship3);
    pkb->storeRelationship(followsRelationship4);
    pkb->storeRelationship(followsRelationship5);
    pkb->storeRelationship(followsRelationship6);
    pkb->storeRelationship(followsRelationship7);
    pkb->storeRelationship(followsRelationship8);

    pkb->storeRelationship(followsTRelationship1);
    pkb->storeRelationship(followsTRelationship2);
    pkb->storeRelationship(followsTRelationship3);
    pkb->storeRelationship(followsTRelationship4);
    pkb->storeRelationship(followsTRelationship5);
    pkb->storeRelationship(followsTRelationship6);
    pkb->storeRelationship(followsTRelationship7);
    pkb->storeRelationship(followsTRelationship8);
    pkb->storeRelationship(followsTRelationship9);
    pkb->storeRelationship(followsTRelationship10);
    pkb->storeRelationship(followsTRelationship11);
    pkb->storeRelationship(followsTRelationship12);
    pkb->storeRelationship(followsTRelationship13);
    pkb->storeRelationship(followsTRelationship14);
    pkb->storeRelationship(followsTRelationship15);
    pkb->storeRelationship(followsTRelationship16);
    pkb->storeRelationship(followsTRelationship17);
    pkb->storeRelationship(followsTRelationship18);
    pkb->storeRelationship(followsTRelationship19);

    pkb->storeRelationship(parentRelationship1);
    pkb->storeRelationship(parentRelationship2);
    pkb->storeRelationship(parentRelationship3);
    pkb->storeRelationship(parentRelationship4);
    pkb->storeRelationship(parentRelationship5);
    pkb->storeRelationship(parentRelationship6);

    pkb->storeRelationship(parentTRelationship1);
    pkb->storeRelationship(parentTRelationship2);
    pkb->storeRelationship(parentTRelationship3);
    pkb->storeRelationship(parentTRelationship4);
    pkb->storeRelationship(parentTRelationship5);
    pkb->storeRelationship(parentTRelationship6);

    pkb->storeRelationship(usesRelationship1);
    pkb->storeRelationship(usesRelationship2);
    pkb->storeRelationship(usesRelationship3);
    pkb->storeRelationship(usesRelationship4);
    pkb->storeRelationship(usesRelationship5);
    pkb->storeRelationship(usesRelationship6);
    pkb->storeRelationship(usesRelationship7);
    pkb->storeRelationship(usesRelationship8);
    pkb->storeRelationship(usesRelationship9);
    pkb->storeRelationship(usesRelationship10);
    pkb->storeRelationship(usesRelationship11);
    pkb->storeRelationship(usesRelationship12);
    pkb->storeRelationship(usesRelationship13);
    pkb->storeRelationship(usesRelationship14);
    pkb->storeRelationship(usesRelationship15);
    pkb->storeRelationship(usesRelationship16);
    pkb->storeRelationship(usesRelationship17);
    pkb->storeRelationship(usesRelationship18);
    pkb->storeRelationship(usesRelationship19);

    pkb->storeRelationship(modifyRelationship1);
    pkb->storeRelationship(modifyRelationship2);
    pkb->storeRelationship(modifyRelationship3);
    pkb->storeRelationship(modifyRelationship4);
    pkb->storeRelationship(modifyRelationship5);
    pkb->storeRelationship(modifyRelationship6);
    pkb->storeRelationship(modifyRelationship7);
    pkb->storeRelationship(modifyRelationship8);
    pkb->storeRelationship(modifyRelationship9);
    pkb->storeRelationship(modifyRelationship10);
    pkb->storeRelationship(modifyRelationship11);
    pkb->storeRelationship(modifyRelationship12);
    pkb->storeRelationship(modifyRelationship13);
    pkb->storeRelationship(modifyRelationship14);
    pkb->storeRelationship(modifyRelationship15);

    pkb->storePattern(assignPattern1);
    pkb->storePattern(assignPattern2);
    pkb->storePattern(assignPattern3);
    pkb->storePattern(assignPattern4);
    pkb->storePattern(assignPattern5);
    pkb->storePattern(assignPattern6);
    pkb->storePattern(assignPattern7);
    pkb->storePattern(assignPattern8);
    pkb->storePattern(assignPattern9);
    pkb->storePattern(assignPattern10);

    return 0;
}

int dummyForRun = initPKB();

TEST_CASE("Select all queries") {

    SECTION("Select if statements") {
        std::string testQuery = "if ifs; Select ifs";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"8"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Select assign statements") {
        std::string testQuery = "assign a; Select a";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"1", "2", "3", "5", "6", "7", "9", "10", "11", "12"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults.size() == expectedResults.size());
    }

    SECTION("Select read statements") {
        std::string testQuery = "read re; Select re";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
        REQUIRE(testResults.empty());
    }

    SECTION("Select print statements") {
        std::string testQuery = "print p; Select p";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
        REQUIRE(testResults.empty());
    }

    SECTION("Select procedures") {
        std::string testQuery = "procedure p; Select p";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"computeCentroid"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Select while statements") {
        std::string testQuery = "while w; Select w";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"4"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Select variables") {
        std::string testQuery = "variable v; Select v";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"count", "cenX", "cenY", "x", "y", "flag", "normSq"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults.size() == expectedResults.size());
    }

    SECTION("Select constants") {
        std::string testQuery = "constant c; Select c";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"0", "1"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults.size() == expectedResults.size());
    }
}

TEST_CASE("Syntax and Semantics Checks") {
    SECTION("Syntax error - invalid synonym") {
        std::string testQuery = "variable 1; Select v such that Modifies(1, _)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"SyntaxError"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Syntax error - invalid multiple declaration") {
        std::string testQuery = "variable v v1; Select v such that Modifies(1, v1)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Syntax error - invalid multiple single declaration") {
        std::string testQuery = "variable v assign a; Select v such that Modifies(1, v)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Syntax error - invalid design entity") {
        std::string testQuery = "variable v assign a; statement s; Select v such that Modifies(s, v)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Syntax error - typo in design entity") {
        std::string testQuery = "var1able v assign a; statement s; Select v such that Modifies(s, v)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    // Semantically invalid also, but syntax is caught first
    SECTION("Syntax error - invalid subexpression") {
        std::string testQuery = R"(variable v; Select s such that Uses (s, "x") pattern a (_"x", _"y"_))";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"SyntaxError"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Syntax error - missing select clause") {
        std::string testQuery = R"(variable v; assign a; such that Uses (4, "x") pattern a (_"x"_, _"y"_))";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Syntax error - small letter Select") {
        std::string testQuery = R"(variable v; assign a; select v such that Uses (6, "x") pattern a (_"x"_, _"y"_))";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Syntax error - typo in Select") {
        std::string testQuery = R"(variable v; assign a; Seletc v such that Uses (6, "x") pattern a (_"x"_, _"y"_))";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Syntax error - return non-synonym") {
        std::string testQuery = R"(variable v; assign a; Select 4 such that Uses (6, "x") pattern a (_"x"_, _"y"_))";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Syntax error - end with semicolon") {
        std::string testQuery = "variable v; Select v such that Modifies(1, _);";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"SyntaxError"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Syntax error - semicolon in middle of select clause") {
        std::string testQuery = "variable v; Select v such; that Modifies(1, _)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Syntax error - typo in Select") {
        std::string testQuery = R"(variable v; assign a; Seletc v such that Uses (6, "x") pattern a (_"x"_, _"y"_))";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Syntax error - missing bracket in such that clause") {
        std::string testQuery = R"(variable v; assign a; Select v such that Uses 6, "x") pattern a (_"x"_, _"y"_))";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Syntax error - missing bracket in pattern clause") {
        std::string testQuery = R"(variable v; assign a; Select v such that Uses (6, "x") pattern a (_"x"_, _"y"_)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Syntax error - empty second parameter in such that clause") {
        std::string testQuery = R"(variable v; assign a; Select v such that Uses (6, "") pattern a (_"x"_, _"y"_)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Syntax error - empty first parameter in such that clause") {
        std::string testQuery = R"(variable v; assign a; Select v such that Uses ("", "x") pattern a (_"x"_, _"y"_)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Syntax error - empty first parameter in pattern clause") {
        std::string testQuery = R"(variable v; assign a; Select v such that Uses (1, "x") pattern a ("", _"y"_)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Syntax error - empty second parameter in pattern clause") {
        std::string testQuery = R"(variable v; assign a; Select v such that Uses (1, "x") pattern a ("x", "")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Syntax error - invalid wildcard parameter") {
        std::string testQuery = R"(variable v; assign a; Select v such that Uses (1, "x") pattern a ("x", "_")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Syntax error - non-existing relationship") {
        std::string testQuery = R"(variable v; assign a; Select v such that Uses* (1, "x") pattern a ("x", "4")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Syntax error - Uses take in constant value in second param") {
        std::string testQuery = R"(variable v; assign a; Select v such that Uses (1, "6") pattern a ("x", "4")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Syntax error - additional parenthesis") {
        std::string testQuery = "variable v; Select v such that Modifies((1, _))";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"SyntaxError"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Semantics error - synonym not declared") {
        std::string testQuery = "variable v; Select s such that Uses (1, v)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"SemanticError"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Semantics error - ambiguity in first argument") {
        std::string testQuery = "variable v; Select v such that Uses (_, v)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"SemanticError"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Semantics error - read as first param for Uses") {
        std::string testQuery = "variable v; read re; Select v such that Uses (re, v)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Semantics error - print as first param for Modifies") {
        std::string testQuery = "variable v; print pn; Select v such that Modifies (pn, v)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Semantics error - ambiguity in first argument for Modifies") {
        std::string testQuery = "variable v; Select v such that Modifies (_, v)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SemanticError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Semantics error - non-variable as second paramter") {
        std::string testQuery = "constant v; Select v such that Uses (_, v)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SemanticError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Semantics error - non-statement for Follows*") {
        std::string testQuery = "procedure v; Select v such that Follows* (_, v)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SemanticError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Semantics error - non-statement for Follows*") {
        std::string testQuery = "procedure v; Select v such that Follows* (_, v)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SemanticError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Semantics error - non-statement for Follows") {
        std::string testQuery = "constant v; Select v such that Follows (_, v)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SemanticError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Semantics error - non-statement for Parent*") {
        std::string testQuery = "variable v; Select v such that Parent* (_, v)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SemanticError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Semantics error - non-statement for Parent") {
        std::string testQuery = "procedure v; Select v such that Parent (_, v)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SemanticError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("Refactor multiclause test") {
    std::string testQuery = R"(assign a; Select a such that Modifies(a, _) pattern a("count","0"))";
    std::list<std::string> testResults;
    std::list<std::string> expectedResults = {"1"};
    QPS::processQueryResult(testQuery, testResults, qpsClient);
    REQUIRE(testResults == expectedResults);
}

//while w;
//Select w such that Follows(_, w)

TEST_CASE("Debug wildcard, synonym") {
    std::string testQuery = R"(while w; Select w such that Follows(_, w))";
    std::list<std::string> testResults;
    std::list<std::string> expectedResults = {"4"};
    QPS::processQueryResult(testQuery, testResults, qpsClient);
    REQUIRE(testResults == expectedResults);
}

TEST_CASE("Debug synonym, wildcard") {
    std::string testQuery = R"(assign a; Select a such that Follows(a, _))";
    std::list<std::string> testResults;
    std::list<std::string> expectedResults = {"10", "3", "2", "1", "6", "5"};
    QPS::processQueryResult(testQuery, testResults, qpsClient);
    REQUIRE(testResults == expectedResults);
}

TEST_CASE("1 Relationship, 1 Pattern Tests") {
    SECTION("Test 1") {
        std::string testQuery = R"(assign a; stmt s; Select a such that Parent(s, a) pattern a(_, _))";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"11", "6", "9", "5", "7", "10"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Test for same synonym") {
        std::string testQuery = R"(stmt s; Select s such that Follows(s, s))";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
        REQUIRE(testResults.empty());
    }

    SECTION("Test 2") {
        std::string testQuery = R"(assign a; Select a such that Uses(a, "cenX") pattern a(_,_"1"_))";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
        REQUIRE(testResults.empty());
    }

    // a = 1, 5 || a = 6
    SECTION("Test 3") {
        std::string testQuery = R"(assign a; Select a such that Uses(a, "count") pattern a("cenX",_"x"_))";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
        REQUIRE(testResults.empty());
    }


    SECTION("Test 4") {
        std::string testQuery = R"(assign a; variable v; Select v such that Uses(a, v) pattern a(v,_"x"_))";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"cenX"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    // a = 1, 5 || a = 5
    SECTION("Test 5") {
        std::string testQuery = R"(assign a; Select a such that Uses(a, "count") pattern a(_,_"1"_))";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"5"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Test 6") {
        std::string testQuery = R"(assign a; Select a such that Modifies(5, "count") pattern a(_,_"1"_))";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"9", "5"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Test 7") {
        std::string testQuery = R"(assign a; Select a such that Modifies(5, "flag") pattern a(_,_"1"_))";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
        REQUIRE(testResults.empty());
    }
}

TEST_CASE("Relationships and patterns") {
    SECTION("No synonym Clause - return true") {
        std::string testQuery = "variable v; Select v such that Modifies(1, _)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"normSq", "flag", "cenY", "cenX", "count", "y", "x"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("No synonym Clause - return false") {
        std::string testQuery = "variable v; Select v such that Uses(1, _)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
        REQUIRE(testResults.empty());
    }

    SECTION("Single synonym, has select") {
        std::string testQuery = "variable v; Select v such that Uses(12, v)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"cenX", "cenY"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults.size() == expectedResults.size());
    }

    SECTION("Single synonym Clause - Modifies") {
        std::string testQuery = "assign a; Select a such that Modifies(a, _)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"1", "2", "3", "5", "6", "7", "9", "10", "11", "12"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults.size() == expectedResults.size());
    }

    SECTION("Single synonym Clause - Pattern") {
        std::string testQuery = R"(assign a; Select a pattern a("count","0"))";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"1"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Multi Clause - common synonym") {
        std::string testQuery = R"(assign a; Select a such that Modifies(a, _) pattern a("count","0"))";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"1"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Multi Clause - Unrelated to Select") {
        std::string testQuery = R"(assign a; variable v; Select v such that Modifies(a, _) pattern a("count","0"))";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"count", "cenX", "cenY", "x", "y", "flag", "normSq"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults.size() == expectedResults.size());
    }

    SECTION("Multi Clause - Unrelated to Select with pattern clause before such that clause") {
        std::string testQuery = R"(assign a; variable v; Select v pattern a("count","0") such that Modifies(a, _) )";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "count", "cenX", "cenY", "x", "y", "flag", "normSq" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults.size() == expectedResults.size());
    }

    SECTION("Single synonym Clause - Follows") {
        std::string testQuery = "stmt s; Select s such that Follows(1, s)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"2"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Multi Clause - One clause related to Select") {
        std::string testQuery = "stmt s; variable v; Select s such that Modifies(s, v)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"1", "2", "3", "12", "6", "9", "11", "5", "7", "10"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Multi Clause - One clause related to Select") {
        std::string testQuery = "assign a; Select a pattern a(_,\"1\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"9"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Multi Clause - One clause related to Select") {
        std::string testQuery = "stmt s; variable v; assign a; Select a such that Modifies(s, v) pattern a(_,\"1\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"9"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Multi Clause - common synonym") {
        std::string testQuery = "variable v; Select v such that Modifies(1, v)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"count"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Multi Clause - common synonym") {
        std::string testQuery = "variable v; assign a; Select v pattern a(v,\"1\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"flag"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Multi Clause - common synonym") {
        std::string testQuery = "assign a; variable v; Select v such that Modifies(1, v) pattern a(v,\"1\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
        REQUIRE(testResults.empty());
    }

    SECTION("Multiple common synonym") {
        std::string testQuery = "assign a; variable v; Select v such that Modifies(a, v) pattern a(v, \"x\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
        REQUIRE(testResults.empty());
    }

    SECTION("Multi Clause - query broken up into 2 lines") {
        std::string testQuery = "stmt s; variable v; assign a;\n Select a such that Modifies(s, v) pattern a(_,\"1\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "9" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Multi Clause - query broken up into 2 lines in middle of pattern clause") {
        std::string testQuery = "stmt s; variable v; assign a; Select a such that Modifies(s, v) pattern a\n(_,\"1\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "9" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Multi Clause - query broken up into 2 lines in middle of such that clause") {
        std::string testQuery = "stmt s; variable v; assign a; Select a such that Modifies(\ns, v) pattern a(_,\"1\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "9" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Multi Clause - query broken up into 2 lines in middle of declaration") {
        std::string testQuery = "stmt s; variable v\n; assign a; Select a such that Modifies(s, v) pattern a(_,\"1\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "9" };
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Follows* Clause") {
        std::string testQuery = "stmt s; Select s such that Follows*(1, s)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"12", "8", "4", "3", "2"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Parent* Clause") {
        std::string testQuery = "stmt s, s1; Select s such that Parent*(s, s1)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"4", "8"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Same synonym as parameters in Follows") {
        std::string testQuery = "stmt s; Select s such that Follows(s, s)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
        REQUIRE(testResults.empty());
    }

    SECTION("Non-container statement as parameters in Parent") {
        std::string testQuery = "stmt s; assign a; Select s such that Parent(a, s)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
        REQUIRE(testResults.empty());
    }
}


