#include "models/Relationship.h"
#include "models/ModifyRelationship.h"
#include "models/UsesRelationship.h"

#include <catch.hpp>

// To be amended
TEST_CASE("Relationship Test") {
    std::string leftValue = "leftValue";
    std::string rightValue = "rightValue";
    Relationship relationship = Relationship(leftValue, rightValue);
    REQUIRE(relationship.getLeftValue() == leftValue);
    REQUIRE(relationship.getRightValue() == rightValue);
}

TEST_CASE("Uses Relationship Test") {
    std::string leftValue = "1";
    std::string rightValue = "variableA";
    Relationship relationship = UsesRelationship(leftValue, rightValue);
    REQUIRE(relationship.getLeftValue() == leftValue);
    REQUIRE(relationship.getRightValue() == rightValue);
}

TEST_CASE("Modify Relationship Test") {
    std::string leftValue = "1";
    std::string rightValue = "variableA";
    Relationship relationship = Relationship(leftValue, rightValue);
    REQUIRE(relationship.getLeftValue() == leftValue);
    REQUIRE(relationship.getRightValue() == rightValue);
}