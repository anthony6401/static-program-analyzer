#include "components/sp/parser/SimpleParser.h"
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
    Extractor extractor_m2 = Extractor(spClient_m2);
    SimpleParser simpleParser_m2 = SimpleParser(&extractor_m2);
    simpleParser_m2.parseCode("procedure First {\
                                read x;\
                                read z;\
                                call Second; }\
                            \
                            procedure Second {\
                                x = 0;\
                                i = 5;\
                                while (i != 0) {\
                                    x = x + 2 * y;\
                                    call Third;\
                                    i = i - 1; }\
                                if (x == 1) then {\
                                    x = x + 1; }\
                                else {\
                                    z = 1; }\
                                z = z + x + i;\
                                y = z + 2;\
                                x = x * y + z; }\
                            \
                            procedure Third {\
                                z = 5;\
                                v = z;\
                                print v; }");
}

// pkbSP APIs queries
TEST_CASE("Select all queries for SP m2") {
    SECTION("Select call statements") {
        std::unordered_set<std::string> testResults = pkbSP_m2->getAllEntity(DesignEntity::CALL);
        std::unordered_set<std::string> expectedResults = { "3", "8" };
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("Calls queries SP") {
    SECTION("Calls with no synonym") {
        // Calls("First", "Second")
        bool testResults = pkbSP_m2->getRelationship(RelationshipType::CALLS, TokenObject(TokenType::NAME_WITH_QUOTATION, "First"), TokenObject(TokenType::NAME_WITH_QUOTATION, "Second"));
        REQUIRE(testResults);
    }

    SECTION("Calls with synonym first argument") {
        // Calls(p, "Third")
        std::unordered_set<std::string> testResults = pkbSP_m2->getRelationshipBySecond(RelationshipType::CALLS, DesignEntity::PROCEDURE, TokenObject(TokenType::NAME_WITH_QUOTATION, "Third"));
        std::unordered_set<std::string> expectedResults = { "Second" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls with synonym second argument") {
        // Calls("First", p)
        std::unordered_set<std::string> testResults = pkbSP_m2->getRelationshipByFirst(RelationshipType::CALLS, TokenObject(TokenType::NAME_WITH_QUOTATION, "First"), DesignEntity::PROCEDURE);
        std::unordered_set<std::string> expectedResults = { "Second" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls with 2 synonyms") {
        // Calls(p1, p2)
        std::unordered_map<std::string, std::unordered_set<std::string>> testResults = pkbSP_m2->getAllRelationship(RelationshipType::CALLS, DesignEntity::PROCEDURE, DesignEntity::PROCEDURE);
        std::unordered_map<std::string, std::unordered_set<std::string>> expectedResults = { {"First", std::unordered_set<std::string>({"Second"})},
                                                                                                {"Second", std::unordered_set<std::string>({"Third"})} };
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("Calls* queries SP") {
    SECTION("Calls* with no synonym") {
        // Calls*("First", "Second")
        bool testResults = pkbSP_m2->getRelationship(RelationshipType::CALLS_T, TokenObject(TokenType::NAME_WITH_QUOTATION, "First"), TokenObject(TokenType::NAME_WITH_QUOTATION, "Second"));
        REQUIRE(testResults);
    }

    SECTION("Calls* with synonym first argument") {
        // Calls*(p, "Third")
        std::unordered_set<std::string> testResults = pkbSP_m2->getRelationshipBySecond(RelationshipType::CALLS_T, DesignEntity::PROCEDURE, TokenObject(TokenType::NAME_WITH_QUOTATION, "Third"));
        std::unordered_set<std::string> expectedResults = { "First", "Second" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls* with synonym second argument") {
        // Calls*("First", p)
        std::unordered_set<std::string> testResults = pkbSP_m2->getRelationshipByFirst(RelationshipType::CALLS_T, TokenObject(TokenType::NAME_WITH_QUOTATION, "First"), DesignEntity::PROCEDURE);
        std::unordered_set<std::string> expectedResults = { "Second", "Third" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Calls* with 2 synonyms") {
        // Calls*(p1, p2)
        std::unordered_map<std::string, std::unordered_set<std::string>> testResults = pkbSP_m2->getAllRelationship(RelationshipType::CALLS_T, DesignEntity::PROCEDURE, DesignEntity::PROCEDURE);
        std::unordered_map<std::string, std::unordered_set<std::string>> expectedResults = { {"First", std::unordered_set<std::string>({"Second", "Third" })},
                                                                                                {"Second", std::unordered_set<std::string>({"Third"})} };
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("Next queries SP") {
    SECTION("Next with no synonym") {
        // Next(1, 2)
        bool testResults = pkbSP_m2->getRelationship(RelationshipType::NEXT, TokenObject(TokenType::INTEGER, "1"), TokenObject(TokenType::INTEGER, "2"));
        REQUIRE(testResults);
    }

    SECTION("Next with synonym first argument") {
        // Next(a, 13)
        std::unordered_set<std::string> testResults = pkbSP_m2->getRelationshipBySecond(RelationshipType::NEXT, DesignEntity::ASSIGN, TokenObject(TokenType::INTEGER, "13"));
        std::unordered_set<std::string> expectedResults = { "11", "12" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Next with synonym second argument") {
        // Next(17, pr)
        std::unordered_set<std::string> testResults = pkbSP_m2->getRelationshipByFirst(RelationshipType::NEXT, TokenObject(TokenType::INTEGER, "17"), DesignEntity::PRINT);
        std::unordered_set<std::string> expectedResults = { "18" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Next with 2 synonyms") {
        // Next(a, w)
        std::unordered_map<std::string, std::unordered_set<std::string>> testResults = pkbSP_m2->getAllRelationship(RelationshipType::NEXT, DesignEntity::ASSIGN, DesignEntity::WHILE);
        std::unordered_map<std::string, std::unordered_set<std::string>> expectedResults = {{ "5", std::unordered_set<std::string>({ "6" }) },
                                                                                            { "9", std::unordered_set<std::string>({ "6" }) } };
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("Next* queries SP") {
    SECTION("Next* with no synonym") {
        // Next*(4, 15)
        bool testResults = pkbSP_m2->getRelationship(RelationshipType::NEXT_T, TokenObject(TokenType::INTEGER, "4"), TokenObject(TokenType::INTEGER, "15"));
        REQUIRE(testResults);
    }

    SECTION("Next* with synonym first argument") {
        // Next*(s, 6)
        std::unordered_set<std::string> testResults = pkbSP_m2->getRelationshipBySecond(RelationshipType::NEXT_T, DesignEntity::STMT, TokenObject(TokenType::INTEGER, "6"));
        std::unordered_set<std::string> expectedResults = { "4", "5", "6", "7", "8", "9" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Next* with synonym second argument") {
        // Next*(4, a)
        std::unordered_set<std::string> testResults = pkbSP_m2->getRelationshipByFirst(RelationshipType::NEXT_T, TokenObject(TokenType::INTEGER, "4"), DesignEntity::ASSIGN);
        std::unordered_set<std::string> expectedResults = { "5", "7", "9", "11", "12", "13", "14", "15" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Next* with 2 synonyms") {
        // Next*(s1, s2)
        std::unordered_map<std::string, std::unordered_set<std::string>> testResults = pkbSP_m2->getAllRelationship(RelationshipType::NEXT_T, DesignEntity::STMT, DesignEntity::STMT);
        std::unordered_map<std::string, std::unordered_set<std::string>> expectedResults = {{ "1", std::unordered_set<std::string>({ "2", "3"}) },
                                                                                { "2", std::unordered_set<std::string>({ "3" }) },
                                                                                { "4", std::unordered_set<std::string>({ "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15" }) },
                                                                                { "5", std::unordered_set<std::string>({ "6", "7", "8", "9", "10", "11", "12", "13", "14", "15" }) },
                                                                                { "6", std::unordered_set<std::string>({ "6", "7", "8", "9", "10", "11", "12", "13", "14", "15" }) },
                                                                                { "7", std::unordered_set<std::string>({ "6", "7", "8", "9", "10", "11", "12", "13", "14", "15" }) },
                                                                                { "8", std::unordered_set<std::string>({ "6", "7", "8", "9", "10", "11", "12", "13", "14", "15" }) },
                                                                                { "9", std::unordered_set<std::string>({ "6", "7", "8", "9", "10", "11", "12", "13", "14", "15" }) },
                                                                                { "10", std::unordered_set<std::string>({ "11", "12", "13", "14", "15" }) },
                                                                                { "11", std::unordered_set<std::string>({ "13", "14", "15" }) },
                                                                                { "12", std::unordered_set<std::string>({ "13", "14", "15" }) },
                                                                                { "13", std::unordered_set<std::string>({ "14", "15" }) },
                                                                                { "14", std::unordered_set<std::string>({ "15" }) },
                                                                                { "16", std::unordered_set<std::string>({ "17", "18"}) },
                                                                                { "17", std::unordered_set<std::string>({ "18" }) }};
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("Pattern queries SP") {
    SECTION("Pattern with first argument as name in quotes and second argument as expression with operators") {
        // a("x", "x+1")
        std::unordered_set<std::string> testResults = pkbSP_m2->getPattern(DesignEntity::ASSIGN, TokenObject(TokenType::NAME_WITH_QUOTATION, "x"), TokenObject(TokenType::EXPRESSION, "x+1"));
        std::unordered_set<std::string> expectedResults = {"11"};
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Pattern with first argument as name in quotes and second argument as subexpression with operators") {
        // a("x", _"x*y"_)
        std::unordered_set<std::string> testResults = pkbSP_m2->getPattern(DesignEntity::ASSIGN, TokenObject(TokenType::NAME_WITH_QUOTATION, "x"), TokenObject(TokenType::SUBEXPRESSION, "x*y"));
        std::unordered_set<std::string> expectedResults = { "15" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Pattern with first argument as synonym and second argument as expression with operators") {
        // a(v, "x+1")
        std::vector<std::pair<std::string, std::string>> testResults = pkbSP_m2->getPatternPair(DesignEntity::ASSIGN, TokenObject(TokenType::EXPRESSION, "x+1"));
        std::vector<std::pair<std::string, std::string>> expectedResults = { {"11", "x"}};
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Pattern with first argument as synonym and second argument as subexpression with operators") {
        // a(v, _"x*y"_)
        std::vector<std::pair<std::string, std::string>> testResults = pkbSP_m2->getPatternPair(DesignEntity::ASSIGN, TokenObject(TokenType::SUBEXPRESSION, "x*y"));
        std::vector<std::pair<std::string, std::string>> expectedResults = { {"15", "x"}};
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Pattern with synonym and exact expression") {
        // a(_, "x+1")
        std::unordered_set<std::string> testResults = pkbSP_m2->getPatternWildcard(DesignEntity::ASSIGN, TokenObject(TokenType::EXPRESSION, "x+1"));
        std::unordered_set<std::string> expectedResults = { "11" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Pattern with synonym and exact expression") {
        // a(_, _"x*y"_)
        std::unordered_set<std::string> testResults = pkbSP_m2->getPatternWildcard(DesignEntity::ASSIGN, TokenObject(TokenType::SUBEXPRESSION, "x*y"));
        std::unordered_set<std::string> expectedResults = { "15" };
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("Statement to value name mapping queries SP") {
    SECTION("Test for Print") {
        std::string stmtNumber = "18";
        std::string testResults = pkbSP_m2->getStatementMapping(stmtNumber, DesignEntity::PRINT);
        std::string expectedResults = "v";
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Test for Read 1") {
        std::string stmtNumber = "1";
        std::string testResults = pkbSP_m2->getStatementMapping(stmtNumber, DesignEntity::READ);
        std::string expectedResults = "x";
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Test for Read 2") {
        std::string stmtNumber = "2";
        std::string testResults = pkbSP_m2->getStatementMapping(stmtNumber, DesignEntity::READ);
        std::string expectedResults = "z";
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Test for Call 1") {
        std::string stmtNumber = "3";
        std::string testResults = pkbSP_m2->getStatementMapping(stmtNumber, DesignEntity::CALL);
        std::string expectedResults = "Second";
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Test for Call 2") {
        std::string stmtNumber = "8";
        std::string testResults = pkbSP_m2->getStatementMapping(stmtNumber, DesignEntity::CALL);
        std::string expectedResults = "Third";
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("Value name to statement mapping queries SP") {
    SECTION("Test for Print") {
        std::string valueName = "v";
        std::unordered_set<std::string> testResults = pkbSP_m2->getStatementByName(valueName, DesignEntity::PRINT);
        std::unordered_set<std::string> expectedResults = { "18" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Test for Read 1") {
        std::string valueName = "x";
        std::unordered_set<std::string> testResults = pkbSP_m2->getStatementByName(valueName, DesignEntity::READ);
        std::unordered_set<std::string> expectedResults = { "1" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Test for Read 2") {
        std::string valueName = "z";
        std::unordered_set<std::string> testResults = pkbSP_m2->getStatementByName(valueName, DesignEntity::READ);
        std::unordered_set<std::string> expectedResults = { "2" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Test for Call 1") {
        std::string valueName = "Second";
        std::unordered_set<std::string> testResults = pkbSP_m2->getStatementByName(valueName, DesignEntity::CALL);
        std::unordered_set<std::string> expectedResults = { "3" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Test for Call 2") {
        std::string valueName = "Third";
        std::unordered_set<std::string> testResults = pkbSP_m2->getStatementByName(valueName, DesignEntity::CALL);
        std::unordered_set<std::string> expectedResults = { "8" };
        REQUIRE(testResults == expectedResults);
    }
}

TEST_CASE("Get all value name queries SP") {
    SECTION("Test for Print") {
        std::unordered_set<std::string> testResults = pkbSP_m2->getAllName(DesignEntity::PRINT);
        std::unordered_set<std::string> expectedResults = { "v" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Test for Read") {
        std::unordered_set<std::string> testResults = pkbSP_m2->getAllName(DesignEntity::READ);
        std::unordered_set<std::string> expectedResults = { "x", "z" };
        REQUIRE(testResults == expectedResults);
    }

    SECTION("Test for Call") {
        std::unordered_set<std::string> testResults = pkbSP_m2->getAllName(DesignEntity::CALL);
        std::unordered_set<std::string> expectedResults = { "Second", "Third" };
        REQUIRE(testResults == expectedResults);
    }
}
