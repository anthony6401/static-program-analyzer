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

#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"

#include "components/pkb/manager/EntityManager.h"

#include <catch.hpp>

std::string entity_value = "entity_value";
std::string assign_value = "assign_value";
std::string call_value = "call_value";
std::string constant_value = "constant_value";
std::string if_value = "if_value";
std::string print_value = "print_value";
std::string procedure_value = "procedure_value";
std::string read_value = "read_value";
std::string variable_value = "variable_value";
std::string while_value = "while_value";


Entity* entity_new = new Entity(entity_value);
Entity* assignEntity_new = new AssignEntity(assign_value);
Entity* callEntity_new = new CallEntity(call_value);
Entity* constantEntity_new = new ConstantEntity(constant_value);
Entity* ifEntity_new = new IfEntity(if_value);
Entity* printEntity_new = new PrintEntity(print_value);
Entity* procedureEntity_new = new ProcedureEntity(procedure_value);
Entity* readEntity_new = new ReadEntity(read_value);
Entity* variableEntity_new = new VariableEntity(variable_value);
Entity* whileEntity_new = new WhileEntity(while_value);


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

//Test for gettting all entity methods
TEST_CASE("Entity Manager getAllEntity method test") {
	EntityManager entityManager = EntityManager();

	//Storing test cases
	entityManager.storeEntity(assignEntity_new);
	entityManager.storeEntity(callEntity_new);
	entityManager.storeEntity(constantEntity_new);
	entityManager.storeEntity(ifEntity_new);
	entityManager.storeEntity(printEntity_new);
	entityManager.storeEntity(procedureEntity_new);
	entityManager.storeEntity(readEntity_new);
	entityManager.storeEntity(variableEntity_new);
	entityManager.storeEntity(whileEntity_new);

	std::vector<std::string> assign_res{ assign_value };
	std::vector<std::string> call_res{ call_value };
	std::vector<std::string> constant_res{ constant_value };
	std::vector<std::string> if_res{ if_value };
	std::vector<std::string> print_res{ print_value };
	std::vector<std::string> procedure_res{ procedure_value };
	std::vector<std::string> read_res{ read_value };
	std::vector<std::string> variable_res{ variable_value };
	std::vector<std::string> while_res{ while_value };

	std::vector<std::string> ass_test = entityManager.getAllEntity(qps::TokenType::ASSIGN);
	std::vector<std::string> call_test = entityManager.getAllEntity(qps::TokenType::CALL);
	std::vector<std::string> constant_test = entityManager.getAllEntity(qps::TokenType::CONSTANT);
	std::vector<std::string> if_test = entityManager.getAllEntity(qps::TokenType::IF);
	std::vector<std::string> print_test = entityManager.getAllEntity(qps::TokenType::PRINT);
	std::vector<std::string> procedure_test = entityManager.getAllEntity(qps::TokenType::PROCEDURE);
	std::vector<std::string> read_test = entityManager.getAllEntity(qps::TokenType::READ);
	std::vector<std::string> variable_test = entityManager.getAllEntity(qps::TokenType::VARIABLE);
	std::vector<std::string> while_test = entityManager.getAllEntity(qps::TokenType::WHILE);
	

	REQUIRE(ass_test == assign_res);
	REQUIRE(call_test == call_res);
	REQUIRE(constant_test == constant_res);
	REQUIRE(if_test == if_test);
	REQUIRE(print_test == print_res);
	REQUIRE(procedure_test == procedure_res);
	REQUIRE(read_test == read_res);
	REQUIRE(variable_test == variable_res);
	REQUIRE(while_test == while_res);
}
