#include "components/sp/extractor/Extractor.h"

#include <catch.hpp>
#include <iostream>

void parseHolder(SimpleToken& printStmt, std::vector<std::string>& tokens,
	Extractor* extractor) {
}

Extractor generateExtractor() {
	PKB* pkb = new PKB();
	SPClient* spClient = new SPClient(pkb);
	Extractor testExtractor = Extractor(spClient);
	return testExtractor;
}

SimpleToken generateSimpleToken(SpTokenType type, std::string value, int statementNumber) {
	SimpleToken simpleToken = SimpleToken(type, value, statementNumber, &parseHolder);
	return simpleToken;
}

bool equalEntity(Entity* firstEntity, Entity* secondEntity) {
	return (firstEntity->getValue() == secondEntity->getValue());
}

bool equalRelationship(Relationship* result, Relationship* expected) {
	Entity* resultEntity1 = result->getLeftEntity();
	Entity* resultEntity2 = result->getRightEntity();
	Entity* expectedEntity1 = expected->getLeftEntity();
	Entity* expectedEntity2 = expected->getRightEntity();
	return equalEntity(resultEntity1, expectedEntity1) && equalEntity(resultEntity2, expectedEntity2);
}

/* ==================== */
/*      TEST CASES      */
/* ==================== */
 
TEST_CASE("Unit test - getModifyRelationshipForRead for valid tokentype variable a") {
	Extractor testExtractor = generateExtractor();

	SimpleToken simpleToken = generateSimpleToken(SpTokenType::TREAD, "a", 1);
	SimpleToken child = generateSimpleToken(SpTokenType::TVARIABLE, "a", 1);

	std::vector<SimpleToken> children;
	children.push_back(child);
	simpleToken.setChildren(children);

	Relationship* generatedRelationship = testExtractor.getModifyRelationshipForRead(simpleToken);

	ReadEntity* readEntity = new ReadEntity("1");
	VariableEntity* variableEntity = new VariableEntity("a");
	Relationship* expectedRelationship = new ModifyRelationship(readEntity, variableEntity);

	REQUIRE(equalRelationship(generatedRelationship, expectedRelationship));
	REQUIRE_NOTHROW(testExtractor.extractReadStmt(simpleToken));
}

TEST_CASE("Unit test - extractReadStmt for invalid tokentype constant 1") {
	Extractor testExtractor = generateExtractor();

	SimpleToken simpleToken = generateSimpleToken(SpTokenType::TCONSTANT, "1", 1);
	std::vector<SimpleToken> children;
	simpleToken.setChildren(children);

	REQUIRE_THROWS(testExtractor.extractReadStmt(simpleToken));
}

TEST_CASE("Unit test - extractReadStmt for invalid tokentype procedure proc") {
	Extractor testExtractor = generateExtractor();

	SimpleToken simpleToken = generateSimpleToken(SpTokenType::TPROCEDURE, "proc", 1);
	std::vector<SimpleToken> children;
	simpleToken.setChildren(children);

	REQUIRE_THROWS(testExtractor.extractReadStmt(simpleToken));
}

TEST_CASE("Unit test - getUsesRelationshipForPrint for valid tokentype variable a") {
	Extractor testExtractor = generateExtractor();

	SimpleToken simpleToken = generateSimpleToken(SpTokenType::TPRINT, "a", 1);
	SimpleToken child = generateSimpleToken(SpTokenType::TVARIABLE, "a", 1);

	std::vector<SimpleToken> children;
	children.push_back(child);
	simpleToken.setChildren(children);

	Relationship* generatedRelationship = testExtractor.getUsesRelationshipForPrint(simpleToken);

	PrintEntity* printEntity = new PrintEntity("1");
	VariableEntity* variableEntity = new VariableEntity("a");
	Relationship* expectedRelationship = new UsesRelationship(printEntity, variableEntity);

	REQUIRE(equalRelationship(generatedRelationship, expectedRelationship));
	REQUIRE_NOTHROW(testExtractor.extractPrintStmt(simpleToken));
}

TEST_CASE("Unit test - extractPrintStmt for invalid tokentype constant 1 ") {
	Extractor testExtractor = generateExtractor();

	SimpleToken simpleToken = generateSimpleToken(SpTokenType::TCONSTANT, "1", 1);
	std::vector<SimpleToken> children;
	simpleToken.setChildren(children);

	REQUIRE_THROWS(testExtractor.extractPrintStmt(simpleToken));
}

TEST_CASE("Unit test - extractPrintStmt for invalid tokentype procedure proc") {
	Extractor testExtractor = generateExtractor();

	SimpleToken simpleToken = generateSimpleToken(SpTokenType::TPROCEDURE, "proc", 1);
	std::vector<SimpleToken> children;
	simpleToken.setChildren(children);

	REQUIRE_THROWS(testExtractor.extractPrintStmt(simpleToken));
}

