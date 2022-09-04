#include <catch.hpp>
#include "../EntityObject.h"
#include "components/pkb/storage/EntityStorage.h"
#include "components/pkb/storage/AssignEntityStorage.h"
#include "components/pkb/storage/CallEntityStorage.h"
#include "components/pkb/storage/ConstantEntityStorage.h"
#include "components/pkb/storage/EntityStorage.h"
#include "components/pkb/storage/IfEntityStorage.h"
#include "components/pkb/storage/PrintEntityStorage.h"
#include "components/pkb/storage/ProcedureEntityStorage.h"
#include "components/pkb/storage/ReadEntityStorage.h"
#include "components/pkb/storage/VariableEntityStorage.h"
#include "components/pkb/storage/StatementEntityStorage.h"
#include "components/pkb/storage/WhileEntityStorage.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"

TEST_CASE("Assign Entity Storage Test") {
	EntityStorage* assignEntityStorage = new AssignEntityStorage();

	// Storing correct entity
	REQUIRE(assignEntityStorage->storeEntity(assignEntity));
	
	// Storing incorrect entities
	REQUIRE(!assignEntityStorage->storeEntity(entity));
	REQUIRE(!assignEntityStorage->storeEntity(constantEntity));
	REQUIRE(!assignEntityStorage->storeEntity(callEntity));
	REQUIRE(!assignEntityStorage->storeEntity(ifEntity));
	REQUIRE(!assignEntityStorage->storeEntity(printEntity));
	REQUIRE(!assignEntityStorage->storeEntity(procedureEntity));
	REQUIRE(!assignEntityStorage->storeEntity(readEntity));
	REQUIRE(!assignEntityStorage->storeEntity(variableEntity));
	REQUIRE(!assignEntityStorage->storeEntity(whileEntity));

	// Check size to make sure only the correct entity is stored
	REQUIRE(assignEntityStorage->getSize() == 1);

	// Storing second correct entity
	REQUIRE(assignEntityStorage->storeEntity(assignEntityTwo));

	// Check size to make sure both of the correct entities is stored
	REQUIRE(assignEntityStorage->getSize() == 2);

	// Get Set based on TokenType
	std::unordered_set<Entity*>* assignSet = assignEntityStorage->getAllEntity(qps::TokenType::ASSIGN);
	std::unordered_set<Entity*>* constantSet = assignEntityStorage->getAllEntity(qps::TokenType::CONSTANT);
	std::unordered_set<Entity*>* callSet = assignEntityStorage->getAllEntity(qps::TokenType::CALL);
	std::unordered_set<Entity*>* ifSet = assignEntityStorage->getAllEntity(qps::TokenType::IF);
	std::unordered_set<Entity*>* printSet = assignEntityStorage->getAllEntity(qps::TokenType::PRINT);
	std::unordered_set<Entity*>* procedureSet = assignEntityStorage->getAllEntity(qps::TokenType::PROCEDURE);
	std::unordered_set<Entity*>* readSet = assignEntityStorage->getAllEntity(qps::TokenType::READ);
	std::unordered_set<Entity*>* variableSet = assignEntityStorage->getAllEntity(qps::TokenType::VARIABLE);
	std::unordered_set<Entity*>* whileSet = assignEntityStorage->getAllEntity(qps::TokenType::WHILE);
	std::unordered_set<Entity*>* stmtSet = assignEntityStorage->getAllEntity(qps::TokenType::STMT);

	// Correct TokenType should return the set instead of nullptr
	REQUIRE(assignSet != nullptr);

	// Incorrect TokenType should return nullptr instead of the set
	REQUIRE(constantSet == nullptr);
	REQUIRE(callSet == nullptr);
	REQUIRE(ifSet == nullptr);
	REQUIRE(printSet == nullptr);
	REQUIRE(procedureSet == nullptr);
	REQUIRE(readSet == nullptr);
	REQUIRE(variableSet == nullptr);
	REQUIRE(whileSet == nullptr);
	REQUIRE(stmtSet == nullptr);

	// Retreiving entities from the storage
	REQUIRE(assignSet->find(assignEntity) != assignSet->end());
	REQUIRE(assignSet->find(assignEntityTwo) != assignSet->end());
	REQUIRE(assignSet->find(assignEntityThree) == assignSet->end());

}

