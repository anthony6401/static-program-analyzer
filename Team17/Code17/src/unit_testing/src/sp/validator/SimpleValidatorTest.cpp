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
