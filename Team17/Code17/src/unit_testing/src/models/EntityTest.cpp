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
	Entity e = Entity(VALUE);
	REQUIRE(p.getValue() == "1");
	REQUIRE(e == p);

}

TEST_CASE("Assign Entity Test") {
	AssignEntity a = AssignEntity(VALUE);
	Entity e = Entity(VALUE);

	REQUIRE(a.getValue() == "1");
	REQUIRE(e == a);
}

TEST_CASE("Call Entity Test") {
	CallEntity c = CallEntity(VALUE);
	Entity e = Entity(VALUE);

	REQUIRE(c.getValue() == "1");
	REQUIRE(e == c);
}

TEST_CASE("Constant Entity Test") {
	ConstantEntity ct = ConstantEntity(VALUE);
	Entity e = Entity(VALUE);

	REQUIRE(ct.getValue() == "1");
	REQUIRE(e == ct);
}

TEST_CASE("Variable Entity Test") {
	VariableEntity v = VariableEntity(VALUE);
	Entity e = Entity(VALUE);

	REQUIRE(v.getValue() == "1");
	REQUIRE(e == v);

}

//Statement Entity
TEST_CASE("Statement Entity Test") {
	StatementEntity st = StatementEntity(VALUE);
	Entity e = Entity(VALUE);

	REQUIRE(st.getValue() == "1");
	REQUIRE(e == st);
}

// Child of Statement Entity
TEST_CASE("If Entity Test") {
	IfEntity i = IfEntity(VALUE);
	Entity e = Entity(VALUE);
	StatementEntity st = StatementEntity(VALUE);

	REQUIRE(i.getValue() == "1");
	REQUIRE(e == i);
	REQUIRE(st == i);

}

TEST_CASE("Print Entity Test") {
	PrintEntity pr = PrintEntity(VALUE);
	Entity e = Entity(VALUE);
	StatementEntity st = StatementEntity(VALUE);

	REQUIRE(pr.getValue() == "1");
	REQUIRE(e == pr);
	REQUIRE(st == pr);

}

TEST_CASE("Read Entity Test") {
	ReadEntity rd = ReadEntity(VALUE);
	Entity e = Entity(VALUE);
	StatementEntity st = StatementEntity(VALUE);

	REQUIRE(rd.getValue() == "1");
	REQUIRE(e == rd);
	REQUIRE(st == rd);


}

TEST_CASE("While Entity Test") {
	WhileEntity w = WhileEntity(VALUE);
	Entity e = Entity(VALUE);
	StatementEntity st = StatementEntity(VALUE);

	REQUIRE(w.getValue() == "1");
	REQUIRE(e == w);
	REQUIRE(st == w);

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

