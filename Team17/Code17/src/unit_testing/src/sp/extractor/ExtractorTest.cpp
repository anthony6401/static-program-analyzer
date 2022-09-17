#include "components/sp/extractor/Extractor.h"

#include <catch.hpp>
#include <iostream>

void parseHolder(SimpleToken& printStmt, std::vector<std::string>& tokens,
	Extractor* extractor) {
}

SimpleToken generateProcedure(int code) {
	if (code == 4) {
		SimpleToken var_count = SimpleToken(SpTokenType::TVARIABLE, "count", 0, &parseHolder);
		SimpleToken var_cenX = SimpleToken(SpTokenType::TVARIABLE, "cenX", 0, &parseHolder);
		SimpleToken var_cenY = SimpleToken(SpTokenType::TVARIABLE, "cenY", 0, &parseHolder);
		SimpleToken var_x = SimpleToken(SpTokenType::TVARIABLE, "x", 0, &parseHolder);
		SimpleToken var_y = SimpleToken(SpTokenType::TVARIABLE, "y", 0, &parseHolder);
		SimpleToken var_flag = SimpleToken(SpTokenType::TVARIABLE, "flag", 0, &parseHolder);
		SimpleToken var_normSq = SimpleToken(SpTokenType::TVARIABLE, "normSq", 0, &parseHolder);
		SimpleToken con_0 = SimpleToken(SpTokenType::TCONSTANT, "0", 0, &parseHolder);
		SimpleToken con_1 = SimpleToken(SpTokenType::TCONSTANT, "1", 0, &parseHolder);
		SimpleToken opr_plus = SimpleToken(SpTokenType::TOPR, "+", 0, &parseHolder);
		SimpleToken opr_divi = SimpleToken(SpTokenType::TOPR, "/", 0, &parseHolder);
		SimpleToken opr_time = SimpleToken(SpTokenType::TOPR, "*", 0, &parseHolder);

		SimpleToken while_exp_1 = SimpleToken(SpTokenType::TEXPR, "count + 1", 0, &parseHolder);
		SimpleToken while_exp_2 = SimpleToken(SpTokenType::TEXPR, "cenX + x", 0, &parseHolder);
		SimpleToken while_exp_3 = SimpleToken(SpTokenType::TEXPR, "cenY + y", 0, &parseHolder);
		SimpleToken while_ass_1 = SimpleToken(SpTokenType::TASSIGN, "count = count + 1", 5, &parseHolder);
		SimpleToken while_ass_2 = SimpleToken(SpTokenType::TASSIGN, "cenX = cenX + x", 6, &parseHolder);
		SimpleToken while_ass_3 = SimpleToken(SpTokenType::TASSIGN, "cenY = cenY + y", 7, &parseHolder);
		SimpleToken while_stmtLst = SimpleToken(SpTokenType::TSTMTLIST, "", 0, &parseHolder);
		SimpleToken while_cond = SimpleToken(SpTokenType::TCONDEXPR, "((x != 0) && (y != 0))", 0, &parseHolder);
		SimpleToken whileT = SimpleToken(SpTokenType::TWHILE, "while ((x != 0) && (y != 0))", 4, &parseHolder);
		std::vector<SimpleToken> w_exp_1;
		std::vector<SimpleToken> w_exp_2;
		std::vector<SimpleToken> w_exp_3;
		std::vector<SimpleToken> w_ass_1;
		std::vector<SimpleToken> w_ass_2;
		std::vector<SimpleToken> w_ass_3;
		std::vector<SimpleToken> w_stmtLst;
		std::vector<SimpleToken> w_cond;
		std::vector<SimpleToken> whC;
		w_exp_1.push_back(var_count);
		w_exp_1.push_back(opr_plus);
		w_exp_1.push_back(con_1);
		while_exp_1.setChildren(w_exp_1);
		w_exp_2.push_back(var_cenX);
		w_exp_2.push_back(opr_plus);
		w_exp_2.push_back(var_x);
		while_exp_2.setChildren(w_exp_2);
		w_exp_3.push_back(var_cenY);
		w_exp_3.push_back(opr_plus);
		w_exp_3.push_back(var_y);
		while_exp_3.setChildren(w_exp_3);
		w_ass_1.push_back(var_count);
		w_ass_1.push_back(while_exp_1);
		while_ass_1.setChildren(w_ass_1);
		w_ass_2.push_back(var_cenX);
		w_ass_2.push_back(while_exp_2);
		while_ass_2.setChildren(w_ass_2);
		w_ass_3.push_back(var_cenY);
		w_ass_3.push_back(while_exp_3);
		while_ass_3.setChildren(w_ass_3);
		w_stmtLst.push_back(while_ass_1);
		w_stmtLst.push_back(while_ass_2);
		w_stmtLst.push_back(while_ass_3);
		while_stmtLst.setChildren(w_stmtLst);
		w_cond.push_back(var_x);
		w_cond.push_back(con_0);
		w_cond.push_back(var_y);
		w_cond.push_back(con_0);
		while_cond.setChildren(w_cond);
		whC.push_back(while_cond);
		whC.push_back(while_stmtLst);
		whileT.setChildren(whC);
		
		SimpleToken if_exp_1 = SimpleToken(SpTokenType::TEXPR, "1", 0, &parseHolder);
		SimpleToken if_exp_2 = SimpleToken(SpTokenType::TEXPR, "cenX / count", 0, &parseHolder);
		SimpleToken if_exp_3 = SimpleToken(SpTokenType::TEXPR, "cenY / count", 0, &parseHolder);
		SimpleToken if_ass_1 = SimpleToken(SpTokenType::TASSIGN, "flag = 1", 9, &parseHolder);
		SimpleToken if_ass_2 = SimpleToken(SpTokenType::TASSIGN, "cenX = cenX / count", 10, &parseHolder);
		SimpleToken if_ass_3 = SimpleToken(SpTokenType::TASSIGN, "cenY = cenY / count", 11, &parseHolder);
		SimpleToken if_stmtLst_1 = SimpleToken(SpTokenType::TSTMTLIST, "", 0, &parseHolder);
		SimpleToken if_stmtLst_2 = SimpleToken(SpTokenType::TSTMTLIST, "", 0, &parseHolder);
		SimpleToken if_cond = SimpleToken(SpTokenType::TCONDEXPR, "(count == 0)", 0, &parseHolder);
		SimpleToken ifT = SimpleToken(SpTokenType::TIF, "if (count == 0)", 8, &parseHolder);
		std::vector<SimpleToken> i_exp_1;
		std::vector<SimpleToken> i_exp_2;
		std::vector<SimpleToken> i_exp_3;
		std::vector<SimpleToken> i_ass_1;
		std::vector<SimpleToken> i_ass_2;
		std::vector<SimpleToken> i_ass_3;
		std::vector<SimpleToken> i_stmtLst_1;
		std::vector<SimpleToken> i_stmtLst_2;
		std::vector<SimpleToken> i_cond;
		std::vector<SimpleToken> ifC;
		i_exp_1.push_back(con_1);
		if_exp_1.setChildren(i_exp_1);
		i_exp_2.push_back(var_cenX);
		i_exp_2.push_back(opr_divi);
		i_exp_2.push_back(var_count);
		if_exp_2.setChildren(i_exp_2);
		i_exp_3.push_back(var_cenY);
		i_exp_3.push_back(opr_divi);
		i_exp_3.push_back(var_count);
		if_exp_3.setChildren(i_exp_3);
		i_ass_1.push_back(var_flag);
		i_ass_1.push_back(if_exp_1);
		if_ass_1.setChildren(i_ass_1);
		i_ass_2.push_back(var_cenX);
		i_ass_2.push_back(if_exp_2);
		if_ass_2.setChildren(i_ass_2);
		i_ass_3.push_back(var_cenY);
		i_ass_3.push_back(if_exp_3);
		if_ass_3.setChildren(i_ass_3);
		i_stmtLst_1.push_back(if_ass_1);
		if_stmtLst_1.setChildren(i_stmtLst_1);
		i_stmtLst_2.push_back(if_ass_2);
		i_stmtLst_2.push_back(if_ass_3);
		if_stmtLst_2.setChildren(i_stmtLst_2);
		i_cond.push_back(var_count);
		i_cond.push_back(con_0);
		if_cond.setChildren(i_cond);
		ifC.push_back(if_cond);
		ifC.push_back(if_stmtLst_1);
		ifC.push_back(if_stmtLst_2);
		ifT.setChildren(ifC);

		SimpleToken stmt_exp_1 = SimpleToken(SpTokenType::TEXPR, "0", 0, &parseHolder);
		SimpleToken stmt_exp_2 = SimpleToken(SpTokenType::TEXPR, "0", 0, &parseHolder);
		SimpleToken stmt_exp_3 = SimpleToken(SpTokenType::TEXPR, "0", 0, &parseHolder);
		SimpleToken stmt_exp_4 = SimpleToken(SpTokenType::TEXPR, "cenX * cenX + cenY * cenY", 0, &parseHolder);
		SimpleToken stmt_ass_1 = SimpleToken(SpTokenType::TASSIGN, "count = 0", 1, &parseHolder);
		SimpleToken stmt_ass_2 = SimpleToken(SpTokenType::TASSIGN, "cenX = 0", 2, &parseHolder);
		SimpleToken stmt_ass_3 = SimpleToken(SpTokenType::TASSIGN, "cenY = 0", 3, &parseHolder);
		SimpleToken stmt_ass_4 = SimpleToken(SpTokenType::TASSIGN, "normSq = cenX * cenX + cenY * cenY", 12, &parseHolder);
		std::vector<SimpleToken> s_exp_1;
		std::vector<SimpleToken> s_exp_2;
		std::vector<SimpleToken> s_exp_3;
		std::vector<SimpleToken> s_exp_4;
		std::vector<SimpleToken> s_ass_1;
		std::vector<SimpleToken> s_ass_2;
		std::vector<SimpleToken> s_ass_3;
		std::vector<SimpleToken> s_ass_4;
		s_exp_1.push_back(con_0);
		stmt_exp_1.setChildren(s_exp_1);
		s_exp_2.push_back(con_0);
		stmt_exp_2.setChildren(s_exp_2);
		s_exp_3.push_back(con_0);
		stmt_exp_3.setChildren(s_exp_3);
		s_exp_4.push_back(var_cenX);
		s_exp_4.push_back(opr_time);
		s_exp_4.push_back(var_cenX);
		s_exp_4.push_back(opr_plus);
		s_exp_4.push_back(var_cenY);
		s_exp_4.push_back(opr_time);
		s_exp_4.push_back(var_cenY);
		stmt_exp_4.setChildren(s_exp_4);
		s_ass_1.push_back(var_count);
		s_ass_1.push_back(stmt_exp_1);
		stmt_ass_1.setChildren(s_ass_1);
		s_ass_2.push_back(var_cenX);
		s_ass_2.push_back(stmt_exp_2);
		stmt_ass_2.setChildren(s_ass_2);
		s_ass_3.push_back(var_cenY);
		s_ass_3.push_back(stmt_exp_3);
		stmt_ass_3.setChildren(s_ass_3);
		s_ass_4.push_back(var_normSq);
		s_ass_4.push_back(stmt_exp_4);
		stmt_ass_4.setChildren(s_ass_4);

		SimpleToken computeCentroid = SimpleToken(SpTokenType::TPROCEDURE, "computeCentroid", 0, &parseHolder);
		std::vector<SimpleToken> procStmtLst;
		procStmtLst.push_back(stmt_ass_1);
		procStmtLst.push_back(stmt_ass_2);
		procStmtLst.push_back(stmt_ass_3);
		procStmtLst.push_back(whileT);
		procStmtLst.push_back(ifT);
		procStmtLst.push_back(stmt_ass_4);
		computeCentroid.setChildren(procStmtLst);

		return computeCentroid;
	}

	SimpleToken procedureToken = SimpleToken(SpTokenType::TPROCEDURE, "procedure basicProcedure", 0, &parseHolder);
	SimpleToken readToken = SimpleToken(SpTokenType::TREAD, "read first", 1, &parseHolder);
	SimpleToken variableToken_first = SimpleToken(SpTokenType::TVARIABLE, "first", 0, &parseHolder);
	SimpleToken printToken = SimpleToken(SpTokenType::TPRINT, "print second", 2, &parseHolder);
	SimpleToken variableToken_second = SimpleToken(SpTokenType::TVARIABLE, "second", 0, &parseHolder);
	SimpleToken assignToken = SimpleToken(SpTokenType::TASSIGN, "x = first + second + 1", 3, &parseHolder);
	SimpleToken variableToken_x = SimpleToken(SpTokenType::TVARIABLE, "x", 0, &parseHolder);
	SimpleToken exprToken = SimpleToken(SpTokenType::TEXPR, "first + second + 1", 0, &parseHolder);
	SimpleToken constToken_1 = SimpleToken(SpTokenType::TASSIGN, "1", 0, &parseHolder);

	std::vector<SimpleToken> procedureTokenChildren;
	std::vector<SimpleToken> readTokenChildren;
	std::vector<SimpleToken> printTokenChildren;
	std::vector<SimpleToken> assignTokenChildren;
	std::vector<SimpleToken> exprTokenChildren;

	exprTokenChildren.push_back(variableToken_first);
	exprTokenChildren.push_back(variableToken_second);
	exprTokenChildren.push_back(constToken_1);
	exprToken.setChildren(exprTokenChildren);

	assignTokenChildren.push_back(variableToken_x);
	assignTokenChildren.push_back(exprToken);
	assignToken.setChildren(assignTokenChildren);

	readTokenChildren.push_back(variableToken_first);
	readToken.setChildren(readTokenChildren);

	printTokenChildren.push_back(variableToken_second);
	printToken.setChildren(printTokenChildren);

	procedureTokenChildren.push_back(readToken);
	procedureTokenChildren.push_back(printToken);
	procedureTokenChildren.push_back(assignToken);
	procedureToken.setChildren(procedureTokenChildren);

	return procedureToken;
}

