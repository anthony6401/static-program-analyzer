#include <catch.hpp>
#include "components/qps/QPS.h"
#include "components/qps/abstract_query_object/QueryObject.h"
#include "components/qps/query_evaluator/Evaluator.h"
#include "models/Entity/Entity.h"
#include "models/Entity/AssignEntity.h"
#include "models/Entity/IfEntity.h"
#include "models/Entity/WhileEntity.h"
#include "models/Entity/ProcedureEntity.h"
#include "models/Entity/ConstantEntity.h"
#include "models/Entity/VariableEntity.h"
#include "models/Entity/ReadEntity.h"
#include "models/Entity/PrintEntity.h"
#include "models/Entity/CallEntity.h"
#include "models/Relationship/Relationship.h"
#include "models/Relationship/UsesRelationship.h"
#include "models/Relationship/ModifyRelationship.h"
#include "models/Relationship/FollowsRelationship.h"
#include "models/Relationship/FollowsTRelationship.h"
#include "models/Relationship/ParentRelationship.h"
#include "models/Relationship/ParentTRelationship.h"
#include "models/Relationship/NextRelationship.h"
#include "models/Relationship/CallsRelationship.h"
#include "models/Relationship/CallsTRelationship.h"
#include "models/Pattern/Pattern.h"
#include "models/Pattern/AssignPattern.h"
#include "models/Pattern/WhilePattern.h"
#include "models/Pattern/IfPattern.h"
#include "components/qps/QPS.h"
#include <iostream>

// Populating data in PKB
PKB* pkb_m2 = new PKB();
auto qpsClient_m2 = QPSClient(pkb_m2);

// Stmt Entity
static Entity* stmt1 = new ReadEntity("1", "x");
static Entity* stmt2 = new ReadEntity("2", "z");
static Entity* stmt3 = new CallEntity("3", "Second");
static Entity* stmt4 = new AssignEntity("4");
static Entity* stmt5 = new AssignEntity("5");
static Entity* stmt6 = new WhileEntity("6");
static Entity* stmt7 = new AssignEntity("7");
static Entity* stmt8 = new CallEntity("8", "Third");
static Entity* stmt9 = new AssignEntity("9");
static Entity* stmt10 = new IfEntity("10");
static Entity* stmt11 = new AssignEntity("11");
static Entity* stmt12 = new AssignEntity("12");
static Entity* stmt13 = new AssignEntity("13");
static Entity* stmt14 = new AssignEntity("14");
static Entity* stmt15 = new AssignEntity("15");
static Entity* stmt16 = new AssignEntity("16");
static Entity* stmt17 = new AssignEntity("17");
static Entity* stmt18 = new PrintEntity("18", "v");

// Proc Entity
static Entity* procFirst = new ProcedureEntity("First");
static Entity* procSecond = new ProcedureEntity("Second");
static Entity* procThird = new ProcedureEntity("Third");

// Variable Entity
static Entity* variableX = new VariableEntity("x");
static Entity* variableY = new VariableEntity("y");
static Entity* variableZ = new VariableEntity("z");
static Entity* variableI = new VariableEntity("i");
static Entity* variableV = new VariableEntity("v");

// Constant Entity
static Entity* constant0 = new ConstantEntity("0");
static Entity* constant1 = new ConstantEntity("1");
static Entity* constant2 = new ConstantEntity("2");
static Entity* constant5 = new ConstantEntity("5");

// Follows Relationship
static Relationship* followsRelationship1 = new FollowsRelationship(stmt1, stmt2);
static Relationship* followsRelationship2 = new FollowsRelationship(stmt2, stmt3);
static Relationship* followsRelationship3 = new FollowsRelationship(stmt4, stmt5);
static Relationship* followsRelationship4 = new FollowsRelationship(stmt5, stmt6);
static Relationship* followsRelationship5 = new FollowsRelationship(stmt6, stmt10);
static Relationship* followsRelationship6 = new FollowsRelationship(stmt10, stmt13);
static Relationship* followsRelationship7 = new FollowsRelationship(stmt13, stmt14);
static Relationship* followsRelationship8 = new FollowsRelationship(stmt14, stmt15);
static Relationship* followsRelationship9 = new FollowsRelationship(stmt16, stmt17);
static Relationship* followsRelationship10 = new FollowsRelationship(stmt17, stmt18);
static Relationship* followsRelationship11 = new FollowsRelationship(stmt7, stmt8);
static Relationship* followsRelationship12 = new FollowsRelationship(stmt8, stmt9);

// Follows* Relationship
static Relationship* followsTRelationship1 = new FollowsTRelationship(stmt1, stmt2);
static Relationship* followsTRelationship2 = new FollowsTRelationship(stmt1, stmt3);
static Relationship* followsTRelationship3 = new FollowsTRelationship(stmt2, stmt3);
static Relationship* followsTRelationship4 = new FollowsTRelationship(stmt4, stmt5);
static Relationship* followsTRelationship5 = new FollowsTRelationship(stmt4, stmt6);
static Relationship* followsTRelationship6 = new FollowsTRelationship(stmt4, stmt10);
static Relationship* followsTRelationship7 = new FollowsTRelationship(stmt4, stmt13);
static Relationship* followsTRelationship8 = new FollowsTRelationship(stmt4, stmt14);
static Relationship* followsTRelationship9 = new FollowsTRelationship(stmt4, stmt15);
static Relationship* followsTRelationship10 = new FollowsTRelationship(stmt5, stmt6);
static Relationship* followsTRelationship11 = new FollowsTRelationship(stmt5, stmt10);
static Relationship* followsTRelationship12 = new FollowsTRelationship(stmt5, stmt13);
static Relationship* followsTRelationship13 = new FollowsTRelationship(stmt5, stmt14);
static Relationship* followsTRelationship14 = new FollowsTRelationship(stmt5, stmt15);
static Relationship* followsTRelationship15 = new FollowsTRelationship(stmt6, stmt10);
static Relationship* followsTRelationship16 = new FollowsTRelationship(stmt6, stmt13);
static Relationship* followsTRelationship17 = new FollowsTRelationship(stmt6, stmt14);
static Relationship* followsTRelationship18 = new FollowsTRelationship(stmt6, stmt15);
static Relationship* followsTRelationship19 = new FollowsTRelationship(stmt10, stmt13);
static Relationship* followsTRelationship20 = new FollowsTRelationship(stmt10, stmt14);
static Relationship* followsTRelationship21 = new FollowsTRelationship(stmt10, stmt15);
static Relationship* followsTRelationship22 = new FollowsTRelationship(stmt13, stmt14);
static Relationship* followsTRelationship23 = new FollowsTRelationship(stmt13, stmt15);
static Relationship* followsTRelationship24 = new FollowsTRelationship(stmt14, stmt15);
static Relationship* followsTRelationship25 = new FollowsTRelationship(stmt16, stmt17);
static Relationship* followsTRelationship26 = new FollowsTRelationship(stmt16, stmt18);
static Relationship* followsTRelationship27 = new FollowsTRelationship(stmt17, stmt18);
static Relationship* followsTRelationship28 = new FollowsTRelationship(stmt7, stmt8);
static Relationship* followsTRelationship29 = new FollowsTRelationship(stmt7, stmt9);
static Relationship* followsTRelationship30 = new FollowsTRelationship(stmt8, stmt9);

