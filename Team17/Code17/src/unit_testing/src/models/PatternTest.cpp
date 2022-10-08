#include "models/Pattern/Pattern.h"
#include "models/Pattern/AssignPattern.h"
#include "models/Pattern/IfPattern.h"
#include "models/Pattern/WhilePattern.h"

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

    IfPattern ifPattern = IfPattern(ifLineNum, ifFirstValue);
    REQUIRE(ifPattern.getLineNum() == ifLineNum);
    REQUIRE(ifPattern.getFirstValue() == ifFirstValue);
}

TEST_CASE("While Pattern Test") {
    std::string whileLineNum = "1";
    std::string whileFirstValue = "firstValue";

    WhilePattern whilePattern = WhilePattern(whileLineNum, whileFirstValue);
    REQUIRE(whilePattern.getLineNum() == whileLineNum);
    REQUIRE(whilePattern.getFirstValue() == whileFirstValue);
}
