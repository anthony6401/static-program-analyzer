#include "components/sp/validator/SimpleValidator.h"

#include <catch.hpp>
#include <regex>

TEST_CASE("valid Variable") {
    std::string test_string = "azAZ09";
    REQUIRE(SimpleValidator::validateVariable(test_string));
}

TEST_CASE("invalid Variable") {
    std::string test_string = "0abcd";
    REQUIRE(!(SimpleValidator::validateVariable(test_string)));
    test_string = "+--/%()&";
    REQUIRE(!(SimpleValidator::validateVariable(test_string)));
}

TEST_CASE("valid constant") {
    std::string test_string = "123456789";
    REQUIRE(SimpleValidator::validateConstant(test_string));
    test_string = "1";
    REQUIRE(SimpleValidator::validateConstant(test_string));
    test_string = "0";
    REQUIRE(SimpleValidator::validateConstant(test_string));
}

TEST_CASE("invalid constant") {
    std::string test_string = "012345";
    REQUIRE(!(SimpleValidator::validateConstant(test_string)));
    test_string = "-123";
    REQUIRE(!(SimpleValidator::validateConstant(test_string)));
    test_string = "000";
    REQUIRE(!(SimpleValidator::validateConstant(test_string)));
}

/*
TEST_CASE("test") {
    std::vector<std::string> result;
    std::vector<std::string> test;
    std::vector<std::string> temp;
    temp.push_back(" 1 + 2 ");
    temp.push_back(" (1 * 2) ");
    result.push_back("1 + 2");
    result.push_back("(1 * 2)");
    std::regex whiteSpace = std::regex("^ +| +$|( ) +");
    for (std::string i : temp) {
        i = std::regex_replace(i, whiteSpace, "$1");
        test.push_back(i);
    }
    REQUIRE(result==test);
}*/
