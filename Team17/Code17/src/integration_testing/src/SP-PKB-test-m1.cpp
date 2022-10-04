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
PKB* pkbSP = new PKB();
auto spClient = new SPClient(pkbSP);

TEST_CASE("test SP PKB integration") {
    Extractor extractor = Extractor(spClient);
    SimpleParser simpleParser = SimpleParser(&extractor);
    simpleParser.parseCode("    procedure computeCentroid {\
		      count = 0;\
	      cenX = 0;\
	      cenY = 0;\
	      while ((x != 0) && (y != 0)) {\
		          count = count + 1;\
		          cenX = cenX + x;\
		          cenY = cenY + y;\
	}\
	      if (count == 0) then{\
	          flag = 1;\
	}\
	else {\
		          cenX = cenX / count;\
		          cenY = cenY / count;\
	}\
	      normSq = cenX * cenX + cenY * cenY;\
    }");
}

// pkbSP APIs queries
TEST_CASE("Select all queries for SP") {
    SECTION("Select if statements") {
        std::unordered_set<std::string> testResults = pkbSP->getAllEntity(DesignEntity::IF);
        std::unordered_set<std::string> expectedResults = { "8" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Select assign statements") {
        std::unordered_set<std::string> testResults = pkbSP->getAllEntity(DesignEntity::ASSIGN);
        std::unordered_set<std::string> expectedResults = { "1", "2", "3", "5", "6", "7", "9", "10", "11", "12" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Select read statements") {
        std::unordered_set<std::string> testResults = pkbSP->getAllEntity(DesignEntity::READ);
        std::unordered_set<std::string> expectedResults = {};
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Select print statements") {
        std::unordered_set<std::string> testResults = pkbSP->getAllEntity(DesignEntity::PRINT);
        std::unordered_set<std::string> expectedResults = {};
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Select procedures") {
        std::unordered_set<std::string> testResults = pkbSP->getAllEntity(DesignEntity::PROCEDURE);
        std::unordered_set<std::string> expectedResults = { "computeCentroid" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Select while statements") {
        std::unordered_set<std::string> testResults = pkbSP->getAllEntity(DesignEntity::WHILE);
        std::unordered_set<std::string> expectedResults = { "4" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Select variables") {
        std::unordered_set<std::string> testResults = pkbSP->getAllEntity(DesignEntity::VARIABLE);
        std::unordered_set<std::string> expectedResults = { "count", "cenX", "cenY", "x", "y", "flag", "normSq" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Select constants") {
        std::unordered_set<std::string> testResults = pkbSP->getAllEntity(DesignEntity::CONSTANT);
        std::unordered_set<std::string> expectedResults = { "0", "1" };
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("Relationships and patterns for SP") {
    SECTION("Modifies with no synonym") {
        // Modifies(2, cenX)
        bool testResults = pkbSP->getRelationship(RelationshipType::MODIFIES, TokenObject(TokenType::INTEGER, "2"), TokenObject(TokenType::NAME_WITH_QUOTATION, "cenX"));
        REQUIRE(testResults);
    }

    SECTION("Modifies with synonym first argument") {
        // Modifies(a, "count")
        std::unordered_set<std::string> testResults = pkbSP->getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::ASSIGN, TokenObject(TokenType::NAME_WITH_QUOTATION, "count"));
        std::unordered_set<std::string> expectedResults = { "1", "5" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Modifies with synonym second argument") {
        // Modifies(1, v)
        std::unordered_set<std::string> testResults = pkbSP->getRelationshipByFirst(RelationshipType::MODIFIES, TokenObject(TokenType::INTEGER, "1"), DesignEntity::VARIABLE);
        std::unordered_set<std::string> expectedResults = { "count" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Modifies with 2 synonyms") {
        // Modifies(a, v)
        std::unordered_map<std::string, std::unordered_set<std::string>> testResults = pkbSP->getAllRelationship(RelationshipType::MODIFIES, DesignEntity::ASSIGN, DesignEntity::VARIABLE);
        std::unordered_map<std::string, std::unordered_set<std::string>> expectedResults = { {"1", std::unordered_set<std::string>({"count"})},
                                                                                                {"2", std::unordered_set<std::string>({"cenX"})},
                                                                                                {"3", std::unordered_set<std::string>({"cenY"})},
                                                                                                {"5", std::unordered_set<std::string>({"count"})},
                                                                                                {"6", std::unordered_set<std::string>({"cenX"})},
                                                                                                {"7", std::unordered_set<std::string>({"cenY"})},
                                                                                                {"9", std::unordered_set<std::string>({"flag"})},
                                                                                                {"10", std::unordered_set<std::string>({"cenX"})},
                                                                                                {"11", std::unordered_set<std::string>({"cenY"})},
                                                                                                {"12", std::unordered_set<std::string>({"normSq"})} };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Uses with no synonym") {
        // Uses(4, "x")
        bool testResults = pkbSP->getRelationship(RelationshipType::USES, TokenObject(TokenType::INTEGER, "4"), TokenObject(TokenType::NAME_WITH_QUOTATION, "x"));
        REQUIRE(testResults);
    }

    SECTION("Uses with synonym first argument") {
        // Uses(if, "count")
        std::unordered_set<std::string> testResults = pkbSP->getRelationshipBySecond(RelationshipType::USES, DesignEntity::IF, TokenObject(TokenType::NAME_WITH_QUOTATION, "count"));
        std::unordered_set<std::string> expectedResults = { "8" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Uses with synonym second argument") {
        // Uses(12, v)
        std::unordered_set<std::string> testResults = pkbSP->getRelationshipByFirst(RelationshipType::USES, TokenObject(TokenType::INTEGER, "12"), DesignEntity::VARIABLE);
        std::unordered_set<std::string> expectedResults = { "cenX", "cenY" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Uses with 2 synonyms") {
        // Uses(a, v)
        std::unordered_map<std::string, std::unordered_set<std::string>> testResults = pkbSP->getAllRelationship(RelationshipType::USES, DesignEntity::ASSIGN, DesignEntity::VARIABLE);
        std::unordered_map<std::string, std::unordered_set<std::string>> expectedResults = { {"5", std::unordered_set<std::string>({"count"})},
                                                                                                {"6", std::unordered_set<std::string>({"cenX", "x"})},
                                                                                                {"7", std::unordered_set<std::string>({"cenY", "y"})},
                                                                                                {"10", std::unordered_set<std::string>({"count", "cenX"})},
                                                                                                {"11", std::unordered_set<std::string>({"count", "cenY"})},
                                                                                                {"12", std::unordered_set<std::string>({"cenX", "cenY"})} };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Follows with no synonym") {
        // Follows(1, 2)
        bool testResults = pkbSP->getRelationship(RelationshipType::FOLLOWS, TokenObject(TokenType::INTEGER, "1"), TokenObject(TokenType::INTEGER, "2"));
        REQUIRE(testResults);
    }

    SECTION("Follows with synonym first argument") {
        // Follows(w, 8)
        std::unordered_set<std::string> testResults = pkbSP->getRelationshipBySecond(RelationshipType::FOLLOWS, DesignEntity::WHILE, TokenObject(TokenType::INTEGER, "8"));
        std::unordered_set<std::string> expectedResults = { "4" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Follows with synonym second argument") {
        // Follows(1, s)
        std::unordered_set<std::string> testResults = pkbSP->getRelationshipByFirst(RelationshipType::FOLLOWS, TokenObject(TokenType::INTEGER, "1"), DesignEntity::STMT);
        std::unordered_set<std::string> expectedResults = { "2" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Follows with 2 synonyms") {
        // Follows(a, s)
        std::unordered_map<std::string, std::unordered_set<std::string>> testResults = pkbSP->getAllRelationship(RelationshipType::FOLLOWS, DesignEntity::ASSIGN, DesignEntity::STMT);
        std::unordered_map<std::string, std::unordered_set<std::string>> expectedResults = { {"1", std::unordered_set<std::string>({"2"})},
                                                                                                {"2", std::unordered_set<std::string>({"3"})},
                                                                                                {"3", std::unordered_set<std::string>({"4"})},
                                                                                                {"5", std::unordered_set<std::string>({"6"})},
                                                                                                {"6", std::unordered_set<std::string>({"7"})},
                                                                                                {"10", std::unordered_set<std::string>({"11"})} };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Follows* with no synonym") {
        // Follows*(1, 3)
        bool testResults = pkbSP->getRelationship(RelationshipType::FOLLOWS_T, TokenObject(TokenType::INTEGER, "1"), TokenObject(TokenType::INTEGER, "3"));
        REQUIRE(testResults);
    }

    SECTION("Follows* with synonym first argument") {
        // Follows*(a, 7)
        std::unordered_set<std::string> testResults = pkbSP->getRelationshipBySecond(RelationshipType::FOLLOWS_T, DesignEntity::ASSIGN, TokenObject(TokenType::INTEGER, "7"));
        std::unordered_set<std::string> expectedResults = { "5", "6" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Follows* with synonym second argument") {
        // Follows*(1, s)
        std::unordered_set<std::string> testResults = pkbSP->getRelationshipByFirst(RelationshipType::FOLLOWS_T, TokenObject(TokenType::INTEGER, "1"), DesignEntity::STMT);
        std::unordered_set<std::string> expectedResults = { "2", "3", "4", "8", "12" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Follows* with 2 synonyms") {
        // Follows*(a, s)
        std::unordered_map<std::string, std::unordered_set<std::string>> testResults = pkbSP->getAllRelationship(RelationshipType::FOLLOWS_T, DesignEntity::ASSIGN, DesignEntity::STMT);
        std::unordered_map<std::string, std::unordered_set<std::string>> expectedResults = { {"1", std::unordered_set<std::string>({"2", "3", "4", "8", "12"})},
                                                                                                {"2", std::unordered_set<std::string>({"3", "4", "8", "12"})},
                                                                                                {"3", std::unordered_set<std::string>({"4", "8", "12"})},
                                                                                                {"5", std::unordered_set<std::string>({"6", "7"})},
                                                                                                {"6", std::unordered_set<std::string>({"7"})},
                                                                                                {"10", std::unordered_set<std::string>({"11"})} };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Parent with no synonym") {
        // Parent(4, 5)
        bool testResults = pkbSP->getRelationship(RelationshipType::PARENT, TokenObject(TokenType::INTEGER, "4"), TokenObject(TokenType::INTEGER, "5"));
        REQUIRE(testResults);
    }

    SECTION("Parent with synonym first argument") {
        // Parent(w, 6)
        std::unordered_set<std::string> testResults = pkbSP->getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::WHILE, TokenObject(TokenType::INTEGER, "6"));
        std::unordered_set<std::string> expectedResults = { "4" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Parent with synonym second argument") {
        // Parent(8, s)
        std::unordered_set<std::string> testResults = pkbSP->getRelationshipByFirst(RelationshipType::PARENT, TokenObject(TokenType::INTEGER, "8"), DesignEntity::STMT);
        std::unordered_set<std::string> expectedResults = { "9", "10", "11" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Parent with 2 synonyms") {
        // Parent(if, s)
        std::unordered_map<std::string, std::unordered_set<std::string>> testResults = pkbSP->getAllRelationship(RelationshipType::PARENT, DesignEntity::IF, DesignEntity::STMT);
        std::unordered_map<std::string, std::unordered_set<std::string>> expectedResults = { {"8", std::unordered_set<std::string>({"9", "10", "11"})} };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Parent* with no synonym") {
        // Parent*(4, 5)
        bool testResults = pkbSP->getRelationship(RelationshipType::PARENT_T, TokenObject(TokenType::INTEGER, "4"), TokenObject(TokenType::INTEGER, "5"));
        REQUIRE(testResults);
    }

    SECTION("Parent* with synonym first argument") {
        // Parent*(w, 6)
        std::unordered_set<std::string> testResults = pkbSP->getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::WHILE, TokenObject(TokenType::INTEGER, "6"));
        std::unordered_set<std::string> expectedResults = { "4" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Parent* with synonym second argument") {
        // Parent*(8, s)
        std::unordered_set<std::string> testResults = pkbSP->getRelationshipByFirst(RelationshipType::PARENT_T, TokenObject(TokenType::INTEGER, "8"), DesignEntity::STMT);
        std::unordered_set<std::string> expectedResults = { "9", "10", "11" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Parent with 2 synonyms") {
        // Parent*(w, s)
        std::unordered_map<std::string, std::unordered_set<std::string>> testResults = pkbSP->getAllRelationship(RelationshipType::PARENT_T, DesignEntity::WHILE, DesignEntity::STMT);
        std::unordered_map<std::string, std::unordered_set<std::string>> expectedResults = { {"4", std::unordered_set<std::string>({"5", "6", "7"})} };
        REQUIRE(testResults == expectedResults);
    }


    SECTION("Single synonym Clause - Pattern") {
        // a("count, "0")
        std::unordered_set<std::string> testResults = pkbSP->getPattern(DesignEntity::ASSIGN, TokenObject(TokenType::NAME_WITH_QUOTATION, "count"), TokenObject(TokenType::EXPRESSION, "0"));
        std::unordered_set<std::string> expectedResults = { "1" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Multi Clause - One clause related to Select") {
        // a(v, "1")
        std::vector<std::pair<std::string, std::string>> testResults = pkbSP->getPatternPair(DesignEntity::ASSIGN, TokenObject(TokenType::EXPRESSION, "1"));
        std::vector<std::pair<std::string, std::string>> expectedResults = { {"9", "flag" } };
        REQUIRE(testResults == expectedResults);
    }
}
