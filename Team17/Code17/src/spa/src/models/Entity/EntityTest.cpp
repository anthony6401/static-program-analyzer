#include "AssignEntity.h"
#include "CallEntity.h"
#include "ConstantEntity.h"
#include "Entity.h"
#include "IfEntity.h"
#include "PrintEntity.h"
#include "ProcedureEntity.h"
#include "ReadEntity.h"
#include "StatementEntity.h"
#include "StatementListEntity.h"
#include "VariableEntity.h"
#include "WhileEntity.h"

#include <catch.hpp>

std::string VALUE = "1";

//Parent Class
TEST_CASE("Entity Test") {
	Entity e = Entity(VALUE);

	REQUIRE(e.getValue() == "1");
	
}

//Child of Entity
TEST_CASE("Procedure Test") {
	ProcedureEntity p = ProcedureEntity(VALUE);

	REQUIRE(p.getValue() == "1");

}

