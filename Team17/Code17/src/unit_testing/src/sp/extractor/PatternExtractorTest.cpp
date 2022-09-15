#include "components/sp/extractor/PatternExtractor.h"

#include <catch.hpp>
#include <iostream>

void parseHolderPattern(SimpleToken& printStmt, std::vector<std::string>& tokens,
	Extractor* extractor) {
}

Extractor generateExtractorPattern() {
	PKB* pkb = new PKB();
	SPClient* spClient = new SPClient(pkb);
	Extractor testExtractor = Extractor(spClient);
	return testExtractor;
}

SimpleToken generateSimpleTokenPattern(SpTokenType type, std::string value, int statementNumber) {
	SimpleToken simpleToken = SimpleToken(type, value, statementNumber, &parseHolderPattern);
	return simpleToken;
}

/* ==================== */
/*      TEST CASES      */
/* ==================== */

TEST_CASE("Unit test - getExpressionAsString: a = 1") {
	Extractor testExtractor = generateExtractorPattern();

	SimpleToken assign = generateSimpleTokenPattern(SpTokenType::TASSIGN, "a = 1", 1);
	SimpleToken varNam = generateSimpleTokenPattern(SpTokenType::TVARIABLE, "a", 1);
	SimpleToken expres = generateSimpleTokenPattern(SpTokenType::TEXPR, "1", 1);
	SimpleToken expr_1 = generateSimpleTokenPattern(SpTokenType::TCONSTANT, "1", 1);

	std::vector<SimpleToken> exprChildren;
	exprChildren.push_back(expr_1);
	expres.setChildren(exprChildren);
	std::vector<SimpleToken> assChildren;
	assChildren.push_back(varNam);
	assChildren.push_back(expres);
	assign.setChildren(assChildren);

	std::string test_result = PatternExtractor::getExpressionAsString(expres);
	std::string expected_result = "1";

	REQUIRE(test_result == expected_result);
	REQUIRE_NOTHROW(PatternExtractor::extractPattern(testExtractor, assign));
}

TEST_CASE("Unit test - getExpressionAsString: a = b") {
	Extractor testExtractor = generateExtractorPattern();

	SimpleToken assign = generateSimpleTokenPattern(SpTokenType::TASSIGN, "a = b", 1);
	SimpleToken varNam = generateSimpleTokenPattern(SpTokenType::TVARIABLE, "a", 1);
	SimpleToken expres = generateSimpleTokenPattern(SpTokenType::TEXPR, "b", 1);
	SimpleToken expr_1 = generateSimpleTokenPattern(SpTokenType::TVARIABLE, "b", 1);

	std::vector<SimpleToken> exprChildren;
	exprChildren.push_back(expr_1);
	expres.setChildren(exprChildren);
	std::vector<SimpleToken> assChildren;
	assChildren.push_back(varNam);
	assChildren.push_back(expres);
	assign.setChildren(assChildren);

	std::string test_result = PatternExtractor::getExpressionAsString(expres);
	std::string expected_result = "b";

	REQUIRE(test_result == expected_result);
	REQUIRE_NOTHROW(PatternExtractor::extractPattern(testExtractor, assign));
}

TEST_CASE("Unit test - getExpressionAsString: a = a + 1") {
	Extractor testExtractor = generateExtractorPattern();

	SimpleToken assign = generateSimpleTokenPattern(SpTokenType::TASSIGN, "a = a + 1", 1);
	SimpleToken varNam = generateSimpleTokenPattern(SpTokenType::TVARIABLE, "a", 1);
	SimpleToken expres = generateSimpleTokenPattern(SpTokenType::TEXPR, "a + 1", 1);
	SimpleToken expr_1 = generateSimpleTokenPattern(SpTokenType::TVARIABLE, "a", 1);
	SimpleToken expr_2 = generateSimpleTokenPattern(SpTokenType::TOPR, "+", 1);
	SimpleToken expr_3 = generateSimpleTokenPattern(SpTokenType::TCONSTANT, "1", 1);

	std::vector<SimpleToken> exprChildren;
	exprChildren.push_back(expr_1);
	exprChildren.push_back(expr_2);
	exprChildren.push_back(expr_3);
	expres.setChildren(exprChildren);
	std::vector<SimpleToken> assChildren;
	assChildren.push_back(varNam);
	assChildren.push_back(expres);
	assign.setChildren(assChildren);

	std::string test_result = PatternExtractor::getExpressionAsString(expres);
	std::string expected_result = "a+1";

	REQUIRE(test_result == expected_result);
	REQUIRE_NOTHROW(PatternExtractor::extractPattern(testExtractor, assign));
}

TEST_CASE("Unit test - getExpressionAsString: a = a + 1 - ( b * c )") {
	Extractor testExtractor = generateExtractorPattern();

	SimpleToken assign = generateSimpleTokenPattern(SpTokenType::TASSIGN, "a = a + 1 - ( b * c )", 1);
	SimpleToken varNam = generateSimpleTokenPattern(SpTokenType::TVARIABLE, "a", 1);
	SimpleToken expres = generateSimpleTokenPattern(SpTokenType::TEXPR, "a + 1 - ( b * c )", 1);
	SimpleToken expr_1 = generateSimpleTokenPattern(SpTokenType::TVARIABLE, "a", 1);
	SimpleToken expr_2 = generateSimpleTokenPattern(SpTokenType::TOPR, "+", 1);
	SimpleToken expr_3 = generateSimpleTokenPattern(SpTokenType::TCONSTANT, "1", 1);
	SimpleToken expr_4 = generateSimpleTokenPattern(SpTokenType::TOPR, "-", 1);
	SimpleToken expr_5 = generateSimpleTokenPattern(SpTokenType::TVARIABLE, "b", 1);
	SimpleToken expr_6 = generateSimpleTokenPattern(SpTokenType::TOPR, "*", 1);
	SimpleToken expr_7 = generateSimpleTokenPattern(SpTokenType::TVARIABLE, "c", 1);

	std::vector<SimpleToken> exprChildren;
	exprChildren.push_back(expr_1);
	exprChildren.push_back(expr_2);
	exprChildren.push_back(expr_3);
	exprChildren.push_back(expr_4);
	exprChildren.push_back(expr_5);
	exprChildren.push_back(expr_6);
	exprChildren.push_back(expr_7);
	expres.setChildren(exprChildren);
	std::vector<SimpleToken> assChildren;
	assChildren.push_back(varNam);
	assChildren.push_back(expres);
	assign.setChildren(assChildren);

	std::string test_result = PatternExtractor::getExpressionAsString(expres);
	std::string expected_result = "a+1-b*c";

	REQUIRE(test_result == expected_result);
	REQUIRE_NOTHROW(PatternExtractor::extractPattern(testExtractor, assign));
}