std::string printResultFollows(std::vector<FollowsRelationship*> vector) {
	std::string s;
	for (int i = 0; i < vector.size(); i++) {
		s = s + vector.at(i)->getLeftEntity()->getValue() + vector.at(i)->getRightEntity()->getValue() + "\n";
	}
	return s;
}

std::string printResultFollowsT(std::vector<FollowsTRelationship*> vector) {
	std::string s;
	for (int i = 0; i < vector.size(); i++) {
		s = s + vector.at(i)->getLeftEntity()->getValue() + vector.at(i)->getRightEntity()->getValue() + "\n";
	}
	return s;
}

std::string printResultParent(std::vector<ParentRelationship*> vector) {
	std::string s;
	for (int i = 0; i < vector.size(); i++) {
		s = s + vector.at(i)->getLeftEntity()->getValue() + vector.at(i)->getRightEntity()->getValue() + "\n";
	}
	return s;
}

std::string printResultParentT(std::vector<ParentTRelationship*> vector) {
	std::string s;
	for (int i = 0; i < vector.size(); i++) {
		s = s + vector.at(i)->getLeftEntity()->getValue() + vector.at(i)->getRightEntity()->getValue() + "\n";
	}
	return s;
}

std::string printResultUses(std::vector<UsesRelationship*> vector) {
	std::string s;
	for (int i = 0; i < vector.size(); i++) {
		s = s + vector.at(i)->getLeftEntity()->getValue() + vector.at(i)->getRightEntity()->getValue() + "\n";
	}
	return s;
}