// Parent Relationship
static Relationship* parentRelationship1 = new ParentRelationship(stmt6, stmt7);
static Relationship* parentRelationship2 = new ParentRelationship(stmt6, stmt8);
static Relationship* parentRelationship3 = new ParentRelationship(stmt6, stmt9);
static Relationship* parentRelationship4 = new ParentRelationship(stmt10, stmt11);
static Relationship* parentRelationship5 = new ParentRelationship(stmt10, stmt12);

// Parent* Relationship
static Relationship* parentTRelationship1 = new ParentTRelationship(stmt6, stmt7);
static Relationship* parentTRelationship2 = new ParentTRelationship(stmt6, stmt8);
static Relationship* parentTRelationship3 = new ParentTRelationship(stmt6, stmt9);
static Relationship* parentTRelationship4 = new ParentTRelationship(stmt10, stmt11);
static Relationship* parentTRelationship5 = new ParentTRelationship(stmt10, stmt12);

// Uses Relationship
static Relationship* usesRelationship1 = new UsesRelationship(procFirst, variableI);
static Relationship* usesRelationship2 = new UsesRelationship(procFirst, variableX);
static Relationship* usesRelationship3 = new UsesRelationship(procFirst, variableY);
static Relationship* usesRelationship4 = new UsesRelationship(procFirst, variableZ);
static Relationship* usesRelationship5 = new UsesRelationship(procFirst, variableV);
static Relationship* usesRelationship6 = new UsesRelationship(procSecond, variableI);
static Relationship* usesRelationship7 = new UsesRelationship(procSecond, variableX);
static Relationship* usesRelationship8 = new UsesRelationship(procSecond, variableY);
static Relationship* usesRelationship9 = new UsesRelationship(procSecond, variableZ);
static Relationship* usesRelationship10 = new UsesRelationship(procSecond, variableV);
static Relationship* usesRelationship11 = new UsesRelationship(procThird, variableV);
static Relationship* usesRelationship12 = new UsesRelationship(procThird, variableZ);
static Relationship* usesRelationship13 = new UsesRelationship(stmt3, variableI);
static Relationship* usesRelationship14 = new UsesRelationship(stmt3, variableX);
static Relationship* usesRelationship15 = new UsesRelationship(stmt3, variableY);
static Relationship* usesRelationship16 = new UsesRelationship(stmt3, variableZ);
static Relationship* usesRelationship17 = new UsesRelationship(stmt3, variableV);
static Relationship* usesRelationship18 = new UsesRelationship(stmt6, variableI);
static Relationship* usesRelationship19 = new UsesRelationship(stmt6, variableX);
static Relationship* usesRelationship20 = new UsesRelationship(stmt6, variableY);
static Relationship* usesRelationship21 = new UsesRelationship(stmt6, variableV);
static Relationship* usesRelationship22 = new UsesRelationship(stmt6, variableZ);
static Relationship* usesRelationship23 = new UsesRelationship(stmt7, variableX);
static Relationship* usesRelationship24 = new UsesRelationship(stmt7, variableY);
static Relationship* usesRelationship25 = new UsesRelationship(stmt8, variableV);
static Relationship* usesRelationship26 = new UsesRelationship(stmt8, variableZ);
static Relationship* usesRelationship27 = new UsesRelationship(stmt9, variableI);
static Relationship* usesRelationship28 = new UsesRelationship(stmt10, variableX);
static Relationship* usesRelationship29 = new UsesRelationship(stmt11, variableX);
static Relationship* usesRelationship30 = new UsesRelationship(stmt13, variableZ);
static Relationship* usesRelationship31 = new UsesRelationship(stmt13, variableX);
static Relationship* usesRelationship32 = new UsesRelationship(stmt13, variableI);
static Relationship* usesRelationship33 = new UsesRelationship(stmt14, variableZ);
static Relationship* usesRelationship34 = new UsesRelationship(stmt15, variableX);
static Relationship* usesRelationship35 = new UsesRelationship(stmt15, variableY);
static Relationship* usesRelationship36 = new UsesRelationship(stmt15, variableZ);
static Relationship* usesRelationship37 = new UsesRelationship(stmt17, variableZ);
static Relationship* usesRelationship38 = new UsesRelationship(stmt18, variableV);