TEST_CASE("Unit test - getModifyRelationshipForAssign: a = 1") {
	Extractor testExtractor = generateExtractor();

	SimpleToken assign = generateSimpleToken(SpTokenType::TASSIGN, "a = 1", 1);
	SimpleToken varNam = generateSimpleToken(SpTokenType::TVARIABLE, "a", 1);
	SimpleToken expr_1 = generateSimpleToken(SpTokenType::TCONSTANT, "1", 1);

	std::vector<SimpleToken> children;
	children.push_back(varNam);
	children.push_back(expr_1);
	assign.setChildren(children);

	AssignEntity* assignEntity = new AssignEntity("1");
	VariableEntity* variableEntity = new VariableEntity("a");
	Relationship* expectedRelationship = new ModifyRelationship(assignEntity, variableEntity);
	Relationship* generatedRelationship = testExtractor.getModifyRelationshipForAssign(assign);

	REQUIRE(equalRelationship(generatedRelationship, expectedRelationship));
	REQUIRE_NOTHROW(testExtractor.extractAssignStmt(assign));
}

TEST_CASE("Unit test - getModifyRelationshipForAssign: a = b") {
	Extractor testExtractor = generateExtractor();

	SimpleToken assign = generateSimpleToken(SpTokenType::TASSIGN, "a = b", 1);
	SimpleToken varNam = generateSimpleToken(SpTokenType::TVARIABLE, "a", 1);
	SimpleToken expr_1 = generateSimpleToken(SpTokenType::TVARIABLE, "b", 1);

	std::vector<SimpleToken> children;
	children.push_back(varNam);
	children.push_back(expr_1);
	assign.setChildren(children);

	// code here
}

TEST_CASE("Unit test - getModifyRelationshipForAssign: a = a + 1") {
	Extractor testExtractor = generateExtractor();

	SimpleToken assign = generateSimpleToken(SpTokenType::TASSIGN, "a = a + 1", 1);
	SimpleToken varNam = generateSimpleToken(SpTokenType::TVARIABLE, "a", 1);
	SimpleToken expr_1 = generateSimpleToken(SpTokenType::TVARIABLE, "a", 1);
	SimpleToken expr_2 = generateSimpleToken(SpTokenType::TOPR, "+", 1);
	SimpleToken expr_3 = generateSimpleToken(SpTokenType::TCONSTANT, "1", 1);

	std::vector<SimpleToken> children;
	children.push_back(varNam);
	children.push_back(expr_1);
	children.push_back(expr_2);
	children.push_back(expr_3);
	assign.setChildren(children);

	// code here
}

TEST_CASE("Unit test - getModifyRelationshipForAssign: a = a + 1 - ( b * c )") {
	Extractor testExtractor = generateExtractor();

	SimpleToken assign = generateSimpleToken(SpTokenType::TASSIGN, "a = a + 1 - ( b * c )", 1);
	SimpleToken varNam = generateSimpleToken(SpTokenType::TVARIABLE, "a", 1);
	SimpleToken expr_1 = generateSimpleToken(SpTokenType::TVARIABLE, "a", 1);
	SimpleToken expr_2 = generateSimpleToken(SpTokenType::TOPR, "+", 1);
	SimpleToken expr_3 = generateSimpleToken(SpTokenType::TCONSTANT, "1", 1);
	SimpleToken expr_4 = generateSimpleToken(SpTokenType::TOPR, "-", 1);
	SimpleToken expr_5 = generateSimpleToken(SpTokenType::TVARIABLE, "b", 1);
	SimpleToken expr_6 = generateSimpleToken(SpTokenType::TOPR, "*", 1);
	SimpleToken expr_7 = generateSimpleToken(SpTokenType::TVARIABLE, "c", 1);

	std::vector<SimpleToken> children;
	children.push_back(varNam);
	children.push_back(expr_1);
	children.push_back(expr_2);
	children.push_back(expr_3);
	children.push_back(expr_4);
	children.push_back(expr_5);
	children.push_back(expr_6);
	children.push_back(expr_7);
	assign.setChildren(children);

	// code here
}

TEST_CASE("Unit test - getUsesRelationshipForAssign: a = 1") {}

TEST_CASE("Unit test - getUsesRelationshipForAssign: a = b") {}

TEST_CASE("Unit test - getUsesRelationshipForAssign: a = a + 1") {}

TEST_CASE("Unit test - getUsesRelationshipForAssign: a = a + 1 - ( b * c )") {}

TEST_CASE("Integration test - extractProcedure") {}
TEST_CASE("Integration test - extractParentRelationships") {}
TEST_CASE("Integration test - extractFollowsRelationships") {}
TEST_CASE("Integration test - extractSeriesOfStmts") {}
TEST_CASE("Integration test - extractWhileStmt") {}
TEST_CASE("Integration test - extractIfStmt") {}
TEST_CASE("Integration test - extractStmtLst") {}

// TO BE IMPLEMENTED
TEST_CASE("extractCondExpr") {}
TEST_CASE("extractCall") {}
