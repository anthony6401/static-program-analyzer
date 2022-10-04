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
#include "models/Relationship/NextTRelationship.h"
#include "models/Relationship/CallsRelationship.h"
#include "models/Relationship/CallsTRelationship.h"
#include "models/Pattern/Pattern.h"
#include "models/Pattern/AssignPattern.h"
#include "components/qps/QPS.h"
#include <iostream>

// Populating data in PKB
PKB* pkb_m2 = new PKB();
auto qpsClient_m2 = QPSClient(pkb_m2);

// Stmt Entity
static Entity* stmt1 = new ReadEntity("1");
static Entity* stmt2 = new ReadEntity("2");
static Entity* stmt3 = new CallEntity("3");
static Entity* stmt4 = new AssignEntity("4");
static Entity* stmt5 = new AssignEntity("5");
static Entity* stmt6 = new WhileEntity("6");
static Entity* stmt7 = new AssignEntity("7");
static Entity* stmt8 = new CallEntity("8");
static Entity* stmt9 = new AssignEntity("9");
static Entity* stmt10 = new IfEntity("10");
static Entity* stmt11 = new AssignEntity("11");
static Entity* stmt12 = new AssignEntity("12");
static Entity* stmt13 = new AssignEntity("13");
static Entity* stmt14 = new AssignEntity("14");
static Entity* stmt15 = new AssignEntity("15");
static Entity* stmt16 = new AssignEntity("16");
static Entity* stmt17 = new AssignEntity("17");
static Entity* stmt18 = new PrintEntity("18");

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