TEST_CASE("Constant Entity Storage Test") {
	EntityStorage* constantEntityStorage = new ConstantEntityStorage();

	// Storing correct entity
	REQUIRE(constantEntityStorage->storeEntity(constantEntity));

	// Storing incorrect entities
	REQUIRE(!constantEntityStorage->storeEntity(entity));
	REQUIRE(!constantEntityStorage->storeEntity(assignEntity));
	REQUIRE(!constantEntityStorage->storeEntity(callEntity));
	REQUIRE(!constantEntityStorage->storeEntity(ifEntity));
	REQUIRE(!constantEntityStorage->storeEntity(printEntity));
	REQUIRE(!constantEntityStorage->storeEntity(procedureEntity));
	REQUIRE(!constantEntityStorage->storeEntity(readEntity));
	REQUIRE(!constantEntityStorage->storeEntity(variableEntity));
	REQUIRE(!constantEntityStorage->storeEntity(whileEntity));

	// Check size to make sure only the correct entity is stored
	REQUIRE(constantEntityStorage->getSize() == 1);

	// Storing second correct entity
	REQUIRE(constantEntityStorage->storeEntity(constantEntityTwo));

	// Check size to make sure both of the correct entities is stored
	REQUIRE(constantEntityStorage->getSize() == 2);

	// Get Set based on TokenType
	std::unordered_set<Entity*>* assignSet = constantEntityStorage->getAllEntity(qps::TokenType::ASSIGN);
	std::unordered_set<Entity*>* constantSet = constantEntityStorage->getAllEntity(qps::TokenType::CONSTANT);
	std::unordered_set<Entity*>* callSet = constantEntityStorage->getAllEntity(qps::TokenType::CALL);
	std::unordered_set<Entity*>* ifSet = constantEntityStorage->getAllEntity(qps::TokenType::IF);
	std::unordered_set<Entity*>* printSet = constantEntityStorage->getAllEntity(qps::TokenType::PRINT);
	std::unordered_set<Entity*>* procedureSet = constantEntityStorage->getAllEntity(qps::TokenType::PROCEDURE);
	std::unordered_set<Entity*>* readSet = constantEntityStorage->getAllEntity(qps::TokenType::READ);
	std::unordered_set<Entity*>* variableSet = constantEntityStorage->getAllEntity(qps::TokenType::VARIABLE);
	std::unordered_set<Entity*>* whileSet = constantEntityStorage->getAllEntity(qps::TokenType::WHILE);
	std::unordered_set<Entity*>* stmtSet = constantEntityStorage->getAllEntity(qps::TokenType::STMT);

	// Correct TokenType should return the set instead of nullptr
	REQUIRE(constantSet != nullptr);

	// Incorrect TokenType should return nullptr instead of the set
	REQUIRE(assignSet == nullptr);
	REQUIRE(callSet == nullptr);
	REQUIRE(ifSet == nullptr);
	REQUIRE(printSet == nullptr);
	REQUIRE(procedureSet == nullptr);
	REQUIRE(readSet == nullptr);
	REQUIRE(variableSet == nullptr);
	REQUIRE(whileSet == nullptr);
	REQUIRE(stmtSet == nullptr);

	// Retreiving entities from the storage
	REQUIRE(constantSet->find(constantEntity) != constantSet->end());
	REQUIRE(constantSet->find(constantEntityTwo) != constantSet->end());
	REQUIRE(constantSet->find(constantEntityThree) == constantSet->end());
}

