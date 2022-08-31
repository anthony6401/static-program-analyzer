#include "components/qps/query_preprocessor/query_tokenizer/Tokenizer.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"

#include <catch.hpp>

// To be amended
TEST_CASE("Sample test function") {
    TokenObject variable_token = TokenObject(TokenType::VARIABLE, "variable");
    TokenObject v_token = TokenObject(TokenType::NAME, "v");
    TokenObject semicolon_token = TokenObject(TokenType::SEMI_COLON, ";");
    std::vector<TokenObject> expected_result;
    std::string test_string = "variable v;";
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> test_result = Tokenizer().tokenize(test_string);
    expected_result.push_back(variable_token);
    expected_result.push_back(v_token);
    expected_result.push_back(semicolon_token);
    REQUIRE(test_result == expected_result);
}


