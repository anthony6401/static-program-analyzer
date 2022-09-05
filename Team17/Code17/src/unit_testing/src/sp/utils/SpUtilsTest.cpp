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