TEST_CASE("Call Entity Storage Test") {
	EntityStorage* callEntityStorage = new CallEntityStorage();

	// Storing the correct entity
	REQUIRE(callEntityStorage->storeEntity(callEntity));

	// Storing incorrect entities
	REQUIRE(!callEntityStorage->storeEntity(entity));
	REQUIRE(!callEntityStorage->storeEntity(assignEntity));
	REQUIRE(!callEntityStorage->storeEntity(constantEntity));
	REQUIRE(!callEntityStorage->storeEntity(ifEntity));
	REQUIRE(!callEntityStorage->storeEntity(printEntity));
	REQUIRE(!callEntityStorage->storeEntity(procedureEntity));
	REQUIRE(!callEntityStorage->storeEntity(readEntity));
	REQUIRE(!callEntityStorage->storeEntity(variableEntity));
	REQUIRE(!callEntityStorage->storeEntity(whileEntity));

	// Check size to make sure only the correct entity is stored
	REQUIRE(callEntityStorage->getSize() == 1);

	// Storing second correct entity
	REQUIRE(callEntityStorage->storeEntity(callEntityTwo));

	// Check size to make sure both of the correct entities is stored
	REQUIRE(callEntityStorage->getSize() == 2);

	// Get Set based on TokenType
	std::unordered_set<Entity*>* assignSet = callEntityStorage->getAllEntity(qps::TokenType::ASSIGN);
	std::unordered_set<Entity*>* constantSet = callEntityStorage->getAllEntity(qps::TokenType::CONSTANT);
	std::unordered_set<Entity*>* callSet = callEntityStorage->getAllEntity(qps::TokenType::CALL);
	std::unordered_set<Entity*>* ifSet = callEntityStorage->getAllEntity(qps::TokenType::IF);
	std::unordered_set<Entity*>* printSet = callEntityStorage->getAllEntity(qps::TokenType::PRINT);
	std::unordered_set<Entity*>* procedureSet = callEntityStorage->getAllEntity(qps::TokenType::PROCEDURE);
	std::unordered_set<Entity*>* readSet = callEntityStorage->getAllEntity(qps::TokenType::READ);
	std::unordered_set<Entity*>* variableSet = callEntityStorage->getAllEntity(qps::TokenType::VARIABLE);
	std::unordered_set<Entity*>* whileSet = callEntityStorage->getAllEntity(qps::TokenType::WHILE);
	std::unordered_set<Entity*>* stmtSet = callEntityStorage->getAllEntity(qps::TokenType::STMT);

	// Correct TokenType should return the set instead of nullptr
	REQUIRE(callSet != nullptr);

	// Incorrect TokenType should return nullptr instead of the set
	REQUIRE(assignSet == nullptr);
	REQUIRE(constantSet == nullptr);
	REQUIRE(ifSet == nullptr);
	REQUIRE(printSet == nullptr);
	REQUIRE(procedureSet == nullptr);
	REQUIRE(readSet == nullptr);
	REQUIRE(variableSet == nullptr);
	REQUIRE(whileSet == nullptr);
	REQUIRE(stmtSet == nullptr);

	// Retreiving entities from the storage
	REQUIRE(callSet->find(callEntity) != callSet->end());
	REQUIRE(callSet->find(callEntityTwo) != callSet->end());
	REQUIRE(callSet->find(callEntityThree) == callSet->end());
}

TEST_CASE("If Entity Storage Test") {
	EntityStorage* ifEntityStorage = new IfEntityStorage();

	// Storing the correct entity
	REQUIRE(ifEntityStorage->storeEntity(ifEntity));

	// Storing incorrect entities
	REQUIRE(!ifEntityStorage->storeEntity(entity));
	REQUIRE(!ifEntityStorage->storeEntity(assignEntity));
	REQUIRE(!ifEntityStorage->storeEntity(constantEntity));
	REQUIRE(!ifEntityStorage->storeEntity(callEntity));
	REQUIRE(!ifEntityStorage->storeEntity(printEntity));
	REQUIRE(!ifEntityStorage->storeEntity(procedureEntity));
	REQUIRE(!ifEntityStorage->storeEntity(readEntity));
	REQUIRE(!ifEntityStorage->storeEntity(variableEntity));
	REQUIRE(!ifEntityStorage->storeEntity(whileEntity));

	// Check size to make sure only the correct entity is stored
	REQUIRE(ifEntityStorage->getSize() == 1);

	// Storing second correct entity
	REQUIRE(ifEntityStorage->storeEntity(ifEntityTwo));


	// Check size to make sure both of the correct entities is stored
	REQUIRE(ifEntityStorage->getSize() == 2);

	// Get Set based on TokenType
	std::unordered_set<Entity*>* assignSet = ifEntityStorage->getAllEntity(qps::TokenType::ASSIGN);
	std::unordered_set<Entity*>* constantSet = ifEntityStorage->getAllEntity(qps::TokenType::CONSTANT);
	std::unordered_set<Entity*>* callSet = ifEntityStorage->getAllEntity(qps::TokenType::CALL);
	std::unordered_set<Entity*>* ifSet = ifEntityStorage->getAllEntity(qps::TokenType::IF);
	std::unordered_set<Entity*>* printSet = ifEntityStorage->getAllEntity(qps::TokenType::PRINT);
	std::unordered_set<Entity*>* procedureSet = ifEntityStorage->getAllEntity(qps::TokenType::PROCEDURE);
	std::unordered_set<Entity*>* readSet = ifEntityStorage->getAllEntity(qps::TokenType::READ);
	std::unordered_set<Entity*>* variableSet = ifEntityStorage->getAllEntity(qps::TokenType::VARIABLE);
	std::unordered_set<Entity*>* whileSet = ifEntityStorage->getAllEntity(qps::TokenType::WHILE);
	std::unordered_set<Entity*>* stmtSet = ifEntityStorage->getAllEntity(qps::TokenType::STMT);

	// Correct TokenType should return the set instead of nullptr
	REQUIRE(ifSet != nullptr);

	// Incorrect TokenType should return nullptr instead of the set
	REQUIRE(assignSet == nullptr);
	REQUIRE(constantSet == nullptr);
	REQUIRE(callSet == nullptr);
	REQUIRE(printSet == nullptr);
	REQUIRE(procedureSet == nullptr);
	REQUIRE(readSet == nullptr);
	REQUIRE(variableSet == nullptr);
	REQUIRE(whileSet == nullptr);
	REQUIRE(stmtSet == nullptr);

	// Retreiving entities from the storage
	REQUIRE(ifSet->find(ifEntity) != ifSet->end());
	REQUIRE(ifSet->find(ifEntityTwo) != ifSet->end());
	REQUIRE(ifSet->find(ifEntityThree) == ifSet->end());
}

