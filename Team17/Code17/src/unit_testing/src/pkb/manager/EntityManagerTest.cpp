#pragma once

#include "models/Entity/AssignEntity.h"
#include "models/Entity/CallEntity.h"
#include "models/Entity/ConstantEntity.h"
#include "models/Entity/DesignEntity.h"
#include "models/Entity/Entity.h"
#include "models/Entity/IfEntity.h"
#include "models/Entity/PrintEntity.h"
#include "models/Entity/ProcedureEntity.h"
#include "models/Entity/ReadEntity.h"
#include "models/Entity/StatementEntity.h"
#include "models/Entity/StatementListEntity.h"
#include "models/Entity/VariableEntity.h"
#include "models/Entity/WhileEntity.h"

#include "../EntityObject.h"

#include "components/pkb/manager/EntityManager.h"

#include <catch.hpp>

//Test for EntityManager::storeEntity()
TEST_CASE("Entity Manager storing method test") {
	EntityManager entityManager = EntityManager();

	//Storing test cases
	REQUIRE(entityManager.storeEntity(assignEntity));
	REQUIRE(entityManager.storeEntity(callEntity));
	REQUIRE(entityManager.storeEntity(constantEntity));
	REQUIRE(entityManager.storeEntity(ifEntity));
	REQUIRE(entityManager.storeEntity(printEntity));
	REQUIRE(entityManager.storeEntity(procedureEntity));
	REQUIRE(entityManager.storeEntity(readEntity));
	REQUIRE(entityManager.storeEntity(variableEntity));
	REQUIRE(entityManager.storeEntity(whileEntity));
	
}

//Test for gettting all entity methods
TEST_CASE("Entity Manager getAllEntity method test") {
	EntityManager entityManager = EntityManager();

	//Storing test cases
	entityManager.storeEntity(assignEntity);
	entityManager.storeEntity(callEntity);
	entityManager.storeEntity(constantEntity);
	entityManager.storeEntity(ifEntity);
	entityManager.storeEntity(printEntity);
	entityManager.storeEntity(procedureEntity);
	entityManager.storeEntity(readEntity);
	entityManager.storeEntity(variableEntity);
	entityManager.storeEntity(whileEntity);

	std::unordered_set<std::string> assign_res{ assign_value_one };
	std::unordered_set<std::string> call_res{ call_value_one };
	std::unordered_set<std::string> constant_res{ constant_value_one };
	std::unordered_set<std::string> if_res{ if_value_one };
	std::unordered_set<std::string> print_res{ print_value_one };
	std::unordered_set<std::string> procedure_res{ procedure_value_one };
	std::unordered_set<std::string> read_res{ read_value_one };
	std::unordered_set<std::string> variable_res{ variable_value_one };
	std::unordered_set<std::string> while_res{ while_value_one };

	std::unordered_set<std::string> ass_test = entityManager.getAllEntity(DesignEntity::ASSIGN);
	std::unordered_set<std::string> call_test = entityManager.getAllEntity(DesignEntity::CALL);
	std::unordered_set<std::string> constant_test = entityManager.getAllEntity(DesignEntity::CONSTANT);
	std::unordered_set<std::string> if_test = entityManager.getAllEntity(DesignEntity::IF);
	std::unordered_set<std::string> print_test = entityManager.getAllEntity(DesignEntity::PRINT);
	std::unordered_set<std::string> procedure_test = entityManager.getAllEntity(DesignEntity::PROCEDURE);
	std::unordered_set<std::string> read_test = entityManager.getAllEntity(DesignEntity::READ);
	std::unordered_set<std::string> variable_test = entityManager.getAllEntity(DesignEntity::VARIABLE);
	std::unordered_set<std::string> while_test = entityManager.getAllEntity(DesignEntity::WHILE);
	

	REQUIRE(ass_test == assign_res);
	REQUIRE(call_test == call_res);
	REQUIRE(constant_test == constant_res);
	REQUIRE(if_test == if_test);
	REQUIRE(print_test == print_res);
	REQUIRE(procedure_test == procedure_res);
	REQUIRE(read_test == read_res);
	REQUIRE(variable_test == variable_res);
	REQUIRE(while_test == while_res);

	std::string callMappingResult = procedure_value_one;
	std::string printMappingResult = variable_value_one;
	std::string readMappingResult = variable_value_one;

	std::string callMappingTest = entityManager.getStatementMapping(call_value_one, DesignEntity::CALL);
	std::string printMappingTest = entityManager.getStatementMapping(print_value_one, DesignEntity::PRINT);
	std::string readMappingTest = entityManager.getStatementMapping(read_value_one, DesignEntity::READ);

	REQUIRE(callMappingTest == callMappingResult);
	REQUIRE(printMappingTest == printMappingResult);
	REQUIRE(readMappingTest == readMappingResult);

	std::unordered_set<std::string> callGetStmtByNameTest = entityManager.getStatementByName(procedure_value_one, DesignEntity::CALL);
	std::unordered_set<std::string> printGetStmgByNameTest = entityManager.getStatementByName(variable_value_one, DesignEntity::PRINT);
	std::unordered_set<std::string> readGetStmtByNameTest = entityManager.getStatementByName(variable_value_one, DesignEntity::READ);

	std::unordered_set<std::string> callStmtByNameExpectedResult({ call_value_one });
	std::unordered_set<std::string> printStmtByNameExpectedResult({ print_value_one });
	std::unordered_set<std::string> readStmtByNameExpectedResult({ read_value_one });

	REQUIRE(callGetStmtByNameTest == callStmtByNameExpectedResult);
	REQUIRE(printGetStmgByNameTest == printStmtByNameExpectedResult);
	REQUIRE(readGetStmtByNameTest == readStmtByNameExpectedResult);
}
