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
// Uncomment all test cases when SP has populate PKB
TEST_CASE("Select all queries for SP m2") {
    //SECTION("Select call statements") {
    //    std::unordered_set<std::string> testResults = pkbSP_m2->getAllEntity(DesignEntity::CALL);
    //    std::unordered_set<std::string> expectedResults = { "Third", "Second", "First" };
    //    REQUIRE(testResults == expectedResults);
    //}
}

TEST_CASE("Calls queries SP") {
    //SECTION("Calls with no synonym") {
    //    // Calls("First", "Second")
    //    bool testResults = pkbSP_m2->getRelationship(RelationshipType::CALLS, TokenObject(TokenType::NAME_WITH_QUOTATION, "First"), TokenObject(TokenType::NAME_WITH_QUOTATION, "Second"));
    //    REQUIRE(testResults);
    //}

    //SECTION("Calls with synonym first argument") {
    //    // Calls(p, "Third")
    //    std::unordered_set<std::string> testResults = pkbSP_m2->getRelationshipBySecond(RelationshipType::CALLS, DesignEntity::PROCEDURE, TokenObject(TokenType::NAME_WITH_QUOTATION, "Third"));
    //    std::unordered_set<std::string> expectedResults = { "Second" };
    //    REQUIRE(testResults == expectedResults);
    //}

    //SECTION("Calls with synonym second argument") {
    //    // Calls("First", p)
    //    std::unordered_set<std::string> testResults = pkbSP_m2->getRelationshipByFirst(RelationshipType::CALLS, TokenObject(TokenType::NAME_WITH_QUOTATION, "First"), DesignEntity::PROCEDURE);
    //    std::unordered_set<std::string> expectedResults = { "Second" };
    //    REQUIRE(testResults == expectedResults);
    //}

    //SECTION("Calls with 2 synonyms") {
    //    // Calls(p1, p2)
    //    std::unordered_map<std::string, std::unordered_set<std::string>> testResults = pkbSP_m2->getAllRelationship(RelationshipType::CALLS, DesignEntity::PROCEDURE, DesignEntity::PROCEDURE);
    //    std::unordered_map<std::string, std::unordered_set<std::string>> expectedResults = { {"First", std::unordered_set<std::string>({"Second"})},
    //                                                                                            {"Second", std::unordered_set<std::string>({"Third"})} };
    //    REQUIRE(testResults == expectedResults);
    //}
}

TEST_CASE("Calls* queries SP") {
    //SECTION("Calls* with no synonym") {
    //    // Calls*("First", "Second")
    //    bool testResults = pkbSP_m2->getRelationship(RelationshipType::CALLS_T, TokenObject(TokenType::NAME_WITH_QUOTATION, "First"), TokenObject(TokenType::NAME_WITH_QUOTATION, "Second"));
    //    REQUIRE(testResults);
    //}

    //SECTION("Calls* with synonym first argument") {
    //    // Calls*(p, "Third")
    //    std::unordered_set<std::string> testResults = pkbSP_m2->getRelationshipBySecond(RelationshipType::CALLS_T, DesignEntity::PROCEDURE, TokenObject(TokenType::NAME_WITH_QUOTATION, "Third"));
    //    std::unordered_set<std::string> expectedResults = { "First", "Second" };
    //    REQUIRE(testResults == expectedResults);
    //}

    //SECTION("Calls* with synonym second argument") {
    //    // Calls*("First", p)
    //    std::unordered_set<std::string> testResults = pkbSP_m2->getRelationshipByFirst(RelationshipType::CALLS_T, TokenObject(TokenType::NAME_WITH_QUOTATION, "First"), DesignEntity::PROCEDURE);
    //    std::unordered_set<std::string> expectedResults = { "Second", "Third" };
    //    REQUIRE(testResults == expectedResults);
    //}

    //SECTION("Calls* with 2 synonyms") {
    //    // Calls*(p1, p2)
    //    std::unordered_map<std::string, std::unordered_set<std::string>> testResults = pkbSP_m2->getAllRelationship(RelationshipType::CALLS_T, DesignEntity::PROCEDURE, DesignEntity::PROCEDURE);
    //    std::unordered_map<std::string, std::unordered_set<std::string>> expectedResults = { {"First", std::unordered_set<std::string>({"Second", "Third" })},
    //                                                                                            {"Second", std::unordered_set<std::string>({"Third"})} };
    //    REQUIRE(testResults == expectedResults);
    //}
}