TEST_CASE("print Entity Storage Test") {
	EntityStorage* printEntityStorage = new PrintEntityStorage();

	// Storing the correct entity
	REQUIRE(printEntityStorage->storeEntity(printEntity));

	// Storing incorrect entities
	REQUIRE(!printEntityStorage->storeEntity(entity));
	REQUIRE(!printEntityStorage->storeEntity(assignEntity));
	REQUIRE(!printEntityStorage->storeEntity(constantEntity));
	REQUIRE(!printEntityStorage->storeEntity(callEntity));
	REQUIRE(!printEntityStorage->storeEntity(ifEntity));
	REQUIRE(!printEntityStorage->storeEntity(procedureEntity));
	REQUIRE(!printEntityStorage->storeEntity(readEntity));
	REQUIRE(!printEntityStorage->storeEntity(variableEntity));
	REQUIRE(!printEntityStorage->storeEntity(whileEntity));

	// Check size to make sure only the correct entity is stored
	REQUIRE(printEntityStorage->getSize() == 1);

	// Storing second correct entity
	REQUIRE(printEntityStorage->storeEntity(printEntityTwo));

	// Check size to make sure both of the correct entities is stored
	REQUIRE(printEntityStorage->getSize() == 2);

	// Get Set based on TokenType
	std::unordered_set<Entity*>* assignSet = printEntityStorage->getAllEntity(qps::TokenType::ASSIGN);
	std::unordered_set<Entity*>* constantSet = printEntityStorage->getAllEntity(qps::TokenType::CONSTANT);
	std::unordered_set<Entity*>* callSet = printEntityStorage->getAllEntity(qps::TokenType::CALL);
	std::unordered_set<Entity*>* ifSet = printEntityStorage->getAllEntity(qps::TokenType::IF);
	std::unordered_set<Entity*>* printSet = printEntityStorage->getAllEntity(qps::TokenType::PRINT);
	std::unordered_set<Entity*>* procedureSet = printEntityStorage->getAllEntity(qps::TokenType::PROCEDURE);
	std::unordered_set<Entity*>* readSet = printEntityStorage->getAllEntity(qps::TokenType::READ);
	std::unordered_set<Entity*>* variableSet = printEntityStorage->getAllEntity(qps::TokenType::VARIABLE);
	std::unordered_set<Entity*>* whileSet = printEntityStorage->getAllEntity(qps::TokenType::WHILE);
	std::unordered_set<Entity*>* stmtSet = printEntityStorage->getAllEntity(qps::TokenType::STMT);

	// Correct TokenType should return the set instead of nullptr
	REQUIRE(printSet != nullptr);

	// Incorrect TokenType should return nullptr instead of the set
	REQUIRE(assignSet == nullptr);
	REQUIRE(constantSet == nullptr);
	REQUIRE(callSet == nullptr);
	REQUIRE(ifSet == nullptr);
	REQUIRE(procedureSet == nullptr);
	REQUIRE(readSet == nullptr);
	REQUIRE(variableSet == nullptr);
	REQUIRE(whileSet == nullptr);
	REQUIRE(stmtSet == nullptr);

	// Retreiving entities from the storage
	REQUIRE(printSet->find(printEntity) != printSet->end());
	REQUIRE(printSet->find(printEntityTwo) != printSet->end());
	REQUIRE(printSet->find(printEntityThree) == printSet->end());
}