// Modifies Relationship
static Relationship* modifyRelationship1 = new ModifyRelationship(procFirst, variableX);
static Relationship* modifyRelationship2 = new ModifyRelationship(procFirst, variableY);
static Relationship* modifyRelationship3 = new ModifyRelationship(procFirst, variableI);
static Relationship* modifyRelationship4 = new ModifyRelationship(procFirst, variableZ);
static Relationship* modifyRelationship5 = new ModifyRelationship(procFirst, variableV);
static Relationship* modifyRelationship6 = new ModifyRelationship(procSecond, variableX);
static Relationship* modifyRelationship7 = new ModifyRelationship(procSecond, variableY);
static Relationship* modifyRelationship8 = new ModifyRelationship(procSecond, variableI);
static Relationship* modifyRelationship9 = new ModifyRelationship(procSecond, variableZ);
static Relationship* modifyRelationship10 = new ModifyRelationship(procSecond, variableV);
static Relationship* modifyRelationship11 = new ModifyRelationship(procThird, variableZ);
static Relationship* modifyRelationship12 = new ModifyRelationship(procThird, variableV);
static Relationship* modifyRelationship13 = new ModifyRelationship(stmt1, variableX);
static Relationship* modifyRelationship14 = new ModifyRelationship(stmt2, variableY);
static Relationship* modifyRelationship15 = new ModifyRelationship(stmt3, variableX);
static Relationship* modifyRelationship16 = new ModifyRelationship(stmt3, variableY);
static Relationship* modifyRelationship17 = new ModifyRelationship(stmt3, variableI);
static Relationship* modifyRelationship18 = new ModifyRelationship(stmt3, variableZ);
static Relationship* modifyRelationship19 = new ModifyRelationship(stmt3, variableV);
static Relationship* modifyRelationship20 = new ModifyRelationship(stmt4, variableX);
static Relationship* modifyRelationship21 = new ModifyRelationship(stmt5, variableI);
static Relationship* modifyRelationship22 = new ModifyRelationship(stmt6, variableX);
static Relationship* modifyRelationship23 = new ModifyRelationship(stmt6, variableZ);
static Relationship* modifyRelationship24 = new ModifyRelationship(stmt6, variableV);
static Relationship* modifyRelationship25 = new ModifyRelationship(stmt6, variableI);
static Relationship* modifyRelationship26 = new ModifyRelationship(stmt7, variableX);
static Relationship* modifyRelationship27 = new ModifyRelationship(stmt8, variableZ);
static Relationship* modifyRelationship28 = new ModifyRelationship(stmt8, variableV);
static Relationship* modifyRelationship29 = new ModifyRelationship(stmt9, variableI);
static Relationship* modifyRelationship30 = new ModifyRelationship(stmt10, variableX);
static Relationship* modifyRelationship31 = new ModifyRelationship(stmt10, variableZ);
static Relationship* modifyRelationship32 = new ModifyRelationship(stmt11, variableX);
static Relationship* modifyRelationship33 = new ModifyRelationship(stmt12, variableZ);
static Relationship* modifyRelationship34 = new ModifyRelationship(stmt13, variableZ);
static Relationship* modifyRelationship35 = new ModifyRelationship(stmt14, variableY);
static Relationship* modifyRelationship36 = new ModifyRelationship(stmt15, variableX);
static Relationship* modifyRelationship37 = new ModifyRelationship(stmt16, variableZ);
static Relationship* modifyRelationship38 = new ModifyRelationship(stmt17, variableV);

// Next Relationship
static Relationship* nextRelationship1 = new NextRelationship(stmt1, stmt2);
static Relationship* nextRelationship2 = new NextRelationship(stmt2, stmt3);
static Relationship* nextRelationship3 = new NextRelationship(stmt4, stmt5);
static Relationship* nextRelationship4 = new NextRelationship(stmt5, stmt6);
static Relationship* nextRelationship5 = new NextRelationship(stmt6, stmt7);
static Relationship* nextRelationship6 = new NextRelationship(stmt7, stmt8);
static Relationship* nextRelationship7 = new NextRelationship(stmt8, stmt9);
static Relationship* nextRelationship8 = new NextRelationship(stmt9, stmt6);
static Relationship* nextRelationship9 = new NextRelationship(stmt6, stmt10);
static Relationship* nextRelationship10 = new NextRelationship(stmt10, stmt11);
static Relationship* nextRelationship11 = new NextRelationship(stmt10, stmt12);
static Relationship* nextRelationship12 = new NextRelationship(stmt11, stmt13);
static Relationship* nextRelationship13 = new NextRelationship(stmt12, stmt13);
static Relationship* nextRelationship14 = new NextRelationship(stmt13, stmt14);
static Relationship* nextRelationship15 = new NextRelationship(stmt14, stmt15);
static Relationship* nextRelationship16 = new NextRelationship(stmt16, stmt17);
static Relationship* nextRelationship17 = new NextRelationship(stmt17, stmt18);

// Calls Relationship
static Relationship* callsRelationship1 = new CallsRelationship(procFirst, procSecond);
static Relationship* callsRelationship2 = new CallsRelationship(procSecond, procThird);

// Calls* Relationship
static Relationship* callsTRelationship1 = new CallsTRelationship(procFirst, procSecond);
static Relationship* callsTRelationship2 = new CallsTRelationship(procFirst, procThird);
static Relationship* callsTRelationship3 = new CallsTRelationship(procSecond, procThird);

// Assign Pattern
static kb::Pattern* assignPattern1 = new AssignPattern("4", "x", "0");
static kb::Pattern* assignPattern2 = new AssignPattern("5", "i", "5");
static kb::Pattern* assignPattern3 = new AssignPattern("7", "x", "x+2*y");
static kb::Pattern* assignPattern4 = new AssignPattern("9", "i", "i-1");
static kb::Pattern* assignPattern5 = new AssignPattern("11", "x", "x+1");
static kb::Pattern* assignPattern6 = new AssignPattern("12", "z", "1");
static kb::Pattern* assignPattern7 = new AssignPattern("13", "z", "z+x+i");
static kb::Pattern* assignPattern8 = new AssignPattern("14", "y", "z+2");
static kb::Pattern* assignPattern9 = new AssignPattern("15", "x", "x*y+z");
static kb::Pattern* assignPattern10 = new AssignPattern("16", "z", "5");
static kb::Pattern* assignPattern11 = new AssignPattern("17", "v", "z");

// While Pattern
static kb::Pattern* whilePattern1 = new WhilePattern("6", "i");

