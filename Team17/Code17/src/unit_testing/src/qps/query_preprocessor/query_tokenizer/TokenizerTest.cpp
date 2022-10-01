#include "components/qps/query_preprocessor/query_tokenizer/Tokenizer.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "ReusableTokens.h"

#include <catch.hpp>
#include <iostream>

TEST_CASE("Declarations - Single") {
    std::string testQuery = "variable v;";
    std::vector<TokenObject> expectedResult {variableTokenObject, v_nameTokenObject, semicolonTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);
    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Declarations - Multiple") {
    std::string testQuery = "stmt s, s1; variable v, v1; procedure p, q; assign a, a1; while w; if ifs; constant c; read re; print pn; call cl;";
    std::vector<TokenObject> expectedResult {
        stmtTokenObject, s_nameTokenObject, commaTokenObject, s1_nameTokenObject, semicolonTokenObject,
        variableTokenObject, v_nameTokenObject, commaTokenObject, v1_nameTokenObject, semicolonTokenObject,
        procTokenObject, p_nameTokenObject, commaTokenObject, q_nameTokenObject, semicolonTokenObject,
        assignTokenObject, a_nameTokenObject, commaTokenObject, a1_nameTokenObject, semicolonTokenObject,
        whileTokenObject, w_nameTokenObject, semicolonTokenObject,
        ifTokenObject, ifs_nameTokenObject, semicolonTokenObject,
        constantTokenObject, c_nameTokenObject, semicolonTokenObject,
        readTokenObject, re_nameTokenObject, semicolonTokenObject,
        printTokenObject, pn_nameTokenObject, semicolonTokenObject,
        callTokenObject, cl_nameTokenObject, semicolonTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("No relationship") {
    std::string testQuery = "variable v; Select v";
    std::vector<TokenObject> expectedResult {variableTokenObject, v_nameTokenObject, semicolonTokenObject,
    selectTokenObject, v_nameTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Modifies Relationship with integer") {
    std::string testQuery = "variable v;\n"
                            "Select v such that Modifies (6, v)";
    std::vector<TokenObject> expectedResult {variableTokenObject, v_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, v_nameTokenObject, suchTokenObject, thatTokenObject,
                                             modifiesTokenObject, openBracketTokenObject, six_intTokenObject, commaTokenObject,
                                             v_nameTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Uses Relationship with integer") {
    std::string testQuery = "variable v;\n"
                            "Select v such that Uses (14, v)";
    std::vector<TokenObject> expectedResult {variableTokenObject, v_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, v_nameTokenObject, suchTokenObject, thatTokenObject,
                                             usesTokenObject, openBracketTokenObject, fourteen_intTokenObject, commaTokenObject,
                                             v_nameTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Follows Relationship") {
    std::string testQuery = "stmt s;\n"
                            "Select s such that Follows (6, s)";
    std::vector<TokenObject> expectedResult {stmtTokenObject, s_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, s_nameTokenObject, suchTokenObject, thatTokenObject,
                                             followsTokenObject, openBracketTokenObject, six_intTokenObject, commaTokenObject,
                                             s_nameTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Follows* Relationship") {
    std::string testQuery = "stmt s;\n"
                            "Select s such that Follows* (6, s)";
    std::vector<TokenObject> expectedResult {stmtTokenObject, s_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, s_nameTokenObject, suchTokenObject, thatTokenObject,
                                             followsTTokenObject, openBracketTokenObject, six_intTokenObject, commaTokenObject,
                                             s_nameTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Parent Relationship") {
    std::string testQuery = "stmt s;\n"
                            "Select s such that Parent (s, 6)";
    std::vector<TokenObject> expectedResult {stmtTokenObject, s_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, s_nameTokenObject, suchTokenObject, thatTokenObject,
                                             parentTokenObject, openBracketTokenObject, s_nameTokenObject, commaTokenObject,
                                             six_intTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Parent* Relationship") {
    std::string testQuery = "assign a; while w;\n"
                            "Select a such that Parent* (w, a)";
    std::vector<TokenObject> expectedResult {assignTokenObject, a_nameTokenObject, semicolonTokenObject,
                                             whileTokenObject, w_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, a_nameTokenObject, suchTokenObject, thatTokenObject,
                                             parentTTokenObject, openBracketTokenObject, w_nameTokenObject, commaTokenObject,
                                             a_nameTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Pattern Clause with expressions and subexpressions") {
    std::string testQuery = "assign newa;\n"
                            "Select newa pattern newa ( \"normSq    \n  \" , _\"cenX\"_)";
    std::vector<TokenObject> expectedResult {assignTokenObject, newa_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, newa_nameTokenObject, patternTokenObject, newa_nameTokenObject,
                                             openBracketTokenObject, normsq_nameWithQuotesTokenObject, commaTokenObject,
                                             cenX_subexpressionTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Queries with synonyms as design entities") {
    std::string testQuery = "assign variable;\n"
                            "Select variable pattern variable ( \" \v  normSq   \t \" , _\" \n cenX\"_)";
    std::vector<TokenObject> expectedResult {assignTokenObject, variableTokenObject, semicolonTokenObject,
                                             selectTokenObject, variableTokenObject, patternTokenObject, variableTokenObject,
                                             openBracketTokenObject, normsq_nameWithQuotesTokenObject, commaTokenObject,
                                             cenX_subexpressionTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Pattern Clause with constant expressions") {
    std::string testQuery = "assign newa;\n"
                            "Select newa pattern newa ( \"normSq\" , \"1\")";
    std::vector<TokenObject> expectedResult {assignTokenObject, newa_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, newa_nameTokenObject, patternTokenObject, newa_nameTokenObject,
                                             openBracketTokenObject, normsq_nameWithQuotesTokenObject, commaTokenObject,
                                             one_constantExpressionTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Pattern Clause with constant subexpressions") {
    std::string testQuery = "assign a1;\n"
                            "Select a1 pattern a1 ( \"x\" , _\"11\"_)";
    std::vector<TokenObject> expectedResult {assignTokenObject, a1_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, a1_nameTokenObject, patternTokenObject, a1_nameTokenObject,
                                             openBracketTokenObject, x_nameWithQuotesTokenObject, commaTokenObject,
                                             eleven_constantSubexpressionTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Capital letter synonyms") {
    std::string testQuery = "stmt Statement;\n"
                            "Select Statement such that Parent (s, 6)";
    std::vector<TokenObject> expectedResult {stmtTokenObject, capital_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, capital_nameTokenObject, suchTokenObject, thatTokenObject,
                                             parentTokenObject, openBracketTokenObject, s_nameTokenObject, commaTokenObject,
                                             six_intTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Capital letter design entity synonyms ") {
    std::string testQuery = "variable Variable;\n"
                            "Select Variable such that Modifies (6, Variable)";
    std::vector<TokenObject> expectedResult {variableTokenObject, capitalEntity_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, capitalEntity_nameTokenObject, suchTokenObject, thatTokenObject,
                                             modifiesTokenObject, openBracketTokenObject, six_intTokenObject, commaTokenObject,
                                             capitalEntity_nameTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

// Calls and Calls* Clauses
TEST_CASE("Calls Relationships") {
    std::string testQuery = "procedure p, q;\n"
                            "Select p such that Calls(p, q)";
    std::vector<TokenObject> expectedResult {procTokenObject, p_nameTokenObject, commaTokenObject, q_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, p_nameTokenObject, suchTokenObject, thatTokenObject,
                                             callsTokenObject,openBracketTokenObject,p_nameTokenObject, commaTokenObject, q_nameTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Calls* Relationships") {
    std::string testQuery = "procedure p, q;\n"
                            "Select p such that Calls*(p, q)";
    std::vector<TokenObject> expectedResult {procTokenObject, p_nameTokenObject, commaTokenObject, q_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, p_nameTokenObject, suchTokenObject, thatTokenObject,
                                             callsTTokenObject,openBracketTokenObject,p_nameTokenObject, commaTokenObject, q_nameTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

// Next and Next* relationship
TEST_CASE("Next Relationships") {
    std::string testQuery = "stmt s; stmt s1;\n"
                            "Select s1 such that Next(s, s1)";
    std::vector<TokenObject> expectedResult {stmtTokenObject, s_nameTokenObject, semicolonTokenObject, stmtTokenObject, s1_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, s1_nameTokenObject, suchTokenObject, thatTokenObject,
                                             nextTokenObject, openBracketTokenObject, s_nameTokenObject, commaTokenObject, s1_nameTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Next* Relationships") {
    std::string testQuery = "stmt s1; stmt s;\n"
                            "Select s1 such that Next*(s1, s)";
    std::vector<TokenObject> expectedResult {stmtTokenObject, s1_nameTokenObject, semicolonTokenObject, stmtTokenObject, s_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, s1_nameTokenObject, suchTokenObject, thatTokenObject,
                                             nextTTokenObject, openBracketTokenObject, s1_nameTokenObject, commaTokenObject, s_nameTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

// Affects and Affects* Relationships
TEST_CASE("Affects Relationships") {
    std::string testQuery = "stmt s; stmt s1;\n"
                            "Select s1 such that Affects(s, s1)";
    std::vector<TokenObject> expectedResult {stmtTokenObject, s_nameTokenObject, semicolonTokenObject, stmtTokenObject, s1_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, s1_nameTokenObject, suchTokenObject, thatTokenObject,
                                             affectsTokenObject, openBracketTokenObject, s_nameTokenObject, commaTokenObject, s1_nameTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Affects* Relationships") {
    std::string testQuery = "stmt s1; stmt s;\n"
                            "Select s1 such that Affects*(s1, s)";
    std::vector<TokenObject> expectedResult {stmtTokenObject, s1_nameTokenObject, semicolonTokenObject, stmtTokenObject, s_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, s1_nameTokenObject, suchTokenObject, thatTokenObject,
                                             affectsTTokenObject, openBracketTokenObject, s1_nameTokenObject, commaTokenObject, s_nameTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

// AND clause
TEST_CASE("AND clause with relationships") {
    std::string testQuery = "assign a; while w;\n"
                            "Select a such that Modifies(a, \"x\") and Parent*(w, a) and Next*(6, a)";
    std::vector<TokenObject> expectedResult {assignTokenObject, a_nameTokenObject, semicolonTokenObject, whileTokenObject, w_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, a_nameTokenObject, suchTokenObject, thatTokenObject, modifiesTokenObject, openBracketTokenObject, a_nameTokenObject, commaTokenObject, x_nameWithQuotesTokenObject, closedBracketTokenObject,
                                             andTokenObject, parentTTokenObject, openBracketTokenObject, w_nameTokenObject, commaTokenObject, a_nameTokenObject, closedBracketTokenObject,
                                             andTokenObject, nextTTokenObject, openBracketTokenObject, six_intTokenObject, commaTokenObject, a_nameTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

// Return BOOLEAN
TEST_CASE("Returns BOOLEAN") {
    std::string testQuery = "Select BOOLEAN such that Affects*(s1, s)";
    std::vector<TokenObject> expectedResult {selectTokenObject, booleanTokenObject, suchTokenObject, thatTokenObject,
                                             affectsTTokenObject, openBracketTokenObject, s1_nameTokenObject, commaTokenObject, s_nameTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

// White spaces
TEST_CASE("White spaces within relationships") {
    std::string testQuery = "stmt\v s1   ; stmt s;\n"
                            "Select s1  \f   such that Next*   (\ts1, s\f)";
    std::vector<TokenObject> expectedResult {stmtTokenObject, s1_nameTokenObject, semicolonTokenObject, stmtTokenObject, s_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, s1_nameTokenObject, suchTokenObject, thatTokenObject,
                                             nextTTokenObject, openBracketTokenObject, s1_nameTokenObject, commaTokenObject, s_nameTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("White spaces within quotes") {
    std::string testQuery = "assign a1;  \t"
                            "Select a1  pattern a1 ( \" \n\r\v  x    \" , _\"\v 11\t \"_)";
    std::vector<TokenObject> expectedResult {assignTokenObject, a1_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, a1_nameTokenObject, patternTokenObject, a1_nameTokenObject,
                                             openBracketTokenObject, x_nameWithQuotesTokenObject, commaTokenObject,
                                             eleven_constantSubexpressionTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

// Return Tuples
TEST_CASE("Tuples with 2 synonym") {
    std::string testQuery = "assign a1, a2; Select <a1, a2> such that Affects (a1, a2)";
    std::vector<TokenObject> expectedResult {assignTokenObject, a1_nameTokenObject, commaTokenObject, a2_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, twoSyn_tupleTokenObject, suchTokenObject, thatTokenObject,
                                             affectsTokenObject, openBracketTokenObject, a1_nameTokenObject, commaTokenObject, a2_nameTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Tuples with 3 synonym") {
    std::string testQuery = "assign a1, a2, a; Select <a,a1, a2> such that Affects (a1, a2)";
    std::vector<TokenObject> expectedResult {assignTokenObject, a1_nameTokenObject, commaTokenObject, a2_nameTokenObject, commaTokenObject, a_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, threeSyn_tupleTokenObject, suchTokenObject, thatTokenObject,
                                             affectsTokenObject, openBracketTokenObject, a1_nameTokenObject, commaTokenObject, a2_nameTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Valid Expressions tests") {
    SECTION("Test 1") {
        std::string testQuery = "assign a1;\n"
                                "Select a1 pattern a1 ( \"x\" , \"1\")";
        std::vector<TokenObject> expectedResult {assignTokenObject, a1_nameTokenObject, semicolonTokenObject,
                                                 selectTokenObject, a1_nameTokenObject, patternTokenObject, a1_nameTokenObject,
                                                 openBracketTokenObject, x_nameWithQuotesTokenObject, commaTokenObject,
                                                 one_constantExpressionTokenObject, closedBracketTokenObject};
        Tokenizer tokenizer = Tokenizer();
        std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);
        REQUIRE(testResult == expectedResult);
    }

    SECTION("Test 2") {
        std::string testQuery = "assign a1;\n"
                                "Select a1 pattern a1 ( \"x\" , \"(x+y)\")";
        std::vector<TokenObject> expectedResult {assignTokenObject, a1_nameTokenObject, semicolonTokenObject,
                                                 selectTokenObject, a1_nameTokenObject, patternTokenObject, a1_nameTokenObject,
                                                 openBracketTokenObject, x_nameWithQuotesTokenObject, commaTokenObject,
                                                 expressionTokenObject1, closedBracketTokenObject};
        Tokenizer tokenizer = Tokenizer();
        std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);
        REQUIRE(testResult == expectedResult);
    }

    SECTION("Test 3") {
        std::string testQuery = "assign a1;\n"
                                "Select a1 pattern a1 ( \"x\" , \"((x+y))*(www / 3)\")";
        std::vector<TokenObject> expectedResult {assignTokenObject, a1_nameTokenObject, semicolonTokenObject,
                                                 selectTokenObject, a1_nameTokenObject, patternTokenObject, a1_nameTokenObject,
                                                 openBracketTokenObject, x_nameWithQuotesTokenObject, commaTokenObject,
                                                 expressionTokenObject2, closedBracketTokenObject};
        Tokenizer tokenizer = Tokenizer();
        std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);
        REQUIRE(testResult == expectedResult);
    }

    SECTION("Test 4") {
        std::string testQuery = "assign a1;\n"
                                "Select a1 pattern a1 ( \"x\" , \"((x1+y))*(1 / 3)\")";
        std::vector<TokenObject> expectedResult {assignTokenObject, a1_nameTokenObject, semicolonTokenObject,
                                                 selectTokenObject, a1_nameTokenObject, patternTokenObject, a1_nameTokenObject,
                                                 openBracketTokenObject, x_nameWithQuotesTokenObject, commaTokenObject,
                                                 expressionTokenObject3, closedBracketTokenObject};
        Tokenizer tokenizer = Tokenizer();
        std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);
        REQUIRE(testResult == expectedResult);
    }

    SECTION("Test 5") {
        std::string testQuery = "assign a1;\n"
                                "Select a1 pattern a1 ( \"x\" , \"((x/(s-y)))*(www / (3*(2/x)))\")";
        std::vector<TokenObject> expectedResult {assignTokenObject, a1_nameTokenObject, semicolonTokenObject,
                                                 selectTokenObject, a1_nameTokenObject, patternTokenObject, a1_nameTokenObject,
                                                 openBracketTokenObject, x_nameWithQuotesTokenObject, commaTokenObject,
                                                 expressionTokenObject4, closedBracketTokenObject};
        Tokenizer tokenizer = Tokenizer();
        std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);
        REQUIRE(testResult == expectedResult);
    }
}

TEST_CASE("Valid Subexpressions tests") {
    SECTION("Test 1") {
        std::string testQuery = "assign a1;\n"
                                "Select a1 pattern a1 ( \"x\" , _\"11\"_)";
        std::vector<TokenObject> expectedResult {assignTokenObject, a1_nameTokenObject, semicolonTokenObject,
                                                 selectTokenObject, a1_nameTokenObject, patternTokenObject, a1_nameTokenObject,
                                                 openBracketTokenObject, x_nameWithQuotesTokenObject, commaTokenObject,
                                                 eleven_constantSubexpressionTokenObject, closedBracketTokenObject};
        Tokenizer tokenizer = Tokenizer();
        std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);
        REQUIRE(testResult == expectedResult);
    }

    SECTION("Test 2") {
        std::string testQuery = "assign a1;\n"
                                "Select a1 pattern a1 ( \"x\" , _\"(x+y)\"_)";
        std::vector<TokenObject> expectedResult {assignTokenObject, a1_nameTokenObject, semicolonTokenObject,
                                                 selectTokenObject, a1_nameTokenObject, patternTokenObject, a1_nameTokenObject,
                                                 openBracketTokenObject, x_nameWithQuotesTokenObject, commaTokenObject,
                                                 subexpressionTokenObject1, closedBracketTokenObject};
        Tokenizer tokenizer = Tokenizer();
        std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);
        REQUIRE(testResult == expectedResult);
    }

    SECTION("Test 3") {
        std::string testQuery = "assign a1;\n"
                                "Select a1 pattern a1 ( \"x\" , _\"((x+y))*(www / 3)\"_)";
        std::vector<TokenObject> expectedResult {assignTokenObject, a1_nameTokenObject, semicolonTokenObject,
                                                 selectTokenObject, a1_nameTokenObject, patternTokenObject, a1_nameTokenObject,
                                                 openBracketTokenObject, x_nameWithQuotesTokenObject, commaTokenObject,
                                                 subexpressionTokenObject2, closedBracketTokenObject};
        Tokenizer tokenizer = Tokenizer();
        std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);
        REQUIRE(testResult == expectedResult);
    }

    SECTION("Test 4") {
        std::string testQuery = "assign a1;\n"
                                "Select a1 pattern a1 ( \"x\" , _\"((x1+y))*(1 / 3)\"_)";
        std::vector<TokenObject> expectedResult {assignTokenObject, a1_nameTokenObject, semicolonTokenObject,
                                                 selectTokenObject, a1_nameTokenObject, patternTokenObject, a1_nameTokenObject,
                                                 openBracketTokenObject, x_nameWithQuotesTokenObject, commaTokenObject,
                                                 subexpressionTokenObject3, closedBracketTokenObject};
        Tokenizer tokenizer = Tokenizer();
        std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);
        REQUIRE(testResult == expectedResult);
    }

    SECTION("Test 5") {
        std::string testQuery = "assign a1;\n"
                                "Select a1 pattern a1 ( \"x\" , _\"((x/(s-y)))*(www / (3*(2/x)))\"_)";
        std::vector<TokenObject> expectedResult {assignTokenObject, a1_nameTokenObject, semicolonTokenObject,
                                                 selectTokenObject, a1_nameTokenObject, patternTokenObject, a1_nameTokenObject,
                                                 openBracketTokenObject, x_nameWithQuotesTokenObject, commaTokenObject,
                                                 subexpressionTokenObject4, closedBracketTokenObject};
        Tokenizer tokenizer = Tokenizer();
        std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);
        REQUIRE(testResult == expectedResult);
    }
}

// Invalid tokens
TEST_CASE("Invalid name token") {
    std::string testQuery = "assign 0x1;\n";
    Tokenizer tokenizer = Tokenizer();
    REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
}

TEST_CASE("Invalid integer token") {
    std::string testQuery = "stmt s;\n"
                            "Select s such that Parent (s, 01)";
    Tokenizer tokenizer = Tokenizer();
    REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
}

TEST_CASE("Invalid expression token") {
    std::string testQuery = "assign a1;\n"
                            "Select s such that Uses (s, \"x\") pattern a (\"x\", \"y)";
    Tokenizer tokenizer = Tokenizer();
    REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
}

TEST_CASE("Invalid subexpression token") {
    std::string testQuery = "assign a1;\n"
                            "Select s such that Uses (s, \"x\") pattern a (_\"x\", _\"y\"_)";
    Tokenizer tokenizer = Tokenizer();
    REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
}

TEST_CASE("Invalid symbols token") {
    std::string testQuery = "assign *;\n"
                            "Select * such that Uses (*, \"x\")";
    Tokenizer tokenizer = Tokenizer();
    REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
}

TEST_CASE("Invalid tuples token") {
    SECTION("Test 1") {
        std::string testQuery = "assign a1, a2; Select <,a1, a2> such that Affects (a1, a2)";
        Tokenizer tokenizer = Tokenizer();
        REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
    }

    SECTION("Test 2") {
        std::string testQuery = "assign a1, a2; Select <a1, a2, a,> such that Affects (a1, a2)";
        Tokenizer tokenizer = Tokenizer();
        REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
    }

    SECTION("Test 3") {
        std::string testQuery = "assign a1, a2; Select <a1, 1a2, a> such that Affects (a1, a2)";
        Tokenizer tokenizer = Tokenizer();
        REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
    }

    SECTION("Test 4") {
        std::string testQuery = "assign a1, a2; Select <a> such that Affects (a1, a2)";
        Tokenizer tokenizer = Tokenizer();
        REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
    }

    SECTION("Test 5") {
        std::string testQuery = "assign a1, a2; Select <a,,a2,a1> such that Affects (a1, a2)";
        Tokenizer tokenizer = Tokenizer();
        REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
    }

    SECTION("Test 6") {
        std::string testQuery = "assign a1, a2; Select <<a,,a2,a1>> such that Affects (a1, a2)";
        Tokenizer tokenizer = Tokenizer();
        REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
    }

    SECTION("Test 7") {
        std::string testQuery = "assign a1, a2; Select <,a,a2,a1,> such that Affects (a1, a2)";
        Tokenizer tokenizer = Tokenizer();
        REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
    }
}

TEST_CASE("Invalid expressions and subexpressions token") {
    SECTION("Test 1") {
        std::string testQuery = "Select a1 pattern a1 ( \"x\" , \"x+a/\")";
        Tokenizer tokenizer = Tokenizer();
        REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
    }

    SECTION("Test 2") {
        std::string testQuery = "Select a1 pattern a1 ( \"x\" , \"(x+a))\")";
        Tokenizer tokenizer = Tokenizer();
        REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
    }

    SECTION("Test 3") {
        std::string testQuery = "Select a1 pattern a1 ( \"x\" , \"(x+a)/(\")";
        Tokenizer tokenizer = Tokenizer();
        REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
    }

    SECTION("Test 4") {
        std::string testQuery = "Select a1 pattern a1 ( \"x\" , \"+1+2\")";
        Tokenizer tokenizer = Tokenizer();
        REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
    }

    SECTION("Test 5") {
        std::string testQuery = "Select a1 pattern a1 ( \"x\" , \"x-+2\")";
        Tokenizer tokenizer = Tokenizer();
        REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
    }

    SECTION("Test 6") {
        std::string testQuery = "Select a1 pattern a1 ( \"x\" , \"x(x+2)+2\")";
        Tokenizer tokenizer = Tokenizer();
        REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
    }

    SECTION("Test 7") {
        std::string testQuery = "Select a1 pattern a1 ( \"x\" , _\"x*(\n)+2\"_)";
        Tokenizer tokenizer = Tokenizer();
        REQUIRE_THROWS_WITH(tokenizer.tokenize(testQuery), "Token Exception Caught");
    }
}



// Edge cases
TEST_CASE("Presence of white spaces") {
    std::string testQuery = "stmt       s;    \n"
                            "Select s    such   that Follows*    (6, \n\r\v  s)";
    std::vector<TokenObject> expectedResult {stmtTokenObject, s_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, s_nameTokenObject, suchTokenObject, thatTokenObject,
                                             followsTTokenObject, openBracketTokenObject, six_intTokenObject, commaTokenObject,
                                             s_nameTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Presence of white spaces in Name with Quotes and Subexpressions") {
    std::string testQuery = "assign newa;\n"
                            "Select newa pattern newa ( \"   \t  normSq\" , _\"   cenX  \"_)";
    std::vector<TokenObject> expectedResult {assignTokenObject, newa_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, newa_nameTokenObject, patternTokenObject, newa_nameTokenObject,
                                             openBracketTokenObject, normsq_nameWithQuotesTokenObject, commaTokenObject,
                                             cenX_subexpressionTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Presence of white spaces in tuple") {
    std::string testQuery = "assign a1, a2, a; Select <a, \na1\t, a2\r> such that Affects (a1, a2)";
    std::vector<TokenObject> expectedResult {assignTokenObject, a1_nameTokenObject, commaTokenObject, a2_nameTokenObject, commaTokenObject, a_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, threeSyn_tupleTokenObject, suchTokenObject, thatTokenObject,
                                             affectsTokenObject, openBracketTokenObject, a1_nameTokenObject, commaTokenObject, a2_nameTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Single line queries with space") {
    std::string testQuery = "assign newa; Select newa pattern newa ( \"     normSq\" , _\"   cenX  \"_)";
    std::vector<TokenObject> expectedResult {assignTokenObject, newa_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, newa_nameTokenObject, patternTokenObject, newa_nameTokenObject,
                                             openBracketTokenObject, normsq_nameWithQuotesTokenObject, commaTokenObject,
                                             cenX_subexpressionTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Single line queries without space") {
    std::string testQuery = "assign newa;Select newa pattern newa ( \"     normSq\" , _\"   cenX  \"_)";
    std::vector<TokenObject> expectedResult {assignTokenObject, newa_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, newa_nameTokenObject, patternTokenObject, newa_nameTokenObject,
                                             openBracketTokenObject, normsq_nameWithQuotesTokenObject, commaTokenObject,
                                             cenX_subexpressionTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}