std::string printResultModify(std::vector<ModifyRelationship*> vector) {
	std::string s;
	for (int i = 0; i < vector.size(); i++) {
		s = s + vector.at(i)->getLeftEntity()->getValue() + vector.at(i)->getRightEntity()->getValue() + "\n";
	}
	return s;
}

std::string printResultPattern(std::vector<AssignPattern*> vector) {
	std::string s;
	for (int i = 0; i < vector.size(); i++) {
		s = s + vector.at(i)->getLineNum() + vector.at(i)->getFirstValue() + vector.at(i)->getSecondValue() + "\n";
	}
	return s;
}

std::string printResultConstant(std::vector<ConstantEntity*> vector) {
	std::string s;
	for (int i = 0; i < vector.size(); i++) {
		s = s + vector.at(i)->getValue() + "\n";
	}
	return s;
}

/* ==================== */
/*      TEST CASES      */
/* ==================== */
 
TEST_CASE("Unit test - FollowsExtractor::extractFollows for computeCentroid") {
	SimpleToken testProcedure = generateProcedure(4);
	std::vector<FollowsRelationship*> testResult = FollowsExtractor::extractFollows(testProcedure);
	std::string s = printResultFollows(testResult);
	REQUIRE(s == "12\n23\n34\n48\n812\n56\n67\n1011\n");
}