TEST_CASE("Procedure Entity Storage Test") {
	EntityStorage* procedureEntityStorage = new ProcedureEntityStorage();

	// Storing the correct entity
	REQUIRE(procedureEntityStorage->storeEntity(procedureEntity));

	// Storing incorrect entities
	REQUIRE(!procedureEntityStorage->storeEntity(entity));
	REQUIRE(!procedureEntityStorage->storeEntity(assignEntity));
	REQUIRE(!procedureEntityStorage->storeEntity(constantEntity));
	REQUIRE(!procedureEntityStorage->storeEntity(callEntity));
	REQUIRE(!procedureEntityStorage->storeEntity(ifEntity));
	REQUIRE(!procedureEntityStorage->storeEntity(printEntity));
	REQUIRE(!procedureEntityStorage->storeEntity(readEntity));
	REQUIRE(!procedureEntityStorage->storeEntity(variableEntity));
	REQUIRE(!procedureEntityStorage->storeEntity(whileEntity));

	// Check size to make sure only the correct entity is stored
	REQUIRE(procedureEntityStorage->getSize() == 1);

	// Storing second correct entity
	REQUIRE(procedureEntityStorage->storeEntity(procedureEntityTwo));

	// Check size to make sure both of the correct entities is stored
	REQUIRE(procedureEntityStorage->getSize() == 2);

	// Get Set based on TokenType
	std::unordered_set<Entity*>* assignSet = procedureEntityStorage->getAllEntity(qps::TokenType::ASSIGN);
	std::unordered_set<Entity*>* constantSet = procedureEntityStorage->getAllEntity(qps::TokenType::CONSTANT);
	std::unordered_set<Entity*>* callSet = procedureEntityStorage->getAllEntity(qps::TokenType::CALL);
	std::unordered_set<Entity*>* ifSet = procedureEntityStorage->getAllEntity(qps::TokenType::IF);
	std::unordered_set<Entity*>* printSet = procedureEntityStorage->getAllEntity(qps::TokenType::PRINT);
	std::unordered_set<Entity*>* procedureSet = procedureEntityStorage->getAllEntity(qps::TokenType::PROCEDURE);
	std::unordered_set<Entity*>* readSet = procedureEntityStorage->getAllEntity(qps::TokenType::READ);
	std::unordered_set<Entity*>* variableSet = procedureEntityStorage->getAllEntity(qps::TokenType::VARIABLE);
	std::unordered_set<Entity*>* whileSet = procedureEntityStorage->getAllEntity(qps::TokenType::WHILE);
	std::unordered_set<Entity*>* stmtSet = procedureEntityStorage->getAllEntity(qps::TokenType::STMT);

	// Correct TokenType should return the set instead of nullptr
	REQUIRE(procedureSet != nullptr);

	// Incorrect TokenType should return nullptr instead of the set
	REQUIRE(assignSet == nullptr);
	REQUIRE(constantSet == nullptr);
	REQUIRE(callSet == nullptr);
	REQUIRE(ifSet == nullptr);
	REQUIRE(printSet == nullptr);
	REQUIRE(readSet == nullptr);
	REQUIRE(variableSet == nullptr);
	REQUIRE(whileSet == nullptr);
	REQUIRE(stmtSet == nullptr);

	// Retreiving entities from the storage
	REQUIRE(procedureSet->find(procedureEntity) != procedureSet->end());
	REQUIRE(procedureSet->find(procedureEntityTwo) != procedureSet->end());
	REQUIRE(procedureSet->find(procedureEntityThree) == procedureSet->end());
}

TEST_CASE("Read Entity Storage Test") {
	EntityStorage* readEntityStorage = new ReadEntityStorage();

	// Storing the correct entity
	REQUIRE(readEntityStorage->storeEntity(readEntity));

	// Storing incorrect entities
	REQUIRE(!readEntityStorage->storeEntity(entity));
	REQUIRE(!readEntityStorage->storeEntity(assignEntity));
	REQUIRE(!readEntityStorage->storeEntity(constantEntity));
	REQUIRE(!readEntityStorage->storeEntity(callEntity));
	REQUIRE(!readEntityStorage->storeEntity(ifEntity));
	REQUIRE(!readEntityStorage->storeEntity(printEntity));
	REQUIRE(!readEntityStorage->storeEntity(procedureEntity));
	REQUIRE(!readEntityStorage->storeEntity(variableEntity));
	REQUIRE(!readEntityStorage->storeEntity(whileEntity));

	// Check size to make sure only the correct entity is stored
	REQUIRE(readEntityStorage->getSize() == 1);

	// Storing second correct entity
	REQUIRE(readEntityStorage->storeEntity(readEntityTwo));

	// Check size to make sure both of the correct entities is stored
	REQUIRE(readEntityStorage->getSize() == 2);

	// Get Set based on TokenType
	std::unordered_set<Entity*>* assignSet = readEntityStorage->getAllEntity(qps::TokenType::ASSIGN);
	std::unordered_set<Entity*>* constantSet = readEntityStorage->getAllEntity(qps::TokenType::CONSTANT);
	std::unordered_set<Entity*>* callSet = readEntityStorage->getAllEntity(qps::TokenType::CALL);
	std::unordered_set<Entity*>* ifSet = readEntityStorage->getAllEntity(qps::TokenType::IF);
	std::unordered_set<Entity*>* printSet = readEntityStorage->getAllEntity(qps::TokenType::PRINT);
	std::unordered_set<Entity*>* procedureSet = readEntityStorage->getAllEntity(qps::TokenType::PROCEDURE);
	std::unordered_set<Entity*>* readSet = readEntityStorage->getAllEntity(qps::TokenType::READ);
	std::unordered_set<Entity*>* variableSet = readEntityStorage->getAllEntity(qps::TokenType::VARIABLE);
	std::unordered_set<Entity*>* whileSet = readEntityStorage->getAllEntity(qps::TokenType::WHILE);
	std::unordered_set<Entity*>* stmtSet = readEntityStorage->getAllEntity(qps::TokenType::STMT);

	// Correct TokenType should return the set instead of nullptr
	REQUIRE(readSet != nullptr);

	// Incorrect TokenType should return nullptr instead of the set
	REQUIRE(assignSet == nullptr);
	REQUIRE(constantSet == nullptr);
	REQUIRE(callSet == nullptr);
	REQUIRE(ifSet == nullptr);
	REQUIRE(printSet == nullptr);
	REQUIRE(procedureSet == nullptr);
	REQUIRE(variableSet == nullptr);
	REQUIRE(whileSet == nullptr);
	REQUIRE(stmtSet == nullptr);

	// Retreiving entities from the storage
	REQUIRE(readSet->find(readEntity) != readSet->end());
	REQUIRE(readSet->find(readEntityTwo) != readSet->end());
	REQUIRE(readSet->find(readEntityThree) == readSet->end());
}

