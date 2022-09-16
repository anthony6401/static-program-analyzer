#include <catch.hpp>
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/Evaluator.h"
#include "components/pkb/PKB.h"
#include "models/Entity/Entity.h"
#include "models/Entity/AssignEntity.h"
#include "models/Entity/IfEntity.h"
#include "models/Entity/WhileEntity.h"
#include "models/Entity/ProcedureEntity.h"
#include "models/Entity/ConstantEntity.h"
#include "models/Entity/VariableEntity.h"
#include "models/Entity/PrintEntity.h"
#include "models/Entity/ReadEntity.h"
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
// Sample source code:

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

// PQL queries
TEST_CASE("Select all queries") {

    SECTION("Select if statements") {
        std::string testQuery = "if ifs; Select if";
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
        std::list<std::string> expectedResults = {"none"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Select print statements") {
        std::string testQuery = "print p; Select p";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"none"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Select procedures") {
        std::string testQuery = "procedure p; Select p";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"computeCentroid"};
        QPS::processQueryResult(testQuery, testResults, qpsClient);
        REQUIRE(testResults == expectedResults);
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


