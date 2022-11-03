#include "components/sp/utils/SpUtils.h"

#include <regex>
#include <catch.hpp>

std::regex lineDelimiters = std::regex("[^{};]*[{};]");

TEST_CASE("Split line lineDelimiters") {
    std::string test_string = "{{{;;}}";
    std::vector<std::string> test_result = SpUtils::split(test_string, lineDelimiters);
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

TEST_CASE("Split line procedure lineDelimiters") {
    std::string test_string = "procedure computeAverage {read num1;sum = num1 + num2 + num3;print ave;}";
    std::vector<std::string> test_result = SpUtils::split(test_string, lineDelimiters);
    std::vector<std::string> expected_result;
    expected_result.push_back("procedure computeAverage {");
    expected_result.push_back("read num1;");
    expected_result.push_back("sum = num1 + num2 + num3;");
    expected_result.push_back("print ave;");
    expected_result.push_back("}");
    REQUIRE(test_result == expected_result);
}

TEST_CASE("Split procedure lineDelimiters") {
    std::string test_string = "procedure computeAverage {"
        "read num1;"
        "sum = num1 + num2 + num3;"
        "print ave;"
        "}";
    std::vector<std::string> test_result = SpUtils::split(test_string, lineDelimiters);
    std::vector<std::string> expected_result;
    expected_result.push_back("procedure computeAverage {");
    expected_result.push_back("read num1;");
    expected_result.push_back("sum = num1 + num2 + num3;");
    expected_result.push_back("print ave;");
    expected_result.push_back("}");
    REQUIRE(test_result == expected_result);
}

TEST_CASE("Split no lineDelimiters") {
    std::string test_string = "qwerty";
    std::vector<std::string> test_result = SpUtils::split(test_string, lineDelimiters);
    REQUIRE(test_result.empty());
}

TEST_CASE("split whitespace") {
    std::string code = "procedure test {";
    std::regex whiteSpace = std::regex("\\S+");
    std::vector<std::string> expected_result;
    expected_result.push_back("procedure");
    expected_result.push_back("test");
    expected_result.push_back("{");
    std::vector<std::string> test_result = SpUtils::split(code, whiteSpace);
    REQUIRE(expected_result == test_result);
}

TEST_CASE("join string") {
    std::vector<std::string> strings{ "if","(", "(", "(", ")", "1", ")", "2", ")","then","{"};
    REQUIRE(SpUtils::join(strings, "") == std::string("if((()1)2)then{"));
}

TEST_CASE("find close bracket") {
    std::vector<std::string> strings{ "(", "(", "(", ")", "1", ")", "2", ")" };
    REQUIRE(SpUtils::findCloseBracket(strings, 0) == 7);
    REQUIRE(SpUtils::findCloseBracket(strings, 1) == 5);
    REQUIRE(SpUtils::findCloseBracket(strings, 2) == 3);
}

TEST_CASE("find open bracket") {
    std::vector<std::string> strings{"(", "(", "(", ")", "1", ")", "2", ")"};
    REQUIRE(SpUtils::findOpenBracket(strings, 7) == 0);
    REQUIRE(SpUtils::findOpenBracket(strings, 5) == 1);
    REQUIRE(SpUtils::findOpenBracket(strings, 3) == 2);
}