TEST_CASE("Variable Entity Storage Test") {
	EntityStorage* variableEntityStorage = new VariableEntityStorage();

	// Storing the correct entity
	REQUIRE(variableEntityStorage->storeEntity(variableEntity));

	// Storing incorrect entities
	REQUIRE(!variableEntityStorage->storeEntity(entity));
	REQUIRE(!variableEntityStorage->storeEntity(assignEntity));
	REQUIRE(!variableEntityStorage->storeEntity(constantEntity));
	REQUIRE(!variableEntityStorage->storeEntity(callEntity));
	REQUIRE(!variableEntityStorage->storeEntity(ifEntity));
	REQUIRE(!variableEntityStorage->storeEntity(printEntity));
	REQUIRE(!variableEntityStorage->storeEntity(procedureEntity));
	REQUIRE(!variableEntityStorage->storeEntity(readEntity));
	REQUIRE(!variableEntityStorage->storeEntity(whileEntity));

	// Check size to make sure only the correct entity is stored
	REQUIRE(variableEntityStorage->getSize() == 1);

	// Storing second correct entity
	REQUIRE(variableEntityStorage->storeEntity(variableEntityTwo));

	// Check size to make sure both of the correct entities is stored
	REQUIRE(variableEntityStorage->getSize() == 2);

	// Get Set based on TokenType
	std::unordered_set<Entity*>* assignSet = variableEntityStorage->getAllEntity(qps::TokenType::ASSIGN);
	std::unordered_set<Entity*>* constantSet = variableEntityStorage->getAllEntity(qps::TokenType::CONSTANT);
	std::unordered_set<Entity*>* callSet = variableEntityStorage->getAllEntity(qps::TokenType::CALL);
	std::unordered_set<Entity*>* ifSet = variableEntityStorage->getAllEntity(qps::TokenType::IF);
	std::unordered_set<Entity*>* printSet = variableEntityStorage->getAllEntity(qps::TokenType::PRINT);
	std::unordered_set<Entity*>* procedureSet = variableEntityStorage->getAllEntity(qps::TokenType::PROCEDURE);
	std::unordered_set<Entity*>* readSet = variableEntityStorage->getAllEntity(qps::TokenType::READ);
	std::unordered_set<Entity*>* variableSet = variableEntityStorage->getAllEntity(qps::TokenType::VARIABLE);
	std::unordered_set<Entity*>* whileSet = variableEntityStorage->getAllEntity(qps::TokenType::WHILE);
	std::unordered_set<Entity*>* stmtSet = variableEntityStorage->getAllEntity(qps::TokenType::STMT);

	// Correct TokenType should return the set instead of nullptr
	REQUIRE(variableSet != nullptr);

	// Incorrect TokenType should return nullptr instead of the set
	REQUIRE(assignSet == nullptr);
	REQUIRE(constantSet == nullptr);
	REQUIRE(callSet == nullptr);
	REQUIRE(ifSet == nullptr);
	REQUIRE(printSet == nullptr);
	REQUIRE(procedureSet == nullptr);
	REQUIRE(readSet == nullptr);
	REQUIRE(whileSet == nullptr);
	REQUIRE(stmtSet == nullptr);

	// Retreiving entities from the storage
	REQUIRE(variableSet->find(variableEntity) != variableSet->end());
	REQUIRE(variableSet->find(variableEntityTwo) != variableSet->end());
	REQUIRE(variableSet->find(variableEntityThree) == variableSet->end());
}

