#include "models/Entity/AssignEntity.h"
#include "models/Entity/CallEntity.h"
#include "models/Entity/ConstantEntity.h"
#include "models/Entity/Entity.h"
#include "models/Entity/IfEntity.h"
#include "models/Entity/PrintEntity.h"
#include "models/Entity/ProcedureEntity.h"
#include "models/Entity/ReadEntity.h"
#include "models/Entity/StatementEntity.h"
#include "models/Entity/StatementListEntity.h"
#include "models/Entity/VariableEntity.h"
#include "models/Entity/WhileEntity.h"

#include <catch.hpp>

#include <vector>

std::string VALUE = "1";

//Parent Class
TEST_CASE("Entity Test") {
	Entity e = Entity(VALUE);

	REQUIRE(e.getValue() == "1");
	
}

//Child of Entity
TEST_CASE("Procedure Entity Test") {
	ProcedureEntity p = ProcedureEntity(VALUE);

	REQUIRE(p.getValue() == "1");

}

TEST_CASE("Assign Entity Test") {
	AssignEntity a = AssignEntity(VALUE);

	REQUIRE(a.getValue() == "1");

}

TEST_CASE("Call Entity Test") {
	CallEntity c = CallEntity(VALUE);

	REQUIRE(c.getValue() == "1");

}

TEST_CASE("Constant Entity Test") {
	ConstantEntity ct = ConstantEntity(VALUE);

	REQUIRE(ct.getValue() == "1");

}

TEST_CASE("Variable Entity Test") {
	VariableEntity v = VariableEntity(VALUE);

	REQUIRE(v.getValue() == "1");

}

//Statement Entity
TEST_CASE("Statement Entity Test") {
	StatementEntity st = StatementEntity(VALUE);

	REQUIRE(st.getValue() == "1");

}

// Child of Statement Entity
TEST_CASE("If Entity Test") {
	IfEntity i = IfEntity(VALUE);

	REQUIRE(i.getValue() == "1");

}

TEST_CASE("Print Entity Test") {
	PrintEntity pr = PrintEntity(VALUE);

	REQUIRE(pr.getValue() == "1");

}

TEST_CASE("Read Entity Test") {
	ReadEntity rd = ReadEntity(VALUE);

	REQUIRE(rd.getValue() == "1");

}

TEST_CASE("While Entity Test") {
	WhileEntity w = WhileEntity(VALUE);

	REQUIRE(w.getValue() == "1");

}

//TODO:NEED TO TEST STATEMENTLISTENTITY
//StatementList
TEST_CASE("StatementList Entity Test") {
	StatementEntity st1 = StatementEntity("1");
	StatementEntity st2 = StatementEntity("2");

	std::vector<StatementEntity> statements{ st1, st2 };

	StatementListEntity stmtLst1 = StatementListEntity(statements);
	StatementListEntity stmtLst2 = StatementListEntity(std::vector<StatementEntity> { st1, st2 });
	

	REQUIRE(stmtLst1 == stmtLst2);

}

