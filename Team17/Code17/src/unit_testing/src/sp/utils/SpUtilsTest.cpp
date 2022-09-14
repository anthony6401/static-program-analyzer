#include "components/sp/utils/SpUtils.h"

#include <regex>
#include <catch.hpp>

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