// If Pattern
static kb::Pattern* ifPattern1 = new IfPattern("10", "x");

static int initPKB() {
    pkb_m2->storeConstant(constant0);
    pkb_m2->storeConstant(constant1);
    pkb_m2->storeConstant(constant2);
    pkb_m2->storeConstant(constant5);

    pkb_m2->storeRelationship(followsRelationship1);
    pkb_m2->storeRelationship(followsRelationship2);
    pkb_m2->storeRelationship(followsRelationship3);
    pkb_m2->storeRelationship(followsRelationship4);
    pkb_m2->storeRelationship(followsRelationship5);
    pkb_m2->storeRelationship(followsRelationship6);
    pkb_m2->storeRelationship(followsRelationship7);
    pkb_m2->storeRelationship(followsRelationship8);
    pkb_m2->storeRelationship(followsRelationship9);
    pkb_m2->storeRelationship(followsRelationship10);
    pkb_m2->storeRelationship(followsRelationship11);
    pkb_m2->storeRelationship(followsRelationship12);

    pkb_m2->storeRelationship(followsTRelationship1);
    pkb_m2->storeRelationship(followsTRelationship2);
    pkb_m2->storeRelationship(followsTRelationship3);
    pkb_m2->storeRelationship(followsTRelationship4);
    pkb_m2->storeRelationship(followsTRelationship5);
    pkb_m2->storeRelationship(followsTRelationship6);
    pkb_m2->storeRelationship(followsTRelationship7);
    pkb_m2->storeRelationship(followsTRelationship8);
    pkb_m2->storeRelationship(followsTRelationship9);
    pkb_m2->storeRelationship(followsTRelationship10);
    pkb_m2->storeRelationship(followsTRelationship11);
    pkb_m2->storeRelationship(followsTRelationship12);
    pkb_m2->storeRelationship(followsTRelationship13);
    pkb_m2->storeRelationship(followsTRelationship14);
    pkb_m2->storeRelationship(followsTRelationship15);
    pkb_m2->storeRelationship(followsTRelationship16);
    pkb_m2->storeRelationship(followsTRelationship17);
    pkb_m2->storeRelationship(followsTRelationship18);
    pkb_m2->storeRelationship(followsTRelationship19);
    pkb_m2->storeRelationship(followsTRelationship20);
    pkb_m2->storeRelationship(followsTRelationship21);
    pkb_m2->storeRelationship(followsTRelationship22);
    pkb_m2->storeRelationship(followsTRelationship23);
    pkb_m2->storeRelationship(followsTRelationship24);
    pkb_m2->storeRelationship(followsTRelationship25);
    pkb_m2->storeRelationship(followsTRelationship26);
    pkb_m2->storeRelationship(followsTRelationship27);
    pkb_m2->storeRelationship(followsTRelationship28);
    pkb_m2->storeRelationship(followsTRelationship29);
    pkb_m2->storeRelationship(followsTRelationship30);

    pkb_m2->storeRelationship(parentRelationship1);
    pkb_m2->storeRelationship(parentRelationship2);
    pkb_m2->storeRelationship(parentRelationship3);
    pkb_m2->storeRelationship(parentRelationship4);
    pkb_m2->storeRelationship(parentRelationship5);

    pkb_m2->storeRelationship(parentTRelationship1);
    pkb_m2->storeRelationship(parentTRelationship2);
    pkb_m2->storeRelationship(parentTRelationship3);
    pkb_m2->storeRelationship(parentTRelationship4);
    pkb_m2->storeRelationship(parentTRelationship5);

    pkb_m2->storeRelationship(usesRelationship1);
    pkb_m2->storeRelationship(usesRelationship2);
    pkb_m2->storeRelationship(usesRelationship3);
    pkb_m2->storeRelationship(usesRelationship4);
    pkb_m2->storeRelationship(usesRelationship5);
    pkb_m2->storeRelationship(usesRelationship6);
    pkb_m2->storeRelationship(usesRelationship7);
    pkb_m2->storeRelationship(usesRelationship8);
    pkb_m2->storeRelationship(usesRelationship9);
    pkb_m2->storeRelationship(usesRelationship10);
    pkb_m2->storeRelationship(usesRelationship11);
    pkb_m2->storeRelationship(usesRelationship12);
    pkb_m2->storeRelationship(usesRelationship13);
    pkb_m2->storeRelationship(usesRelationship14);
    pkb_m2->storeRelationship(usesRelationship15);
    pkb_m2->storeRelationship(usesRelationship16);
    pkb_m2->storeRelationship(usesRelationship17);
    pkb_m2->storeRelationship(usesRelationship18);
    pkb_m2->storeRelationship(usesRelationship19);
    pkb_m2->storeRelationship(usesRelationship20);
    pkb_m2->storeRelationship(usesRelationship21);
    pkb_m2->storeRelationship(usesRelationship22);
    pkb_m2->storeRelationship(usesRelationship23);
    pkb_m2->storeRelationship(usesRelationship24);
    pkb_m2->storeRelationship(usesRelationship25);
    pkb_m2->storeRelationship(usesRelationship26);
    pkb_m2->storeRelationship(usesRelationship27);
    pkb_m2->storeRelationship(usesRelationship28);
    pkb_m2->storeRelationship(usesRelationship29);
    pkb_m2->storeRelationship(usesRelationship30);
    pkb_m2->storeRelationship(usesRelationship31);
    pkb_m2->storeRelationship(usesRelationship32);
    pkb_m2->storeRelationship(usesRelationship33);
    pkb_m2->storeRelationship(usesRelationship34);
    pkb_m2->storeRelationship(usesRelationship35);
    pkb_m2->storeRelationship(usesRelationship36);
    pkb_m2->storeRelationship(usesRelationship37);
    pkb_m2->storeRelationship(usesRelationship38);

    pkb_m2->storeRelationship(modifyRelationship1);
    pkb_m2->storeRelationship(modifyRelationship2);
    pkb_m2->storeRelationship(modifyRelationship3);
    pkb_m2->storeRelationship(modifyRelationship4);
    pkb_m2->storeRelationship(modifyRelationship5);
    pkb_m2->storeRelationship(modifyRelationship6);
    pkb_m2->storeRelationship(modifyRelationship7);
    pkb_m2->storeRelationship(modifyRelationship8);
    pkb_m2->storeRelationship(modifyRelationship9);
    pkb_m2->storeRelationship(modifyRelationship10);
    pkb_m2->storeRelationship(modifyRelationship11);
    pkb_m2->storeRelationship(modifyRelationship12);
    pkb_m2->storeRelationship(modifyRelationship13);
    pkb_m2->storeRelationship(modifyRelationship14);
    pkb_m2->storeRelationship(modifyRelationship15);
    pkb_m2->storeRelationship(modifyRelationship16);
    pkb_m2->storeRelationship(modifyRelationship17);
    pkb_m2->storeRelationship(modifyRelationship18);
    pkb_m2->storeRelationship(modifyRelationship19);
    pkb_m2->storeRelationship(modifyRelationship20);
    pkb_m2->storeRelationship(modifyRelationship21);
    pkb_m2->storeRelationship(modifyRelationship22);
    pkb_m2->storeRelationship(modifyRelationship23);
    pkb_m2->storeRelationship(modifyRelationship24);
    pkb_m2->storeRelationship(modifyRelationship25);
    pkb_m2->storeRelationship(modifyRelationship26);
    pkb_m2->storeRelationship(modifyRelationship27);
    pkb_m2->storeRelationship(modifyRelationship28);
    pkb_m2->storeRelationship(modifyRelationship29);
    pkb_m2->storeRelationship(modifyRelationship30);
    pkb_m2->storeRelationship(modifyRelationship31);
    pkb_m2->storeRelationship(modifyRelationship32);
    pkb_m2->storeRelationship(modifyRelationship33);
    pkb_m2->storeRelationship(modifyRelationship34);
    pkb_m2->storeRelationship(modifyRelationship35);
    pkb_m2->storeRelationship(modifyRelationship36);
    pkb_m2->storeRelationship(modifyRelationship37);
    pkb_m2->storeRelationship(modifyRelationship38);

    pkb_m2->storeRelationship(nextRelationship1);
    pkb_m2->storeRelationship(nextRelationship2);
    pkb_m2->storeRelationship(nextRelationship3);
    pkb_m2->storeRelationship(nextRelationship4);
    pkb_m2->storeRelationship(nextRelationship5);
    pkb_m2->storeRelationship(nextRelationship6);
    pkb_m2->storeRelationship(nextRelationship7);
    pkb_m2->storeRelationship(nextRelationship8);
    pkb_m2->storeRelationship(nextRelationship9);
    pkb_m2->storeRelationship(nextRelationship10);
    pkb_m2->storeRelationship(nextRelationship11);
    pkb_m2->storeRelationship(nextRelationship12);
    pkb_m2->storeRelationship(nextRelationship13);
    pkb_m2->storeRelationship(nextRelationship14);
    pkb_m2->storeRelationship(nextRelationship15);
    pkb_m2->storeRelationship(nextRelationship16);
    pkb_m2->storeRelationship(nextRelationship17);

    pkb_m2->storeRelationship(callsRelationship1);
    pkb_m2->storeRelationship(callsRelationship2);

    pkb_m2->storeRelationship(callsTRelationship1);
    pkb_m2->storeRelationship(callsTRelationship2);
    pkb_m2->storeRelationship(callsTRelationship3);

    pkb_m2->storePattern(assignPattern1);
    pkb_m2->storePattern(assignPattern2);
    pkb_m2->storePattern(assignPattern3);
    pkb_m2->storePattern(assignPattern4);
    pkb_m2->storePattern(assignPattern5);
    pkb_m2->storePattern(assignPattern6);
    pkb_m2->storePattern(assignPattern7);
    pkb_m2->storePattern(assignPattern8);
    pkb_m2->storePattern(assignPattern9);
    pkb_m2->storePattern(assignPattern10);
    pkb_m2->storePattern(assignPattern11);

    pkb_m2->storePattern(ifPattern1);

    pkb_m2->storePattern(whilePattern1);

    return 0;
}

