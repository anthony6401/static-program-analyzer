#include "components/pkb/storage/PatternStorage/utils.h"

#include<iostream>
#include<string>


#include <catch.hpp>

TEST_CASE("Test infix to postfix function") {
	std::string test1 = "a+b"; //Simple format
	std::string test2 = "a+b*c"; //with different hierarchy
	std::string test3 = "(a+b)*c"; //with brackets
	std::string test4 = "abcdef+b*(c%d-e)%(f+g*h)-i"; ///Long variable name and brackets and different arithmetic operations

	std::string expectedResult1 = "a b + ";
	std::string expectedResult2 = "a b c * + ";
	std::string expectedResult3 = "a b + c * ";
	std::string expectedResult4 = "abcdef b c d % e - * f g h * + % + i - ";

	REQUIRE(PatternUtils::convertInfixToPostfix(test1) == expectedResult1);
	REQUIRE(PatternUtils::convertInfixToPostfix(test2) == expectedResult2);
	REQUIRE(PatternUtils::convertInfixToPostfix(test3) == expectedResult3);
	REQUIRE(PatternUtils::convertInfixToPostfix(test4) == expectedResult4);
	//REQUIRE(PatternUtils::convertInfixToPostfix(test3) == expectedResult4);
}

TEST_CASE("Test isSubExpression function") {
	std::string fullExp = "abcdef b c d % e - * f g h * + % + i - ";

	std::string subExp1 = "a"; //return false
	std::string subExp2 = "abcdef"; //return true
	std::string subExp3 = "c%d-e"; //return true
	std::string subExp4 = "abcdef+b*(c%d-e)%(f+g*h)-i"; //return true

	REQUIRE(!PatternUtils::isSubExpression(subExp1, fullExp));
	REQUIRE(PatternUtils::isSubExpression(subExp2, fullExp));
	REQUIRE(PatternUtils::isSubExpression(subExp3, fullExp));
	REQUIRE(PatternUtils::isSubExpression(subExp4, fullExp));
}