TEST_CASE("Unit test - FollowsExtractor::extractFollowsT for computeCentroid") {
	SimpleToken testProcedure = generateProcedure(4);
	std::vector<FollowsTRelationship*> testResult = FollowsExtractor::extractFollowsT(testProcedure);
	std::string s = printResultFollowsT(testResult);
	REQUIRE(s == "12\n13\n14\n18\n112\n23\n24\n28\n212\n34\n38\n312\n48\n412\n812\n56\n57\n67\n1011\n");
}

TEST_CASE("Unit test - ParentExtractor::extractParent for computeCentroid") {
	SimpleToken testProcedure = generateProcedure(4);
	std::vector<ParentRelationship*> testResult = ParentExtractor::extractParent(testProcedure);
	std::string s = printResultParent(testResult);
	REQUIRE(s == "45\n46\n47\n89\n810\n811\n");
}

TEST_CASE("Unit test - ParentExtractor::extractParentT for computeCentroid") {
	SimpleToken testProcedure = generateProcedure(4);
	std::vector<ParentTRelationship*> testResult = ParentExtractor::extractParentT(testProcedure);
	std::string s = printResultParentT(testResult);
	REQUIRE(s == "45\n46\n47\n89\n810\n811\n");
}

TEST_CASE("Unit test - UsesExtractor::extractUses for computeCentroid") {
	SimpleToken testProcedure = generateProcedure(4);
	std::vector<UsesRelationship*> testResult = UsesExtractor::extractUses(testProcedure);
	std::string s = printResultUses(testResult);
	REQUIRE(s == "4x\ncomputeCentroidx\n4y\ncomputeCentroidy\n5count\n6cenX\n6x\n7cenY\n7y\n8count\ncomputeCentroidcount\n10cenX\n10count\n11cenY\n11count\n12cenX\ncomputeCentroidcenX\n12cenX\ncomputeCentroidcenX\n12cenY\ncomputeCentroidcenY\n12cenY\ncomputeCentroidcenY\n");
}