static int dummyForRun = initPKB();

// PQL queries
TEST_CASE("Calls queries") {
    SECTION("Calls Test 1") {
        std::string testQuery = "procedure p, p1; \n "
                                "Select p such that Calls(\"First\", \"Second\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"Third", "Second", "First"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls Test 2") {
        std::string testQuery = "procedure p; \n "
                                "Select p such that Calls(p, _)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"Second", "First"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
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

    SECTION("Calls Test 5") {
        std::string testQuery = "procedure p, p1; \n "
            "Select p such that Calls(\"First\", \"Third\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults.empty() == true);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls Test 6") {
        std::string testQuery = "procedure p, p1; \n "
            "Select p such that Calls(\"First\", \"First\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults.empty() == true);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls Test 7") {
        std::string testQuery = "procedure p; call call; \n "
            "Select call such that Calls(\"First\", \"Second\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"8", "3"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls Test 8") {
        std::string testQuery = "procedure p, p1; \n "
            "Select p such that Calls(1, _)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"SyntaxError"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls Test 9") {
        std::string testQuery = "procedure p, p1; \n "
            "Select p such that Calls(3, _)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls Test 10") {
        std::string testQuery = "procedure p, p1; \n "
            "Select p such that Calls(_, 3)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls Test 11") {
        std::string testQuery = "procedure p; stmt p1; \n "
            "Select p such that Calls(p, p1)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SemanticError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("Calls* queries") {
    SECTION("Calls* Test 1") {
        std::string testQuery = "procedure p; \n "
                                "Select p such that Calls*(_, _)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"Third", "Second", "First"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls* Test 2") {
        std::string testQuery = "procedure p, p1; \n "
                                "Select p1 such that Calls*(\"First\", \"Third\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"Third", "Second", "First"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls* Test 3") {
        std::string testQuery = "procedure p, p1; \n "
                                "Select p1 such that Calls*(p, p1)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"Second", "Third"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls* Test 4") {
        std::string testQuery = "procedure p, p1; \n "
            "Select p1 such that Calls*(p, p1)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "Second", "Third" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls* Test 5") {
        std::string testQuery = "procedure p, p1; \n "
            "Select p1 such that Calls*(\"First\", \"Second\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "Third", "Second", "First" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls* Test 6") {
        std::string testQuery = "procedure p, p1; \n "
            "Select p1 such that Calls*(5, _)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls* Test 7") {
        std::string testQuery = "procedure p, p1; \n "
            "Select p1 such that Calls*(_, 6)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls* Test 8") {
        std::string testQuery = "stmt p, p1; \n "
            "Select p1 such that Calls*(p, _)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SemanticError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls* Test 9") {
        std::string testQuery = "procedure p, p1; call call; \n "
            "Select p1 such that Calls*(call, _)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"SemanticError"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("Next queries") {
    SECTION("Next Test 1") {
        std::string testQuery = "procedure p; \n "
                                "Select p such that Next(2, 3)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"Third", "Second", "First"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Next Test 2") {
        std::string testQuery = "read re; \n "
                                "Select re such that Next(re , 3)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"2"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("Next* queries") {
    SECTION("Next* Test 1") {
        std::string testQuery = "assign a; \n "
                                "Select a such that Next*(8, a)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"14", "13", "15", "12", "11", "9", "7"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
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

TEST_CASE("Multi-clause queries") {
    SECTION("Multi-clause Test 1") {
        std::string testQuery = "assign a; while w; \n "
                                "Select a pattern a (\"x\", _) such that Parent* (w, a) and Next* (4, a)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"7"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Multi-clause Test 2") {
        std::string testQuery = "assign a; while w;\n "
                                "Select a such that Modifies (a, \"x\") and Parent* (w, a) and Next* (4, a)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"7"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Multi-clause Test 3") {
        std::string testQuery = "stmt s;\n "
                                "Select s such that Next* (8, s) and Next* (s, 15)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"14", "12", "11", "6", "9", "13", "10", "8", "7"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Multi-clause Test 4") {
        std::string testQuery = "procedure p;\n "
                                "Select p such that Calls (p, \"Third\") and Modifies (p, \"i\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"Second"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Multi-clause Test 5") {
        std::string testQuery = "assign a; while w; \n "
                                "Select a pattern a (\"x\", _) such that Parent* (w, a) and Modifies (11, \"x\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"7"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Multi-clause Test 6") {
        std::string testQuery = "assign and; while w; \n "
            "Select and pattern and (\"x\", _) such that Parent* (w, and) and Modifies (11, \"x\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "7" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Multi-clause Test 7") {
        std::string testQuery = "assign a; while w; \n "
            "Select a pattern a (\"x\", _) and Parent* (w, a) and Modifies (11, \"x\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Multi-clause Test 8") {
        std::string testQuery = "assign and; while w; \n "
            "Select and pattern a (\"x\", _) such that Parent* (w, adn) and Modifies (11, \"x\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SemanticError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Multi-clause Test 9") {
        std::string testQuery = "assign and, pattern; while Calls; \n "
            "Select and pattern  pattern(\"x\", _) such that Parent* (Calls, and) and Modifies (11, \"x\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "7", "9" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Multi-clause Test 10") {
        std::string testQuery = "assign a; while w; \n "
            "Select a pattern a (\"x\", _) and such that Parent* (w, a) and Modifies (11, \"x\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Multi-clause Test 5") {
        std::string testQuery = "assign a; while w; \n "
            "Select a pattern a (\"x\", _) such that Parent* (w, a) Modifies (11, \"x\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SyntaxError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

}

TEST_CASE("BOOLEAN queries") {
    SECTION("BOOLEAN Test 1 - 1 True") {
        std::string testQuery = "assign a; while w; \n "
                                "Select BOOLEAN such that Modifies(7, \"x\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "TRUE" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("BOOLEAN Test 2 - 1 True") {
        std::string testQuery = "assign a; while w; \n "
                                "Select BOOLEAN such that Modifies(2, \"y\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "TRUE" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("BOOLEAN Test 3 - 1 False") {
        std::string testQuery = "assign a; while w; \n "
                                "Select BOOLEAN such that Modifies(18, \"v\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "FALSE" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("BOOLEAN Test 4 - 2 False") {
        std::string testQuery = "assign a; while w; \n "
                                "Select BOOLEAN such that Modifies(18, \"v\") and Parent(w, 13)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "FALSE" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("BOOLEAN Test 5 - 2 True") {
        std::string testQuery = "procedure p; \n "
                                "Select BOOLEAN such that Uses(18, \"v\") and Calls(\"First\", p)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "TRUE" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("BOOLEAN Test 6 - 1 False, 1 True") {
        std::string testQuery = "procedure p; \n "
                                "Select BOOLEAN such that Modifies(2, \"z\") such that Calls(p, \"Third\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "FALSE" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("BOOLEAN Test 7 - 1 True, 1 False") {
        std::string testQuery = "variable v; assign a;\n "
                                "Select BOOLEAN pattern a(\"x\", _\"x\"_) such that Modifies(2, \"x\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "FALSE" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("BOOLEAN Test 8 - Calls itself") {
        std::string testQuery = "procedure p,p1;\n "
                                "Select BOOLEAN such that Calls(p, p)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "FALSE" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("TUPLE queries with synonyms") {
    SECTION("Tuple Test 1 - 2 synonyms present") {
        std::string testQuery = "procedure p, p1;\n "
                                "Select <p, p1> such that Calls(p, p1)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "First Second", "Second Third" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Tuple Test 2 - 3 synonyms present") {
        std::string testQuery = "procedure p, p1; variable v; stmt s;\n "
                                "Select <p, p1, v> such that Calls(p, p1) and Modifies(14, v)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "First Second y", "Second Third y" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Tuple Test 3 - 3 synonyms present with False result") {
        std::string testQuery = "procedure p, p1; variable v; stmt s;\n "
                                "Select <p, p1, v> such that Calls(p, p1) and Modifies(18, v)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Tuple Test 4 - 3 synonyms present") {
        std::string testQuery = "procedure p, p1; variable v; stmt s;\n "
                                "Select <p, p1, s> such that Calls(p, p1) and Modifies(s, \"i\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "First Second 3", "Second Third 3", "First Second 6", "Second Third 9", "First Second 5", "Second Third 6", "First Second 9", "Second Third 5"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Tuple Test 5") {
        std::string testQuery = "read re; print p1, p2; call c; stmt s;\n "
                                "Select <c, s> such that Uses(c, \"v\") such that Modifies(s, \"x\") such that Uses(s, \"y\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"3 6", "8 6",
                                                  "3 7", "8 7",
                                                  "3 15", "8 15",
                                                  "3 3", "8 3"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Tuple Test 6") {
        std::string testQuery = "read re; print p1, p2; call c; stmt s;\n "
                                "Select <s, s> such that Uses(c, \"v\") such that Modifies(s, \"x\") such that Uses(s, \"y\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"15 15", "3 3", "6 6", "7 7"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("Tuple queries with attributes") {
    SECTION("Tuple Test 1 - 1 attribute present") {
        std::string testQuery = "procedure p, p1; variable v; stmt s;\n "
                                "Select <p.procName, p1, s> such that Calls(p, p1) and Modifies(s, \"i\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"First Second 3", "Second Third 3", "First Second 6", "Second Third 9", "First Second 5", "Second Third 6", "First Second 9", "Second Third 5"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Tuple Test 2 - 3 attributes present") {
        std::string testQuery = "procedure p, p1; variable v; stmt s;\n "
                                "Select <p.procName, p1.procName, s.stmt#> such that Calls(p, p1) and Modifies(s, \"i\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "First Second 3", "Second Third 3", "First Second 6", "Second Third 9", "First Second 5", "Second Third 6", "First Second 9", "Second Third 5"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Tuple Test 3 - 2 attributes present") {
        std::string testQuery = "procedure p, p1; variable v; stmt s; constant c;\n "
                                "Select <c.value, p.procName> such that Calls(p, p1) and Modifies(s, \"i\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"0 First", "0 Second", "5 First", "5 Second", "2 First", "2 Second", "1 First", "1 Second"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Tuple Test 4 - 1 alternative attribute present") {
        std::string testQuery = "procedure p, p1; variable v; stmt s; constant c;\n "
                                "Select <v.varName, p.procName> such that Calls(p, p1) and Modifies(s, \"i\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"x First", "x Second", "y First", "y Second", "i First", "i Second", "z First", "z Second", "v First", "v Second"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Tuple Test 5") {
        std::string testQuery = "procedure p, p1; variable v; stmt s;\n "
                                "Select <v.varName, p.procName> such that Calls(p, p1) and Modifies(s, \"i\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"x First", "x Second", "y First", "y Second", "i First", "i Second", "z First", "z Second", "v First", "v Second"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Tuple Test 6") {
        std::string testQuery = "procedure p, p1; read re; stmt s; call c;\n "
                                "Select <re.varName, c.procName> such that Calls(p, p1) and Modifies(s, \"i\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"x Second", "z Second", "x Third", "z Third"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Tuple Test 7") {
        std::string testQuery = "procedure p, p1; read re; stmt s; call c;\n "
                                "Select <re.varName> such that Calls(p, p1) and Modifies(s, \"i\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"x", "z"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Tuple Test 8") {
        std::string testQuery = "read re; print p1, p2; call c; stmt s;\n "
                                "Select <s.stmt#, re.stmt#, re.varName, p1.varName, c.stmt#> such that Uses(s, \"y\") such that Modifies(re, \"y\") and Modifies(1, \"x\") and Uses(p1, \"v\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"7 2 z v 3", "6 2 z v 3", "15 2 z v 3", "3 2 z v 3",
                                                  "7 2 z v 8", "6 2 z v 8", "15 2 z v 8", "3 2 z v 8"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Tuple Test 9") {
        std::string testQuery = "read re; print p1, p2; call c; stmt s;\n "
                                "Select <c.stmt#, c.procName, s.stmt#> such that Uses(c, \"v\") such that Modifies(s, \"x\") such that Uses(s, \"y\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"8 Third 6", "3 Second 6",
                                                  "8 Third 7", "3 Second 7",
                                                  "8 Third 15", "3 Second 15",
                                                  "8 Third 3", "3 Second 3"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Tuple Test 10") {
        std::string testQuery = "read re; print p1, p2; call c; stmt s;\n "
                                "Select <c.procName, c.procName, s.stmt#> such that Uses(c, \"v\") such that Modifies(s, \"x\") such that Uses(s, \"y\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"Second Second 6", "Second Second 7", "Second Second 15", "Second Second 3",
                                                  "Third Third 6", "Third Third 7", "Third Third 15", "Third Third 3"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Tuple Test 11") {
        std::string testQuery = "read re; print p1, p2; call c; stmt s;\n "
                                "Select <c, c.procName, s.stmt#> such that Uses(c, \"v\") such that Modifies(s, \"x\") such that Uses(s, \"y\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"8 Third 6", "3 Second 6",
                                                  "8 Third 7", "3 Second 7",
                                                  "8 Third 15", "3 Second 15",
                                                  "8 Third 3", "3 Second 3"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Tuple Test 12") {
        std::string testQuery = "read re; print p1, p2; call c; stmt s;\n "
                                "Select <s.stmt#, s.stmt#, s.stmt#> such that Uses(c, \"v\") such that Modifies(s, \"x\") such that Uses(s, \"y\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"6 6 6", "7 7 7", "15 15 15", "3 3 3"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Tuple Test 13") {
        std::string testQuery = "call       c;   stmt s ; print  pn; "
            "Select <s    c\n.    procName,       c.stmt#   ,pnpn        .varName          >   such   that Follows*    (6,   s)";

        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "SemanticError" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }
}


TEST_CASE("Attribute queries - alternate attribute names") {
    SECTION("Attribute Test 1") {
        std::string testQuery = "print p;\n "
                                "Select p.varName";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"v"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Attribute Test 2") {
        std::string testQuery = "print p;\n "
                                "Select p.varName such that Uses(p, \"x\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Attribute Test 3") {
        std::string testQuery = "print p;\n "
                                "Select p.varName such that Uses(p, \"v\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"v"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Attribute Test 4") {
        std::string testQuery = "read re;\n "
                                "Select re.varName such that Uses(re, \"v\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Attribute Test 5") {
        std::string testQuery = "read re;\n "
                                "Select re.varName such that Modifies(re, \"x\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"x"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Attribute Test 6") {
        std::string testQuery = "read re; call c;\n "
                                "Select c.procName such that Follows(2, c)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"Second"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }
}


TEST_CASE("Attribute queries - non alternate attribute names") {
    SECTION("Attribute Test 1") {
        std::string testQuery = "procedure p, p1;\n "
                                "Select p.procName such that Calls(p, p1)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "First", "Second" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Attribute Test 2") {
        std::string testQuery = "stmt s; procedure p,p1;\n "
                                "Select s.stmt# such that Calls(p, p1)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "11", "7", "18", "16", "15", "3", "17", "2", "9", "14", "13", "12", "4", "8", "10", "6", "5", "1" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Attribute Test 3") {
        std::string testQuery = "while w; assign a;\n "
                                "Select w.stmt# such that Modifies(w, \"v\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"6"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Attribute Test 4") {
        std::string testQuery = "variable v; while w;\n "
                                "Select v.varName such that Modifies(w, v)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"x", "i", "z", "v"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Attribute Test 5") {
        std::string testQuery = "constant c;\n "
                                "Select c.value";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"0", "5", "2", "1"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Attribute Test 6") {
        std::string testQuery = "print p;\n "
                                "Select p.stmt#";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"18"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Attribute Test 7") {
        std::string testQuery = "constant value;\n "
                                "Select value.value";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"0", "5", "2", "1"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Attribute Test 8") {
        std::string testQuery = "variable varName; while w;\n "
                                "Select varName.varName such that Modifies(w, varName)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"x", "i", "z", "v"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Attribute Test 9") {
        std::string testQuery = "constant c;\n "
                                "Select c.procName";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"SemanticError"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("With clause queries") {
    SECTION("With clause Test 1") {
        std::string testQuery = "procedure p; call c; while w;\n "
                                "Select p such that Calls (\"Second\", p) and Parent (w, c) with c.procName = p.procName";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"Third"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("With clause Test 2") {
        std::string testQuery = "procedure p, q;\n "
                                "Select p such that Calls (p, q) with q.procName = \"Third\" such that Modifies (p, \"i\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"Second"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("With clause Test 3") {
        std::string testQuery = "procedure p, q;\n "
                                "Select p such that Calls (p, q) with q.procName = \"Third\" and p.procName = \"Second\" such that Modifies (p, \"i\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"Second"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("With clause Test 4") {
        std::string testQuery = "procedure p, q;\n "
                                "Select p such that Calls (p, q) with q.procName = \"Third\" and p.procName = \"First\" such that Modifies (p, \"i\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("With clause Test 5") {
        std::string testQuery = "procedure p, q;\n "
                                "Select p such that Calls (p, q) with \"x\" = \"y\" such that Modifies (p, \"i\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("With clause Test 6") {
        std::string testQuery = "read re; print p1, p2; call c; stmt s;\n "
                                "Select s.stmt# such that Modifies(s, \"x\") such that Uses(s, \"y\") with s.stmt# = s.stmt# and 3 = 4";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("With clause Test 7") {
        std::string testQuery = "procedure p, q;\n "
                                "Select p such that Calls (p, q) with 3=3 such that Modifies (p, \"i\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"First", "Second"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("With clause Test 8") {
        std::string testQuery = "stmt s, s1;\n "
                                "Select s such that Uses(s, \"i\") and Modifies(s1, \"x\") with s.stmt# = s1.stmt#";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"6", "3"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("With clause Test 9") {
        std::string testQuery = "stmt s, s1;\n "
                                "Select s1 such that Uses(s, \"i\") and Modifies(s1, \"x\") with s.stmt# = s1.stmt#";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"6", "3"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("If Pattern queries") {
    SECTION("If Pattern test 1") {
        std::string testQuery = "if ifs;\n "
                                "Select ifs pattern ifs(_, _, _)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"10"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("If Pattern test 2") {
        std::string testQuery = "if ifs; variable v; constant c;\n "
                                "Select <ifs, v, c> pattern ifs(v,_,_)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"10 x 1", "10 x 5", "10 x 2", "10 x 0"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("If Pattern test 3") {
        std::string testQuery = "if ifs; variable v; constant c;\n "
                                "Select ifs pattern ifs(\"x\",_,_)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"10"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("If Pattern test 4") {
        std::string testQuery = "if if; variable v; constant c;\n "
                                "Select if pattern if(\"y\",_,_)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("djfhdjfhd") {
            std::string testQuery = "if ifs; variable v; constant c;\n "
                                "Select <ifs, v, c> pattern ifs(v,_,_)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"10 x 1", "10 x 5", "10 x 2", "10 x 0"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
}

TEST_CASE("While Pattern queries") {
    SECTION("While Pattern test 1") {
        std::string testQuery = "while w;\n "
                                "Select w pattern w(_, _)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"6"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("While Pattern test 2") {
        std::string testQuery = "variable v; while w;\n "
                                "Select <w, v> pattern w(v,_)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"6 i"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("While Pattern test 3") {
        std::string testQuery = "variable v; while w;\n "
                                "Select <w, v> pattern w(\"i\",_)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"6 x", "6 y", "6 i", "6 z", "6 v"};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }

    SECTION("While Pattern test 4") {
        std::string testQuery = "variable v; while w;\n "
                                "Select <w, v> pattern w(\"z\",_)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {};
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        testResults.sort();
        expectedResults.sort();
        REQUIRE(testResults == expectedResults);
    }
}