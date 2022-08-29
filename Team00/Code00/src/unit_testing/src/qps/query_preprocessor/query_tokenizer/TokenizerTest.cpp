#include "components/qps/query_preprocessor/query_tokenizer/Tokenizer.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

#include <catch.hpp>

// To be amended
TEST_CASE("Sample name test function") {
    std::string test_string = "            Select   ";
    Tokenizer tokenizer = Tokenizer();
    std::string test_result = Tokenizer().tokenize(test_string);
    std::string expected_result = "Select";
    REQUIRE(test_result == expected_result);
}


