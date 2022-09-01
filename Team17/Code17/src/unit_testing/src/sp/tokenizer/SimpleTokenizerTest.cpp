#include "components/sp/utils/SpUtils.h"

#include <catch.hpp>

TEST_CASE("Split line {};") {
    std::string test_string = "{{{;;}}";
    std::vector<std::string> test_result = SpUtils::split(test_string, "[^{};]*[{};]");
    std::vector<std::string> expected_result;
    expected_result.push_back("{");
    expected_result.push_back("{");
    expected_result.push_back("{");
    expected_result.push_back(";");
    expected_result.push_back(";");
    expected_result.push_back("}");
    expected_result.push_back("}");
    REQUIRE(test_result == expected_result);
}

TEST_CASE("Split line procedure {};") {
    std::string test_string = "procedure computeAverage {read num1;sum = num1 + num2 + num3;print ave;}";
    std::vector<std::string> test_result = SpUtils::split(test_string, "[^{};]*[{};]");
    std::vector<std::string> expected_result;
    expected_result.push_back("procedure computeAverage {");
    expected_result.push_back("read num1;");
    expected_result.push_back("sum = num1 + num2 + num3;");
    expected_result.push_back("print ave;");
    expected_result.push_back("}");
    REQUIRE(test_result == expected_result);
}

TEST_CASE("Split procedure {};") {
    std::string test_string = "procedure computeAverage {"
        "read num1;"
        "sum = num1 + num2 + num3;"
        "print ave;"
        "}";
    std::vector<std::string> test_result = SpUtils::split(test_string, "[^{};]*[{};]");
    std::vector<std::string> expected_result;
    expected_result.push_back("procedure computeAverage {");
    expected_result.push_back("read num1;");
    expected_result.push_back("sum = num1 + num2 + num3;");
    expected_result.push_back("print ave;");
    expected_result.push_back("}");
    REQUIRE(test_result == expected_result);
}
