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
}

TEST_CASE("Test isSubExpression function") {
	std::string fullExp1 = "abcdef b c d % e - * f g h * + % + i - ";

	std::string subExp1 = "a"; //return false
	std::string subExp2 = "abcdef"; //return true
	std::string subExp3 = "c%d-e"; //return true
	std::string subExp4 = "abcdef+b*(c%d-e)%(f+g*h)-i"; //return true

	REQUIRE(!PatternUtils::isSubExpression(subExp1, fullExp1));
	REQUIRE(PatternUtils::isSubExpression(subExp2, fullExp1));
	REQUIRE(PatternUtils::isSubExpression(subExp3, fullExp1));
	REQUIRE(PatternUtils::isSubExpression(subExp4, fullExp1));

	// Infix: (((a*(b+c)+(c*d))%(m-abc)-((def+z*y)))*abcdefghijklmnopqrstuvwxyz)+raurafweugl
	std::string fullExp2 = PatternUtils::convertInfixToPostfix("(((a+(b+c)+((c*d)))%(abc-m)-((def+z*y)))*abcdefghijklmnopqrstuvwxyz)+raurafweugl");

	std::string subExp5 = "a+b"; //return false
	std::string subExp6 = "def+z"; //return false
	std::string subExp7 = "d%(abc-m)"; //return false
	std::string subExp8 = "(((a+(b+c)+(c*d))%(abc-m)-((def+z*y)))*bcdef)"; //return false
	std::string subExp9 = "c-m"; //return false
	std::string subExp10 = "(b+c)+(c*d)"; //return false


	REQUIRE(!PatternUtils::isSubExpression(subExp5, fullExp2));
	REQUIRE(!PatternUtils::isSubExpression(subExp6, fullExp2));
	REQUIRE(!PatternUtils::isSubExpression(subExp7, fullExp2));
	REQUIRE(!PatternUtils::isSubExpression(subExp8, fullExp2));
	REQUIRE(!PatternUtils::isSubExpression(subExp9, fullExp2));
	REQUIRE(!PatternUtils::isSubExpression(subExp10, fullExp2));

	std::string fullExp3 = PatternUtils::convertInfixToPostfix("((a*b))+((c/d))");

	std::string subExp11 = "(a*b)+(c/d)"; //return true
	std::string subExp12 = "a*b+c/d"; //return true

	REQUIRE(PatternUtils::isSubExpression(subExp11, fullExp3));
	REQUIRE(PatternUtils::isSubExpression(subExp12, fullExp3));

}