TEST_CASE("Unit test - ModifyExtractor::extractModify for computeCentroid") {
	SimpleToken testProcedure = generateProcedure(4);
	std::vector<ModifyRelationship*> testResult = ModifyExtractor::extractModify(testProcedure);
	std::string s = printResultModify(testResult);
	REQUIRE(s == "computeCentroidcount\ncomputeCentroidcenX\ncomputeCentroidcenY\ncomputeCentroidcount\ncomputeCentroidcenX\ncomputeCentroidcenY\ncomputeCentroidflag\ncomputeCentroidcenX\ncomputeCentroidcenY\ncomputeCentroidnormSq\n1count\n2cenX\n3cenY\n5count\n6cenX\n7cenY\n9flag\n10cenX\n11cenY\n12normSq\n");
}

TEST_CASE("Unit test - PatternExtractor::extractPattern for computeCentroid") {
	SimpleToken testProcedure = generateProcedure(4);
	std::vector<AssignPattern*> testResult = PatternExtractor::extractPattern(testProcedure);
	std::string s = printResultPattern(testResult);
	REQUIRE(s == "1count0\n2cenX0\n3cenY0\n12normSqcenX*cenX+cenY*cenY\n5countcount+1\n6cenXcenX+x\n7cenYcenY+y\n9flag1\n10cenXcenX/count\n11cenYcenY/count\n");
}

TEST_CASE("Unit test - Extractor::extractConstants for computeCentroid") {
	SimpleToken testProcedure = generateProcedure(4);
	PKB* pkb = new PKB();
	SPClient* client = new SPClient(pkb);
	Extractor extractor = Extractor(client);
	std::vector<ConstantEntity*> testResult = extractor.extractConstantsVector(testProcedure);
	std::string s = printResultConstant(testResult);
	REQUIRE(s == "0\n0\n0\n0\n0\n1\n0\n1\n");
}

TEST_CASE("Unit test - FollowsExtractor::extractFollows for while token") {}
TEST_CASE("Unit test - FollowsExtractor::extractFollows for if token") {}
TEST_CASE("Unit test - FollowsExtractor::extractFollowsT for while token") {}
TEST_CASE("Unit test - FollowsExtractor::extractFollowsT for if token") {}
TEST_CASE("Unit test - ParentExtractor::extractParent for while") {}
TEST_CASE("Unit test - ParentExtractor::extractParent for if token") {}
TEST_CASE("Unit test - ParentExtractor::extractParentT for while token") {}
TEST_CASE("Unit test - ParentExtractor::extractParentT for if token") {}
TEST_CASE("Unit test - UsesExtractor::extractUses for while token") {}
TEST_CASE("Unit test - UsesExtractor::extractUses for if token") {}
TEST_CASE("Unit test - ModifyExtractor::extractModify for while token") {}
TEST_CASE("Unit test - ModifyExtractor::extractModify for if token") {}
TEST_CASE("Unit test - PatternExtractor::extractPattern for while token") {}
TEST_CASE("Unit test - PatternExtractor::extractPattern for if token") {}

