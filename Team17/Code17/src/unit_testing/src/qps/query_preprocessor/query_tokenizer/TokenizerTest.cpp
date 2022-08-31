#include "components/qps/query_preprocessor/query_tokenizer/Tokenizer.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "ReusableTokens.h"

#include <catch.hpp>

// To be amended
TEST_CASE("Declarations - Single") {
    std::string testQuery = "variable v;";
    std::vector<TokenObject> expectedResult {variableTokenObject, v_nameTokenObject, semicolonTokenObject};
    Tokenizer tokenizer = Tokenizer();
    std::vector<TokenObject> test_result = Tokenizer().tokenize(testQuery);

    REQUIRE(test_result == expectedResult);
}


