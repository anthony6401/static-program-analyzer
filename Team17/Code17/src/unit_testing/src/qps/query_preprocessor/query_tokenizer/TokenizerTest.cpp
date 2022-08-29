#include "components/qps/query_preprocessor/query_tokenizer/Tokenizer.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

#include <catch.hpp>

// To be amended
TEST_CASE("Sample test function") {
    std::vector<std::string> expected_result;
    std::string test_string = "stmt s, s1; assign a, a1; while w; if ifs; variable v, v1;\n"
                              "procedure p, q; constant c; read re; print pn; call cl;";
    Tokenizer tokenizer = Tokenizer();
    std::vector<std::string> test_result = Tokenizer().tokenize(test_string);
    expected_result.push_back("stmt");
    expected_result.push_back("s,");
    REQUIRE(test_result == expected_result);
}


