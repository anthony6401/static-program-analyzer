#include "models/Pattern/Pattern.h"
#include "models/Pattern/AssignPattern.h"

#include <catch.hpp>

TEST_CASE("Pattern Test") {
    std::string lineNum = "1";
    std::string firstValue = "firstValue";
    std::string secondValue = "secondValue";

    Pattern pattern = Pattern(lineNum, firstValue, secondValue);
    REQUIRE(pattern.getLineNum() == lineNum);
    REQUIRE(pattern.getFirstValue() == firstValue);
    REQUIRE(pattern.getSecondValue() == secondValue);
}

TEST_CASE("Assign Pattern Test") {
    std::string assignLineNum = "1";
    std::string assignFirstValue = "firstValue";
    std::string assignSecondValue = "secondValue";

    Pattern assignPattern = AssignPattern(assignLineNum, assignFirstValue, assignSecondValue);
    REQUIRE(assignPattern.getLineNum() == assignLineNum);
    REQUIRE(assignPattern.getFirstValue() == assignFirstValue);
    REQUIRE(assignPattern.getSecondValue() == assignSecondValue);
}
