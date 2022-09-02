#pragma once

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


#include "components/pkb/manager/EntityManager.h"

#include <catch.hpp>

std::string value = "value";

Entity* entity_new = new Entity(value);
Entity* assignEntity_new = new AssignEntity(value);
Entity* callEntity_new = new CallEntity(value);
Entity* constantEntity_new = new ConstantEntity(value);
Entity* ifEntity_new = new IfEntity(value);
Entity* printEntity_new = new PrintEntity(value);
Entity* procedureEntity_new = new ProcedureEntity(value);
Entity* readEntity_new = new ReadEntity(value);
Entity* variableEntity_new = new VariableEntity(value);
Entity* whileEntity_new = new WhileEntity(value);

Entity* assignEntity_dup = new AssignEntity(value);

//Test for EntityManager::storeEntity()
TEST_CASE("Entity Manager storing method test") {
	EntityManager entityManager = EntityManager();

	//Storing test cases
	REQUIRE(entityManager.storeEntity(assignEntity_new));
	REQUIRE(entityManager.storeEntity(callEntity_new));
	REQUIRE(entityManager.storeEntity(constantEntity_new));
	REQUIRE(entityManager.storeEntity(ifEntity_new));
	REQUIRE(entityManager.storeEntity(printEntity_new));
	REQUIRE(entityManager.storeEntity(procedureEntity_new));
	REQUIRE(entityManager.storeEntity(readEntity_new));
	REQUIRE(entityManager.storeEntity(variableEntity_new));
	REQUIRE(entityManager.storeEntity(whileEntity_new));
	




}