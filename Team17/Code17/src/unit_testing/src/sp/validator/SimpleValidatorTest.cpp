#include "components/sp/validator/SimpleValidator.h"

#include <catch.hpp>

TEST_CASE("valid lexical") {
    std::string test_string = "azAZ09";
    REQUIRE(SimpleValidator::validateLexical(test_string));
}

TEST_CASE("invalid lexical") {
    std::string test_string = "+-*/=<>;\"\'[]{}&!";
    REQUIRE(!(SimpleValidator::validateLexical(test_string)));
}