/*
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
	SimpleToken expres = generateSimpleToken(SpTokenType::TEXPR, "1", 1);
	SimpleToken expr_1 = generateSimpleToken(SpTokenType::TCONSTANT, "1", 1);

	std::vector<SimpleToken> exprChildren;
	exprChildren.push_back(expr_1);
	expres.setChildren(exprChildren);
	std::vector<SimpleToken> assChildren;
	assChildren.push_back(varNam);
	assChildren.push_back(expres);
	assign.setChildren(assChildren);

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
	SimpleToken expres = generateSimpleToken(SpTokenType::TEXPR, "b", 1);
	SimpleToken expr_1 = generateSimpleToken(SpTokenType::TVARIABLE, "b", 1);

	std::vector<SimpleToken> exprChildren;
	exprChildren.push_back(expr_1);
	expres.setChildren(exprChildren);
	std::vector<SimpleToken> assChildren;
	assChildren.push_back(varNam);
	assChildren.push_back(expres);
	assign.setChildren(assChildren);

	AssignEntity* assignEntity = new AssignEntity("1");
	VariableEntity* variableEntity = new VariableEntity("a");
	Relationship* expectedRelationship = new ModifyRelationship(assignEntity, variableEntity);
	Relationship* generatedRelationship = testExtractor.getModifyRelationshipForAssign(assign);

	REQUIRE(equalRelationship(generatedRelationship, expectedRelationship));
	REQUIRE_NOTHROW(testExtractor.extractAssignStmt(assign));
}

TEST_CASE("Unit test - getModifyRelationshipForAssign: a = a + 1") {
	Extractor testExtractor = generateExtractor();

	SimpleToken assign = generateSimpleToken(SpTokenType::TASSIGN, "a = a + 1", 1);
	SimpleToken varNam = generateSimpleToken(SpTokenType::TVARIABLE, "a", 1);
	SimpleToken expres = generateSimpleToken(SpTokenType::TEXPR, "a + 1", 1);
	SimpleToken expr_1 = generateSimpleToken(SpTokenType::TVARIABLE, "a", 1);
	SimpleToken expr_2 = generateSimpleToken(SpTokenType::TOPR, "+", 1);
	SimpleToken expr_3 = generateSimpleToken(SpTokenType::TCONSTANT, "1", 1);

	std::vector<SimpleToken> exprChildren;
	exprChildren.push_back(expr_1);
	exprChildren.push_back(expr_2);
	exprChildren.push_back(expr_3);
	expres.setChildren(exprChildren);
	std::vector<SimpleToken> assChildren;
	assChildren.push_back(varNam);
	assChildren.push_back(expres);
	assign.setChildren(assChildren);

	AssignEntity* assignEntity = new AssignEntity("1");
	VariableEntity* variableEntity = new VariableEntity("a");
	Relationship* expectedRelationship = new ModifyRelationship(assignEntity, variableEntity);
	Relationship* generatedRelationship = testExtractor.getModifyRelationshipForAssign(assign);

	REQUIRE(equalRelationship(generatedRelationship, expectedRelationship));
	REQUIRE_NOTHROW(testExtractor.extractAssignStmt(assign));
}

TEST_CASE("Unit test - getModifyRelationshipForAssign: a = a + 1 - ( b * c )") {
	Extractor testExtractor = generateExtractor();

	SimpleToken assign = generateSimpleToken(SpTokenType::TASSIGN, "a = a + 1 - ( b * c )", 1);
	SimpleToken varNam = generateSimpleToken(SpTokenType::TVARIABLE, "a", 1);
	SimpleToken expres = generateSimpleToken(SpTokenType::TEXPR, "a + 1 - ( b * c )", 1);
	SimpleToken expr_1 = generateSimpleToken(SpTokenType::TVARIABLE, "a", 1);
	SimpleToken expr_2 = generateSimpleToken(SpTokenType::TOPR, "+", 1);
	SimpleToken expr_3 = generateSimpleToken(SpTokenType::TCONSTANT, "1", 1);
	SimpleToken expr_4 = generateSimpleToken(SpTokenType::TOPR, "-", 1);
	SimpleToken expr_5 = generateSimpleToken(SpTokenType::TVARIABLE, "b", 1);
	SimpleToken expr_6 = generateSimpleToken(SpTokenType::TOPR, "*", 1);
	SimpleToken expr_7 = generateSimpleToken(SpTokenType::TVARIABLE, "c", 1);

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

	AssignEntity* assignEntity = new AssignEntity("1");
	VariableEntity* variableEntity = new VariableEntity("a");
	Relationship* expectedRelationship = new ModifyRelationship(assignEntity, variableEntity);
	Relationship* generatedRelationship = testExtractor.getModifyRelationshipForAssign(assign);

	REQUIRE(equalRelationship(generatedRelationship, expectedRelationship));
	REQUIRE_NOTHROW(testExtractor.extractAssignStmt(assign));
}

TEST_CASE("Unit test - getUsesRelationshipForAssign: a = 1") {
	Extractor testExtractor = generateExtractor();

	SimpleToken assign = generateSimpleToken(SpTokenType::TASSIGN, "a = 1", 1);
	SimpleToken varNam = generateSimpleToken(SpTokenType::TVARIABLE, "a", 1);
	SimpleToken expres = generateSimpleToken(SpTokenType::TEXPR, "1", 1);
	SimpleToken expr_1 = generateSimpleToken(SpTokenType::TCONSTANT, "1", 1);

	std::vector<SimpleToken> exprChildren;
	exprChildren.push_back(expr_1);
	expres.setChildren(exprChildren);
	std::vector<SimpleToken> assChildren;
	assChildren.push_back(varNam);
	assChildren.push_back(expres);
	assign.setChildren(assChildren);

	std::vector<UsesRelationship*> generatedRelationships = testExtractor.getUsesRelationshipsForAssign(assign);

	REQUIRE(generatedRelationships.empty());
	REQUIRE_NOTHROW(testExtractor.extractAssignStmt(assign));
}

TEST_CASE("Unit test - getUsesRelationshipForAssign: a = b") {
	Extractor testExtractor = generateExtractor();

	SimpleToken assign = generateSimpleToken(SpTokenType::TASSIGN, "a = 1", 1);
	SimpleToken varNam = generateSimpleToken(SpTokenType::TVARIABLE, "a", 1);
	SimpleToken expres = generateSimpleToken(SpTokenType::TEXPR, "b", 1);
	SimpleToken expr_1 = generateSimpleToken(SpTokenType::TVARIABLE, "b", 1);

	std::vector<SimpleToken> exprChildren;
	exprChildren.push_back(expr_1);
	expres.setChildren(exprChildren);
	std::vector<SimpleToken> assChildren;
	assChildren.push_back(varNam);
	assChildren.push_back(expres);
	assign.setChildren(assChildren);

	AssignEntity* assignEntity = new AssignEntity("1");
	VariableEntity* variableEntity = new VariableEntity("b");
	Relationship* expectedRelationship = new UsesRelationship(assignEntity, variableEntity);
	std::vector<Relationship*> expectedRelationships;
	expectedRelationships.push_back(expectedRelationship);
	std::vector<UsesRelationship*> generatedRelationships = testExtractor.getUsesRelationshipsForAssign(assign);

	REQUIRE(generatedRelationships.size() == expectedRelationships.size());
	for (int i = 0; i < expectedRelationships.size(); i++) {
		REQUIRE(equalRelationship(expectedRelationships.at(i), generatedRelationships.at(i)));
	}
	REQUIRE_NOTHROW(testExtractor.extractAssignStmt(assign));
}

TEST_CASE("Unit test - getUsesRelationshipForAssign: a = a + 1") {
	Extractor testExtractor = generateExtractor();

	SimpleToken assign = generateSimpleToken(SpTokenType::TASSIGN, "a = a + 1", 1);
	SimpleToken varNam = generateSimpleToken(SpTokenType::TVARIABLE, "a", 1);
	SimpleToken expres = generateSimpleToken(SpTokenType::TEXPR, "a + 1", 1);
	SimpleToken expr_1 = generateSimpleToken(SpTokenType::TVARIABLE, "a", 1);
	SimpleToken expr_2 = generateSimpleToken(SpTokenType::TOPR, "+", 1);
	SimpleToken expr_3 = generateSimpleToken(SpTokenType::TCONSTANT, "1", 1);

	std::vector<SimpleToken> exprChildren;
	exprChildren.push_back(expr_1);
	exprChildren.push_back(expr_2);
	exprChildren.push_back(expr_3);
	expres.setChildren(exprChildren);
	std::vector<SimpleToken> assChildren;
	assChildren.push_back(varNam);
	assChildren.push_back(expres);
	assign.setChildren(assChildren);

	AssignEntity* assignEntity = new AssignEntity("1");
	VariableEntity* variableEntity = new VariableEntity("a");
	Relationship* expectedRelationship = new UsesRelationship(assignEntity, variableEntity);
	std::vector<Relationship*> expectedRelationships;
	expectedRelationships.push_back(expectedRelationship);
	std::vector<UsesRelationship*> generatedRelationships = testExtractor.getUsesRelationshipsForAssign(assign);

	REQUIRE(generatedRelationships.size() == expectedRelationships.size());
	for (int i = 0; i < expectedRelationships.size(); i++) {
		REQUIRE(equalRelationship(expectedRelationships.at(i), generatedRelationships.at(i)));
	}
	REQUIRE_NOTHROW(testExtractor.extractAssignStmt(assign));
}

TEST_CASE("Unit test - getUsesRelationshipForAssign: a = a + 1 - ( b * c )") {
	Extractor testExtractor = generateExtractor();

	SimpleToken assign = generateSimpleToken(SpTokenType::TASSIGN, "a = a + 1 - ( b * c )", 1);
	SimpleToken varNam = generateSimpleToken(SpTokenType::TVARIABLE, "a", 1);
	SimpleToken expres = generateSimpleToken(SpTokenType::TEXPR, "a + 1 - ( b * c )", 1);
	SimpleToken expr_1 = generateSimpleToken(SpTokenType::TVARIABLE, "a", 1);
	SimpleToken expr_2 = generateSimpleToken(SpTokenType::TOPR, "+", 1);
	SimpleToken expr_3 = generateSimpleToken(SpTokenType::TCONSTANT, "1", 1);
	SimpleToken expr_4 = generateSimpleToken(SpTokenType::TOPR, "-", 1);
	SimpleToken expr_5 = generateSimpleToken(SpTokenType::TVARIABLE, "b", 1);
	SimpleToken expr_6 = generateSimpleToken(SpTokenType::TOPR, "*", 1);
	SimpleToken expr_7 = generateSimpleToken(SpTokenType::TVARIABLE, "c", 1);

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

	AssignEntity* assignEntity = new AssignEntity("1");
	VariableEntity* variableEntity_1 = new VariableEntity("a");
	VariableEntity* variableEntity_2 = new VariableEntity("b");
	VariableEntity* variableEntity_3 = new VariableEntity("c");
	Relationship* expectedRelationship_1 = new UsesRelationship(assignEntity, variableEntity_1);
	Relationship* expectedRelationship_2 = new UsesRelationship(assignEntity, variableEntity_2);
	Relationship* expectedRelationship_3 = new UsesRelationship(assignEntity, variableEntity_3);
	std::vector<Relationship*> expectedRelationships;
	expectedRelationships.push_back(expectedRelationship_1);
	expectedRelationships.push_back(expectedRelationship_2);
	expectedRelationships.push_back(expectedRelationship_3);
	std::vector<UsesRelationship*> generatedRelationships = testExtractor.getUsesRelationshipsForAssign(assign);

	REQUIRE(generatedRelationships.size() == expectedRelationships.size());
	for (int i = 0; i < expectedRelationships.size(); i++) {
		REQUIRE(equalRelationship(expectedRelationships.at(i), generatedRelationships.at(i)));
	}
	REQUIRE_NOTHROW(testExtractor.extractAssignStmt(assign));
}

TEST_CASE("Integration test - extractProcedure (basic)") {
	Extractor testExtractor = generateExtractor();

	SimpleToken procedure  = generateSimpleToken(SpTokenType::TPROCEDURE, "proc", 1);
	SimpleToken readStmt   = generateSimpleToken(SpTokenType::TREAD, "read a", 2);
	SimpleToken printStmt  = generateSimpleToken(SpTokenType::TPRINT, "print a", 3);
	SimpleToken assignStmt = generateSimpleToken(SpTokenType::TASSIGN, "a = a + 1", 4);
	SimpleToken whileStmt  = generateSimpleToken(SpTokenType::TWHILE, "", 5);
	SimpleToken ifStmt     = generateSimpleToken(SpTokenType::TIF, "", 7);
}

TEST_CASE("Integration test - extractParentRelationships") {}
TEST_CASE("Integration test - extractFollowsRelationships") {}
TEST_CASE("Integration test - extractSeriesOfStmts") {}
TEST_CASE("Integration test - extractWhileStmt") {}
TEST_CASE("Integration test - extractIfStmt") {}
TEST_CASE("Integration test - extractStmtLst") {}

TEST_CASE("extractCondExpr") {}

TEST_CASE("extractCall") {}
*/