TEST_CASE("While Entity Storage Test") {
	EntityStorage* whileEntityStorage = new WhileEntityStorage();

	// Storing the correct entity
	REQUIRE(whileEntityStorage->storeEntity(whileEntity));

	// Storing incorrect entities
	REQUIRE(!whileEntityStorage->storeEntity(entity));
	REQUIRE(!whileEntityStorage->storeEntity(assignEntity));
	REQUIRE(!whileEntityStorage->storeEntity(constantEntity));
	REQUIRE(!whileEntityStorage->storeEntity(callEntity));
	REQUIRE(!whileEntityStorage->storeEntity(ifEntity));
	REQUIRE(!whileEntityStorage->storeEntity(printEntity));
	REQUIRE(!whileEntityStorage->storeEntity(procedureEntity));
	REQUIRE(!whileEntityStorage->storeEntity(readEntity));
	REQUIRE(!whileEntityStorage->storeEntity(variableEntity));
	
	// Check size to make sure only the correct entity is stored
	REQUIRE(whileEntityStorage->getSize() == 1);

	// Storing second correct entity
	REQUIRE(whileEntityStorage->storeEntity(whileEntityTwo));

	// Check size to make sure both of the correct entities is stored
	REQUIRE(whileEntityStorage->getSize() == 2);

	// Get Set based on TokenType
	std::unordered_set<Entity*>* assignSet = whileEntityStorage->getAllEntity(qps::TokenType::ASSIGN);
	std::unordered_set<Entity*>* constantSet = whileEntityStorage->getAllEntity(qps::TokenType::CONSTANT);
	std::unordered_set<Entity*>* callSet = whileEntityStorage->getAllEntity(qps::TokenType::CALL);
	std::unordered_set<Entity*>* ifSet = whileEntityStorage->getAllEntity(qps::TokenType::IF);
	std::unordered_set<Entity*>* printSet = whileEntityStorage->getAllEntity(qps::TokenType::PRINT);
	std::unordered_set<Entity*>* procedureSet = whileEntityStorage->getAllEntity(qps::TokenType::PROCEDURE);
	std::unordered_set<Entity*>* readSet = whileEntityStorage->getAllEntity(qps::TokenType::READ);
	std::unordered_set<Entity*>* variableSet = whileEntityStorage->getAllEntity(qps::TokenType::VARIABLE);
	std::unordered_set<Entity*>* whileSet = whileEntityStorage->getAllEntity(qps::TokenType::WHILE);
	std::unordered_set<Entity*>* stmtSet = whileEntityStorage->getAllEntity(qps::TokenType::STMT);

	// Correct TokenType should return the set instead of nullptr
	REQUIRE(whileSet != nullptr);

	// Incorrect TokenType should return nullptr instead of the set
	REQUIRE(assignSet == nullptr);
	REQUIRE(constantSet == nullptr);
	REQUIRE(callSet == nullptr);
	REQUIRE(ifSet == nullptr);
	REQUIRE(printSet == nullptr);
	REQUIRE(procedureSet == nullptr);
	REQUIRE(readSet == nullptr);
	REQUIRE(variableSet == nullptr);
	REQUIRE(stmtSet == nullptr);

	// Retreiving entities from the storage
	REQUIRE(whileSet->find(whileEntity) != whileSet->end());
	REQUIRE(whileSet->find(whileEntityTwo) != whileSet->end());
	REQUIRE(whileSet->find(whileEntityThree) == whileSet->end());
}

