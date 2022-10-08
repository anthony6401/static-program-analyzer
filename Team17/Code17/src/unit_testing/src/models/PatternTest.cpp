#include "models/Pattern/Pattern.h"
#include "models/Pattern/AssignPattern.h"
#include "models/Pattern/IfPattern.h"

#include <catch.hpp>

TEST_CASE("Pattern Test") {
    std::string lineNum = "1";
    std::string firstValue = "firstValue";

    Pattern pattern = Pattern(lineNum, firstValue);
    REQUIRE(pattern.getLineNum() == lineNum);
    REQUIRE(pattern.getFirstValue() == firstValue);
}

TEST_CASE("Assign Pattern Test") {
    std::string assignLineNum = "1";
    std::string assignFirstValue = "firstValue";
    std::string assignSecondValue = "secondValue";

    AssignPattern assignPattern = AssignPattern(assignLineNum, assignFirstValue, assignSecondValue);
    REQUIRE(assignPattern.getLineNum() == assignLineNum);
    REQUIRE(assignPattern.getFirstValue() == assignFirstValue);
    REQUIRE(assignPattern.getSecondValue() == assignSecondValue);
}

TEST_CASE("If Pattern Test") {
    std::string ifLineNum = "1";
    std::string ifFirstValue = "firstValue";

    IfPattern assignPattern = IfPattern(ifLineNum, ifFirstValue);
    REQUIRE(assignPattern.getLineNum() == ifLineNum);
    REQUIRE(assignPattern.getFirstValue() == ifFirstValue);
}
