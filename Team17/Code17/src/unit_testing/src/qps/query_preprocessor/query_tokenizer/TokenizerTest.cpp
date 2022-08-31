#include "components/qps/query_preprocessor/query_tokenizer/Tokenizer.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "ReusableTokens.h"

#include <catch.hpp>
#include <iostream>


// To be added
TEST_CASE("Declarations - Single") {
    std::string testQuery = "variable v;";
    std::vector<TokenObject> expectedResult {variableTokenObject, v_nameTokenObject, semicolonTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> test_result = Tokenizer().tokenize(testQuery);
    REQUIRE(test_result == expectedResult);
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
    std::vector<TokenObject> test_result = Tokenizer().tokenize(testQuery);
    // For debugging purposes
    //    std::cout << test_result.size();
    //    for (TokenObject o : test_result) {
    //        std::cout << o.getValue() << std::endl;
    //    }
    REQUIRE(test_result == expectedResult);
}

TEST_CASE("DEMO") {
    std::string testQuery = "variable v; Select v";
    std::vector<TokenObject> expectedResult {variableTokenObject, v_nameTokenObject, semicolonTokenObject,
    selectTokenObject, v_nameTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> test_result = Tokenizer().tokenize(testQuery);
    REQUIRE(test_result == expectedResult);
}