TEST_CASE("Statement Entity Storage Test") {
	EntityStorage* statementEntityStorage = new StatementEntityStorage();

	// Storing the correct entities
	REQUIRE(statementEntityStorage->storeEntity(assignEntity));
	REQUIRE(statementEntityStorage->storeEntity(printEntity));
	REQUIRE(statementEntityStorage->storeEntity(callEntity));
	REQUIRE(statementEntityStorage->storeEntity(readEntity));
	REQUIRE(statementEntityStorage->storeEntity(ifEntity));
	REQUIRE(statementEntityStorage->storeEntity(whileEntity));

	// Storing incorrect entities
	REQUIRE(!statementEntityStorage->storeEntity(entity));
	REQUIRE(!statementEntityStorage->storeEntity(constantEntity));
	REQUIRE(!statementEntityStorage->storeEntity(procedureEntity));
	REQUIRE(!statementEntityStorage->storeEntity(variableEntity));

	// Check size to make sure only all the correct entities is stored
	REQUIRE(statementEntityStorage->getSize() == 6);

	// Storing correct entities for the second insertion of the same type
	REQUIRE(statementEntityStorage->storeEntity(assignEntityTwo));
	REQUIRE(statementEntityStorage->storeEntity(printEntityTwo));
	REQUIRE(statementEntityStorage->storeEntity(callEntityTwo));
	REQUIRE(statementEntityStorage->storeEntity(readEntityTwo));
	REQUIRE(statementEntityStorage->storeEntity(ifEntityTwo));
	REQUIRE(statementEntityStorage->storeEntity(whileEntityTwo));

	// Check size to make sure all the correct entities is stored after the second insertion
	REQUIRE(statementEntityStorage->getSize() == 12);

	// Storing some of the correct entities to check whether different entities with the same value will not overlap
	REQUIRE(statementEntityStorage->storeEntity(assignEntityThree));
	REQUIRE(statementEntityStorage->storeEntity(printEntityThree));
	REQUIRE(statementEntityStorage->storeEntity(callEntityThree));

	// Get Set based on TokenType
	std::unordered_set<Entity*>* assignSet = statementEntityStorage->getAllEntity(qps::TokenType::ASSIGN);
	std::unordered_set<Entity*>* constantSet = statementEntityStorage->getAllEntity(qps::TokenType::CONSTANT);
	std::unordered_set<Entity*>* callSet = statementEntityStorage->getAllEntity(qps::TokenType::CALL);
	std::unordered_set<Entity*>* ifSet = statementEntityStorage->getAllEntity(qps::TokenType::IF);
	std::unordered_set<Entity*>* printSet = statementEntityStorage->getAllEntity(qps::TokenType::PRINT);
	std::unordered_set<Entity*>* procedureSet = statementEntityStorage->getAllEntity(qps::TokenType::PROCEDURE);
	std::unordered_set<Entity*>* readSet = statementEntityStorage->getAllEntity(qps::TokenType::READ);
	std::unordered_set<Entity*>* variableSet = statementEntityStorage->getAllEntity(qps::TokenType::VARIABLE);
	std::unordered_set<Entity*>* whileSet = statementEntityStorage->getAllEntity(qps::TokenType::WHILE);
	std::unordered_set<Entity*>* stmtSet = statementEntityStorage->getAllEntity(qps::TokenType::STMT);

	// Correct TokenType should return the set instead of nullptr
	REQUIRE(stmtSet != nullptr);

	// Incorrect TokenType should return nullptr instead of the set
	REQUIRE(assignSet == nullptr);
	REQUIRE(constantSet == nullptr);
	REQUIRE(callSet == nullptr);
	REQUIRE(ifSet == nullptr);
	REQUIRE(printSet == nullptr);
	REQUIRE(procedureSet == nullptr);
	REQUIRE(readSet == nullptr);
	REQUIRE(variableSet == nullptr);
	REQUIRE(whileSet == nullptr);

	// Retreiving entities from the storage
	REQUIRE(stmtSet->find(assignEntity) != stmtSet->end());
	REQUIRE(stmtSet->find(assignEntityTwo) != stmtSet->end());
	REQUIRE(stmtSet->find(assignEntityThree) != stmtSet->end());

	REQUIRE(stmtSet->find(printEntity) != stmtSet->end());
	REQUIRE(stmtSet->find(printEntityTwo) != stmtSet->end());
	REQUIRE(stmtSet->find(printEntityThree) != stmtSet->end());

	REQUIRE(stmtSet->find(callEntity) != stmtSet->end());
	REQUIRE(stmtSet->find(callEntityTwo) != stmtSet->end());
	REQUIRE(stmtSet->find(callEntityThree) != stmtSet->end());

	// Retreiving entities from the storage and trying to retreive different entities with same value
	REQUIRE(stmtSet->find(readEntity) != stmtSet->end());
	REQUIRE(stmtSet->find(readEntityTwo) != stmtSet->end());
	REQUIRE(stmtSet->find(readEntityThree) == stmtSet->end());

	REQUIRE(stmtSet->find(readEntity) != stmtSet->end());
	REQUIRE(stmtSet->find(readEntityTwo) != stmtSet->end());
	REQUIRE(stmtSet->find(readEntityThree) == stmtSet->end());

	REQUIRE(stmtSet->find(ifEntity) != stmtSet->end());
	REQUIRE(stmtSet->find(ifEntityTwo) != stmtSet->end());
	REQUIRE(stmtSet->find(ifEntityThree) == stmtSet->end());

	REQUIRE(stmtSet->find(whileEntity) != stmtSet->end());
	REQUIRE(stmtSet->find(whileEntityTwo) != stmtSet->end());
	REQUIRE(stmtSet->find(whileEntityThree) == stmtSet->end());
}
