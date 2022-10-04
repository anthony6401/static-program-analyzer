#include "components/sp/parser/SimpleParser.h"
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
#include "components/pkb/pkb.h"
#include "components/pkb/clients/SPClient.h"

#include <unordered_map>
#include <iostream>

#include <catch.hpp>

// Change the name into pkbSP to avoid clash with QPS-PKB-test
PKB* pkbSP_m2 = new PKB();
auto spClient_m2 = new SPClient(pkbSP_m2);

TEST_CASE("test SP PKB integration m2") {
    // Populate PKB with SP
}

// pkbSP APIs queries
TEST_CASE("Select all queries for SP m2") {
    // Uncomment this when SP has populate PKB
    //SECTION("Select call statements") {
    //    std::list<std::string> testResults = pkbSP_m2->getAllEntity(DesignEntity::CALL);
    //    std::list<std::string> expectedResults = { "Third", "Second", "First" };
    //    REQUIRE(testResults == expectedResults);
    //}
}