// Next* Relationship
static Relationship* nextTRelationship1 = new NextTRelationship(stmt1, stmt2);
static Relationship* nextTRelationship2 = new NextTRelationship(stmt1, stmt3);
static Relationship* nextTRelationship3 = new NextTRelationship(stmt2, stmt3);
static Relationship* nextTRelationship4 = new NextTRelationship(stmt4, stmt5);
static Relationship* nextTRelationship5 = new NextTRelationship(stmt4, stmt6);
static Relationship* nextTRelationship6 = new NextTRelationship(stmt4, stmt7);
static Relationship* nextTRelationship7 = new NextTRelationship(stmt4, stmt8);
static Relationship* nextTRelationship8 = new NextTRelationship(stmt4, stmt9);
static Relationship* nextTRelationship9 = new NextTRelationship(stmt4, stmt10);
static Relationship* nextTRelationship10 = new NextTRelationship(stmt4, stmt11);
static Relationship* nextTRelationship11 = new NextTRelationship(stmt4, stmt12);
static Relationship* nextTRelationship12 = new NextTRelationship(stmt4, stmt13);
static Relationship* nextTRelationship13 = new NextTRelationship(stmt4, stmt14);
static Relationship* nextTRelationship14 = new NextTRelationship(stmt4, stmt15);
static Relationship* nextTRelationship15 = new NextTRelationship(stmt5, stmt6);
static Relationship* nextTRelationship16 = new NextTRelationship(stmt5, stmt7);
static Relationship* nextTRelationship17 = new NextTRelationship(stmt5, stmt8);
static Relationship* nextTRelationship18 = new NextTRelationship(stmt5, stmt9);
static Relationship* nextTRelationship19 = new NextTRelationship(stmt5, stmt10);
static Relationship* nextTRelationship20 = new NextTRelationship(stmt5, stmt11);
static Relationship* nextTRelationship21 = new NextTRelationship(stmt5, stmt12);
static Relationship* nextTRelationship22 = new NextTRelationship(stmt5, stmt13);
static Relationship* nextTRelationship23 = new NextTRelationship(stmt5, stmt14);
static Relationship* nextTRelationship24 = new NextTRelationship(stmt5, stmt15);
static Relationship* nextTRelationship25 = new NextTRelationship(stmt6, stmt6);
static Relationship* nextTRelationship26 = new NextTRelationship(stmt6, stmt7);
static Relationship* nextTRelationship27 = new NextTRelationship(stmt6, stmt8);
static Relationship* nextTRelationship28 = new NextTRelationship(stmt6, stmt9);
static Relationship* nextTRelationship29 = new NextTRelationship(stmt6, stmt10);
static Relationship* nextTRelationship30 = new NextTRelationship(stmt6, stmt11);
static Relationship* nextTRelationship31 = new NextTRelationship(stmt6, stmt12);
static Relationship* nextTRelationship32 = new NextTRelationship(stmt6, stmt13);
static Relationship* nextTRelationship33 = new NextTRelationship(stmt6, stmt14);
static Relationship* nextTRelationship34 = new NextTRelationship(stmt6, stmt15);
static Relationship* nextTRelationship35 = new NextTRelationship(stmt7, stmt6);
static Relationship* nextTRelationship36 = new NextTRelationship(stmt7, stmt7);
static Relationship* nextTRelationship37 = new NextTRelationship(stmt7, stmt8);
static Relationship* nextTRelationship38 = new NextTRelationship(stmt7, stmt9);
static Relationship* nextTRelationship39 = new NextTRelationship(stmt7, stmt10);
static Relationship* nextTRelationship40 = new NextTRelationship(stmt7, stmt11);
static Relationship* nextTRelationship41 = new NextTRelationship(stmt7, stmt12);
static Relationship* nextTRelationship42 = new NextTRelationship(stmt7, stmt13);
static Relationship* nextTRelationship43 = new NextTRelationship(stmt7, stmt14);
static Relationship* nextTRelationship44 = new NextTRelationship(stmt7, stmt15);
static Relationship* nextTRelationship45 = new NextTRelationship(stmt8, stmt6);
static Relationship* nextTRelationship46 = new NextTRelationship(stmt8, stmt7);
static Relationship* nextTRelationship47 = new NextTRelationship(stmt8, stmt8);
static Relationship* nextTRelationship48 = new NextTRelationship(stmt8, stmt9);
static Relationship* nextTRelationship49 = new NextTRelationship(stmt8, stmt10);
static Relationship* nextTRelationship50 = new NextTRelationship(stmt8, stmt11);
static Relationship* nextTRelationship51 = new NextTRelationship(stmt8, stmt12);
static Relationship* nextTRelationship52 = new NextTRelationship(stmt8, stmt13);
static Relationship* nextTRelationship53 = new NextTRelationship(stmt8, stmt14);
static Relationship* nextTRelationship54 = new NextTRelationship(stmt8, stmt15);
static Relationship* nextTRelationship55 = new NextTRelationship(stmt9, stmt6);
static Relationship* nextTRelationship56 = new NextTRelationship(stmt9, stmt7);
static Relationship* nextTRelationship57 = new NextTRelationship(stmt9, stmt8);
static Relationship* nextTRelationship58 = new NextTRelationship(stmt9, stmt9);
static Relationship* nextTRelationship59 = new NextTRelationship(stmt9, stmt10);
static Relationship* nextTRelationship60 = new NextTRelationship(stmt9, stmt11);
static Relationship* nextTRelationship61 = new NextTRelationship(stmt9, stmt12);
static Relationship* nextTRelationship62 = new NextTRelationship(stmt9, stmt13);
static Relationship* nextTRelationship63 = new NextTRelationship(stmt9, stmt14);
static Relationship* nextTRelationship64 = new NextTRelationship(stmt9, stmt15);
static Relationship* nextTRelationship65 = new NextTRelationship(stmt10, stmt11);
static Relationship* nextTRelationship66 = new NextTRelationship(stmt10, stmt12);
static Relationship* nextTRelationship67 = new NextTRelationship(stmt10, stmt13);
static Relationship* nextTRelationship68 = new NextTRelationship(stmt10, stmt14);
static Relationship* nextTRelationship69 = new NextTRelationship(stmt10, stmt15);
static Relationship* nextTRelationship70 = new NextTRelationship(stmt11, stmt13);
static Relationship* nextTRelationship71 = new NextTRelationship(stmt11, stmt14);
static Relationship* nextTRelationship72 = new NextTRelationship(stmt11, stmt15);
static Relationship* nextTRelationship73 = new NextTRelationship(stmt12, stmt13);
static Relationship* nextTRelationship74 = new NextTRelationship(stmt12, stmt14);
static Relationship* nextTRelationship75 = new NextTRelationship(stmt12, stmt15);
static Relationship* nextTRelationship76 = new NextTRelationship(stmt13, stmt14);
static Relationship* nextTRelationship77 = new NextTRelationship(stmt13, stmt15);
static Relationship* nextTRelationship78 = new NextTRelationship(stmt14, stmt15);
static Relationship* nextTRelationship79 = new NextTRelationship(stmt16, stmt17);
static Relationship* nextTRelationship80 = new NextTRelationship(stmt16, stmt18);
static Relationship* nextTRelationship81 = new NextTRelationship(stmt17, stmt18);

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

    pkb_m2->storeRelationship(nextTRelationship1);
    pkb_m2->storeRelationship(nextTRelationship2);
    pkb_m2->storeRelationship(nextTRelationship3);
    pkb_m2->storeRelationship(nextTRelationship4);
    pkb_m2->storeRelationship(nextTRelationship5);
    pkb_m2->storeRelationship(nextTRelationship6);
    pkb_m2->storeRelationship(nextTRelationship7);
    pkb_m2->storeRelationship(nextTRelationship8);
    pkb_m2->storeRelationship(nextTRelationship9);
    pkb_m2->storeRelationship(nextTRelationship10);
    pkb_m2->storeRelationship(nextTRelationship11);
    pkb_m2->storeRelationship(nextTRelationship12);
    pkb_m2->storeRelationship(nextTRelationship13);
    pkb_m2->storeRelationship(nextTRelationship14);
    pkb_m2->storeRelationship(nextTRelationship15);
    pkb_m2->storeRelationship(nextTRelationship16);
    pkb_m2->storeRelationship(nextTRelationship17);
    pkb_m2->storeRelationship(nextTRelationship18);
    pkb_m2->storeRelationship(nextTRelationship19);
    pkb_m2->storeRelationship(nextTRelationship20);
    pkb_m2->storeRelationship(nextTRelationship21);
    pkb_m2->storeRelationship(nextTRelationship22);
    pkb_m2->storeRelationship(nextTRelationship23);
    pkb_m2->storeRelationship(nextTRelationship24);
    pkb_m2->storeRelationship(nextTRelationship25);
    pkb_m2->storeRelationship(nextTRelationship26);
    pkb_m2->storeRelationship(nextTRelationship27);
    pkb_m2->storeRelationship(nextTRelationship28);
    pkb_m2->storeRelationship(nextTRelationship29);
    pkb_m2->storeRelationship(nextTRelationship30);
    pkb_m2->storeRelationship(nextTRelationship31);
    pkb_m2->storeRelationship(nextTRelationship32);
    pkb_m2->storeRelationship(nextTRelationship33);
    pkb_m2->storeRelationship(nextTRelationship34);
    pkb_m2->storeRelationship(nextTRelationship35);
    pkb_m2->storeRelationship(nextTRelationship36);
    pkb_m2->storeRelationship(nextTRelationship37);
    pkb_m2->storeRelationship(nextTRelationship38);
    pkb_m2->storeRelationship(nextTRelationship39);
    pkb_m2->storeRelationship(nextTRelationship40);
    pkb_m2->storeRelationship(nextTRelationship41);
    pkb_m2->storeRelationship(nextTRelationship42);
    pkb_m2->storeRelationship(nextTRelationship43);
    pkb_m2->storeRelationship(nextTRelationship44);
    pkb_m2->storeRelationship(nextTRelationship45);
    pkb_m2->storeRelationship(nextTRelationship46);
    pkb_m2->storeRelationship(nextTRelationship47);
    pkb_m2->storeRelationship(nextTRelationship48);
    pkb_m2->storeRelationship(nextTRelationship49);
    pkb_m2->storeRelationship(nextTRelationship50);
    pkb_m2->storeRelationship(nextTRelationship51);
    pkb_m2->storeRelationship(nextTRelationship52);
    pkb_m2->storeRelationship(nextTRelationship53);
    pkb_m2->storeRelationship(nextTRelationship54);
    pkb_m2->storeRelationship(nextTRelationship55);
    pkb_m2->storeRelationship(nextTRelationship56);
    pkb_m2->storeRelationship(nextTRelationship57);
    pkb_m2->storeRelationship(nextTRelationship58);
    pkb_m2->storeRelationship(nextTRelationship59);
    pkb_m2->storeRelationship(nextTRelationship60);
    pkb_m2->storeRelationship(nextTRelationship61);
    pkb_m2->storeRelationship(nextTRelationship62);
    pkb_m2->storeRelationship(nextTRelationship63);
    pkb_m2->storeRelationship(nextTRelationship64);
    pkb_m2->storeRelationship(nextTRelationship65);
    pkb_m2->storeRelationship(nextTRelationship66);
    pkb_m2->storeRelationship(nextTRelationship67);
    pkb_m2->storeRelationship(nextTRelationship68);
    pkb_m2->storeRelationship(nextTRelationship69);
    pkb_m2->storeRelationship(nextTRelationship70);
    pkb_m2->storeRelationship(nextTRelationship71);
    pkb_m2->storeRelationship(nextTRelationship72);
    pkb_m2->storeRelationship(nextTRelationship73);
    pkb_m2->storeRelationship(nextTRelationship74);
    pkb_m2->storeRelationship(nextTRelationship75);
    pkb_m2->storeRelationship(nextTRelationship76);
    pkb_m2->storeRelationship(nextTRelationship77);
    pkb_m2->storeRelationship(nextTRelationship78);
    pkb_m2->storeRelationship(nextTRelationship79);
    pkb_m2->storeRelationship(nextTRelationship80);
    pkb_m2->storeRelationship(nextTRelationship81);

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
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls Test 2") {
        std::string testQuery = "procedure p; \n "
                                "Select p such that Calls(p, _)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"Second", "First"};
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
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls* Test 2") {
        std::string testQuery = "procedure p, p1; \n "
                                "Select p1 such that Calls*(\"First\", \"Third\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = {"Third", "Second", "First"};
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

    SECTION("Calls* Test 4") {
        std::string testQuery = "procedure p, p1; \n "
            "Select p1 such that Calls*(p, p1)";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "Second", "Third" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls* Test 5") {
        std::string testQuery = "procedure p, p1; \n "
            "Select p1 such that Calls*(\"First\", \"Second\")";
        std::list<std::string> testResults;
        std::list<std::string> expectedResults = { "Third", "Second", "First" };
        QPS::processQueryResult(testQuery, testResults, qpsClient_m2);
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