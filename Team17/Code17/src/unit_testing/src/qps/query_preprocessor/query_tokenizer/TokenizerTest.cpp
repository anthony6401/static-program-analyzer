#include "components/qps/query_preprocessor/query_tokenizer/Tokenizer.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "ReusableTokens.h"

#include <catch.hpp>
#include <iostream>

TEST_CASE("Test new clause") {
    std::string testQuery = "(assign a; Select a pattern a(\"( x   +y    )*z+( 3 + 2\" , _\"x * y\"_)";
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = tokenizer.tokenize(testQuery);
    REQUIRE(1 == 1);
}

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
                            "Select newa pattern newa ( \"normSq\" , _\"cenX\"_)";
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
                            "Select variable pattern variable ( \"normSq\" , _\"cenX\"_)";
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


// Edge cases
TEST_CASE("Presence of white spaces") {
    std::string testQuery = "stmt       s;    \n"
                            "Select s    such   that Follows*    (6,   s)";
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
                            "Select newa pattern newa ( \"     normSq\" , _\"   cenX  \"_)";
    std::vector<TokenObject> expectedResult {assignTokenObject, newa_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, newa_nameTokenObject, patternTokenObject, newa_nameTokenObject,
                                             openBracketTokenObject, normsq_nameWithQuotesTokenObject, commaTokenObject,
                                             cenX_subexpressionTokenObject, closedBracketTokenObject};
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
