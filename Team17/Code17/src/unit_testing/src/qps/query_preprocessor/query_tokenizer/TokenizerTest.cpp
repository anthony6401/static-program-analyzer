#include "components/qps/query_preprocessor/query_tokenizer/Tokenizer.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"

#include <catch.hpp>

// To be amended
TEST_CASE("Sample test function") {
    TokenObject procedure_token = TokenObject(TokenType::VARIABLE, "variable");
    std::vector<TokenObject> expected_result;
    std::string test_string = "variable";
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> test_result = Tokenizer().tokenize(test_string);
    expected_result.push_back(procedure_token);
    REQUIRE(test_result == expected_result);
}


