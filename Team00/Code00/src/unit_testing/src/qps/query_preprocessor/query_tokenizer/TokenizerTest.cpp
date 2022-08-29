#include "components/qps/query_preprocessor/query_tokenizer/Tokenizer.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

#include <catch.hpp>

// To be amended
TEST_CASE("Sample test function") {
    std::string test_string = "A123ndrea";
    Tokenizer tokenizer = Tokenizer();
    bool test_result = Tokenizer().tokenize(test_string);
    bool expected_result = true;
    REQUIRE(test_result == expected_result);
}
