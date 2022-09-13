#include "components/qps/query_preprocessor/query_tokenizer/Tokenizer.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "ReusableTokens.h"

#include <catch.hpp>
#include <iostream>

TEST_CASE("Declarations - Single") {
    std::string testQuery = "variable v;";
    std::vector<TokenObject> expectedResult {variableTokenObject, v_nameTokenObject, semicolonTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = Tokenizer().tokenize(testQuery);
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
    std::vector<TokenObject> testResult = Tokenizer().tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("No relationship") {
    std::string testQuery = "variable v; Select v";
    std::vector<TokenObject> expectedResult {variableTokenObject, v_nameTokenObject, semicolonTokenObject,
    selectTokenObject, v_nameTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = Tokenizer().tokenize(testQuery);

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
    std::vector<TokenObject> testResult = Tokenizer().tokenize(testQuery);

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
    std::vector<TokenObject> testResult = Tokenizer().tokenize(testQuery);

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
    std::vector<TokenObject> testResult = Tokenizer().tokenize(testQuery);

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
    std::vector<TokenObject> testResult = Tokenizer().tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Parent Relationship") {

}

TEST_CASE("Parent* Relationship") {

}

TEST_CASE("Pattern Clause with expressions") {
    std::string testQuery = "assign newa;\n"
                            "Select newa pattern newa ( \"normSq\" , _\"cenX\"_)";
    std::vector<TokenObject> expectedResult {assignTokenObject, newa_nameTokenObject, semicolonTokenObject,
                                             selectTokenObject, newa_nameTokenObject, patternTokenObject, newa_nameTokenObject,
                                             openBracketTokenObject, normsq_nameWithQuotesTokenObject, commaTokenObject,
                                             cenX_subexpressionTokenObject, closedBracketTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> testResult = Tokenizer().tokenize(testQuery);

    REQUIRE(testResult == expectedResult);
}

TEST_CASE("Pattern Clause with subexpressions") {

}
