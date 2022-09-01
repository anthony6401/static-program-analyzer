#include "components/sp/simple_tokenizer/SimpleTokenizer.h"

#include <catch.hpp>

TEST_CASE("Split procedure bracket") {
    std::string test_string = "procedure computeAverage {"
        "read num1;"
        "sum = num1 + num2 + num3;"
        "ave = sum / 3;"
        "print ave;"
        "}";
    SimpleTokenizer tokenizer = SimpleTokenizer();
    std::vector<std::string> test_result = SimpleTokenizer().splitBracket(test_string);
    std::vector<std::string> expected_result;
    expected_result.push_back("procedure computeAverage {");
    expected_result.push_back("read num1;");
    expected_result.push_back("sum = num1 + num2 + num3;");
    expected_result.push_back("ave = sum / 3;");
    expected_result.push_back("print ave;");
    expected_result.push_back("}");
    REQUIRE(test_result == expected_result);
}