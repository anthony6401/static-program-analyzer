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
    simpleParser_m2.parseCode("\
procedure basic {\
    a = 1;\
    while (2 == 2) {\
        a = 3;\
    }\
    if (4 == 4) then {\
        a = 5;\
    } else {\
        a = 6;\
    }\
}\
procedure whileIf {\
    a = 7;\
    while (8 == 8) {\
        if (9 == 9) then {\
            a = 10;\
        } else {\
            a = 11;\
        }\
    }\
    a = 12;\
    while (13 == 13) {\
        a = 14;\
        if (15 == 15) then {\
            a = 16;\
        } else {\
            a = 17;\
        }\
    }\
    a = 18;\
    while (19 == 19) {\
        if (20 == 20) then {\
            a = 21;\
        } else {\
            a = 22;\
        }\
        a = 23;\
    }\
    while (24 == 24) {\
        a = 25;\
        if (26 == 26) then {\
            a = 27;\
        } else {\
            a = 28;\
        }\
        a = 29;\
    }\
    a = 30;\
}\
procedure ifWhile {\
    a = 31;\
    if (32 == 32) then {\
        while (33 == 33) {\
            a = 34;\
        }\
    } else {\
        a = 35;\
    }\
    a = 36;\
    if (37 == 37) then {\
        a = 38;\
    } else {\
        while (39 == 39) {\
            a = 40;\
        }\
        a = 41;\
    }\
    a = 42;\
    if (43 == 43) then {\
        while (44 == 44) {\
            a = 45;\
        }\
    } else {\
        while (46 == 46) {\
            a = 47;\
        }\
    }\
    a = 48;\
}");
}

    /*simpleParser_m2.parseCode("procedure First {\
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
}*/
/*
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
}*/
