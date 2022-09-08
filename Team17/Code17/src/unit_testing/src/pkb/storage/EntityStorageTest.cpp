#include <catch.hpp>
#include "../EntityObject.h"
#include "components/pkb/storage/EntityStorage/EntityStorage.h"
#include "components/pkb/storage/EntityStorage/AssignEntityStorage.h"
#include "components/pkb/storage/EntityStorage/CallEntityStorage.h"
#include "components/pkb/storage/EntityStorage/ConstantEntityStorage.h"
#include "components/pkb/storage/EntityStorage/EntityStorage.h"
#include "components/pkb/storage/EntityStorage/IfEntityStorage.h"
#include "components/pkb/storage/EntityStorage/PrintEntityStorage.h"
#include "components/pkb/storage/EntityStorage/ProcedureEntityStorage.h"
#include "components/pkb/storage/EntityStorage/ReadEntityStorage.h"
#include "components/pkb/storage/EntityStorage/VariableEntityStorage.h"
#include "components/pkb/storage/EntityStorage/StatementEntityStorage.h"
#include "components/pkb/storage/EntityStorage/WhileEntityStorage.h"
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
	std::unordered_set<std::string> assignSet = assignEntityStorage->getAllEntity(DesignEntity::ASSIGN);
	std::unordered_set<std::string> constantSet = assignEntityStorage->getAllEntity(DesignEntity::CONSTANT);
	std::unordered_set<std::string> callSet = assignEntityStorage->getAllEntity(DesignEntity::CALL);
	std::unordered_set<std::string> ifSet = assignEntityStorage->getAllEntity(DesignEntity::IF);
	std::unordered_set<std::string> printSet = assignEntityStorage->getAllEntity(DesignEntity::PRINT);
	std::unordered_set<std::string> procedureSet = assignEntityStorage->getAllEntity(DesignEntity::PROCEDURE);
	std::unordered_set<std::string> readSet = assignEntityStorage->getAllEntity(DesignEntity::READ);
	std::unordered_set<std::string> variableSet = assignEntityStorage->getAllEntity(DesignEntity::VARIABLE);
	std::unordered_set<std::string> whileSet = assignEntityStorage->getAllEntity(DesignEntity::WHILE);
	std::unordered_set<std::string> stmtSet = assignEntityStorage->getAllEntity(DesignEntity::STMT);

	// Correct TokenType should return the set instead of nullptr
	REQUIRE(assignSet != std::unordered_set<std::string>());

	// Incorrect TokenType should return nullptr instead of the set
	REQUIRE(constantSet == std::unordered_set<std::string>());
	REQUIRE(callSet == std::unordered_set<std::string>());
	REQUIRE(ifSet == std::unordered_set<std::string>());
	REQUIRE(printSet == std::unordered_set<std::string>());
	REQUIRE(procedureSet == std::unordered_set<std::string>());
	REQUIRE(readSet == std::unordered_set<std::string>());
	REQUIRE(variableSet == std::unordered_set<std::string>());
	REQUIRE(whileSet == std::unordered_set<std::string>());
	REQUIRE(stmtSet == std::unordered_set<std::string>());

	// Retreiving entities from the storage
	REQUIRE(assignSet.find(assign_value_one) != assignSet.end());
	REQUIRE(assignSet.find(assign_value_two) != assignSet.end());
	REQUIRE(assignSet.find(assign_value_three) == assignSet.end());

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
	std::unordered_set<std::string> assignSet = constantEntityStorage->getAllEntity(DesignEntity::ASSIGN);
	std::unordered_set<std::string> constantSet = constantEntityStorage->getAllEntity(DesignEntity::CONSTANT);
	std::unordered_set<std::string> callSet = constantEntityStorage->getAllEntity(DesignEntity::CALL);
	std::unordered_set<std::string> ifSet = constantEntityStorage->getAllEntity(DesignEntity::IF);
	std::unordered_set<std::string> printSet = constantEntityStorage->getAllEntity(DesignEntity::PRINT);
	std::unordered_set<std::string> procedureSet = constantEntityStorage->getAllEntity(DesignEntity::PROCEDURE);
	std::unordered_set<std::string> readSet = constantEntityStorage->getAllEntity(DesignEntity::READ);
	std::unordered_set<std::string> variableSet = constantEntityStorage->getAllEntity(DesignEntity::VARIABLE);
	std::unordered_set<std::string> whileSet = constantEntityStorage->getAllEntity(DesignEntity::WHILE);
	std::unordered_set<std::string> stmtSet = constantEntityStorage->getAllEntity(DesignEntity::STMT);

	// Correct TokenType should return the set instead of nullptr
	REQUIRE(constantSet != std::unordered_set<std::string>());

	// Incorrect TokenType should return nullptr instead of the set
	REQUIRE(assignSet == std::unordered_set<std::string>());
	REQUIRE(callSet == std::unordered_set<std::string>());
	REQUIRE(ifSet == std::unordered_set<std::string>());
	REQUIRE(printSet == std::unordered_set<std::string>());
	REQUIRE(procedureSet == std::unordered_set<std::string>());
	REQUIRE(readSet == std::unordered_set<std::string>());
	REQUIRE(variableSet == std::unordered_set<std::string>());
	REQUIRE(whileSet == std::unordered_set<std::string>());
	REQUIRE(stmtSet == std::unordered_set<std::string>());

	// Retreiving entities from the storage
	REQUIRE(constantSet.find(constant_value_one) != constantSet.end());
	REQUIRE(constantSet.find(constant_value_two) != constantSet.end());
	REQUIRE(constantSet.find(constant_value_three) == constantSet.end());
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
	std::unordered_set<std::string> assignSet = callEntityStorage->getAllEntity(DesignEntity::ASSIGN);
	std::unordered_set<std::string> constantSet = callEntityStorage->getAllEntity(DesignEntity::CONSTANT);
	std::unordered_set<std::string> callSet = callEntityStorage->getAllEntity(DesignEntity::CALL);
	std::unordered_set<std::string> ifSet = callEntityStorage->getAllEntity(DesignEntity::IF);
	std::unordered_set<std::string> printSet = callEntityStorage->getAllEntity(DesignEntity::PRINT);
	std::unordered_set<std::string> procedureSet = callEntityStorage->getAllEntity(DesignEntity::PROCEDURE);
	std::unordered_set<std::string> readSet = callEntityStorage->getAllEntity(DesignEntity::READ);
	std::unordered_set<std::string> variableSet = callEntityStorage->getAllEntity(DesignEntity::VARIABLE);
	std::unordered_set<std::string> whileSet = callEntityStorage->getAllEntity(DesignEntity::WHILE);
	std::unordered_set<std::string> stmtSet = callEntityStorage->getAllEntity(DesignEntity::STMT);

	// Correct TokenType should return the set instead of nullptr
	REQUIRE(callSet != std::unordered_set<std::string>());

	// Incorrect TokenType should return nullptr instead of the set
	REQUIRE(assignSet == std::unordered_set<std::string>());
	REQUIRE(constantSet == std::unordered_set<std::string>());
	REQUIRE(ifSet == std::unordered_set<std::string>());
	REQUIRE(printSet == std::unordered_set<std::string>());
	REQUIRE(procedureSet == std::unordered_set<std::string>());
	REQUIRE(readSet == std::unordered_set<std::string>());
	REQUIRE(variableSet == std::unordered_set<std::string>());
	REQUIRE(whileSet == std::unordered_set<std::string>());
	REQUIRE(stmtSet == std::unordered_set<std::string>());

	// Retreiving entities from the storage
	REQUIRE(callSet.find(call_value_one) != callSet.end());
	REQUIRE(callSet.find(call_value_two) != callSet.end());
	REQUIRE(callSet.find(call_value_three) == callSet.end());
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
	std::unordered_set<std::string> assignSet = ifEntityStorage->getAllEntity(DesignEntity::ASSIGN);
	std::unordered_set<std::string> constantSet = ifEntityStorage->getAllEntity(DesignEntity::CONSTANT);
	std::unordered_set<std::string> callSet = ifEntityStorage->getAllEntity(DesignEntity::CALL);
	std::unordered_set<std::string> ifSet = ifEntityStorage->getAllEntity(DesignEntity::IF);
	std::unordered_set<std::string> printSet = ifEntityStorage->getAllEntity(DesignEntity::PRINT);
	std::unordered_set<std::string> procedureSet = ifEntityStorage->getAllEntity(DesignEntity::PROCEDURE);
	std::unordered_set<std::string> readSet = ifEntityStorage->getAllEntity(DesignEntity::READ);
	std::unordered_set<std::string> variableSet = ifEntityStorage->getAllEntity(DesignEntity::VARIABLE);
	std::unordered_set<std::string> whileSet = ifEntityStorage->getAllEntity(DesignEntity::WHILE);
	std::unordered_set<std::string> stmtSet = ifEntityStorage->getAllEntity(DesignEntity::STMT);

	// Correct TokenType should return the set instead of nullptr
	REQUIRE(ifSet != std::unordered_set<std::string>());

	// Incorrect TokenType should return nullptr instead of the set
	REQUIRE(assignSet == std::unordered_set<std::string>());
	REQUIRE(constantSet == std::unordered_set<std::string>());
	REQUIRE(callSet == std::unordered_set<std::string>());
	REQUIRE(printSet == std::unordered_set<std::string>());
	REQUIRE(procedureSet == std::unordered_set<std::string>());
	REQUIRE(readSet == std::unordered_set<std::string>());
	REQUIRE(variableSet == std::unordered_set<std::string>());
	REQUIRE(whileSet == std::unordered_set<std::string>());
	REQUIRE(stmtSet == std::unordered_set<std::string>());

	// Retreiving entities from the storage
	REQUIRE(ifSet.find(if_value_one) != ifSet.end());
	REQUIRE(ifSet.find(if_value_two) != ifSet.end());
	REQUIRE(ifSet.find(if_value_three) == ifSet.end());
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
	std::unordered_set<std::string> assignSet = printEntityStorage->getAllEntity(DesignEntity::ASSIGN);
	std::unordered_set<std::string> constantSet = printEntityStorage->getAllEntity(DesignEntity::CONSTANT);
	std::unordered_set<std::string> callSet = printEntityStorage->getAllEntity(DesignEntity::CALL);
	std::unordered_set<std::string> ifSet = printEntityStorage->getAllEntity(DesignEntity::IF);
	std::unordered_set<std::string> printSet = printEntityStorage->getAllEntity(DesignEntity::PRINT);
	std::unordered_set<std::string> procedureSet = printEntityStorage->getAllEntity(DesignEntity::PROCEDURE);
	std::unordered_set<std::string> readSet = printEntityStorage->getAllEntity(DesignEntity::READ);
	std::unordered_set<std::string> variableSet = printEntityStorage->getAllEntity(DesignEntity::VARIABLE);
	std::unordered_set<std::string> whileSet = printEntityStorage->getAllEntity(DesignEntity::WHILE);
	std::unordered_set<std::string> stmtSet = printEntityStorage->getAllEntity(DesignEntity::STMT);

	// Correct TokenType should return the set instead of nullptr
	REQUIRE(printSet != std::unordered_set<std::string>());

	// Incorrect TokenType should return nullptr instead of the set
	REQUIRE(assignSet == std::unordered_set<std::string>());
	REQUIRE(constantSet == std::unordered_set<std::string>());
	REQUIRE(callSet == std::unordered_set<std::string>());
	REQUIRE(ifSet == std::unordered_set<std::string>());
	REQUIRE(procedureSet == std::unordered_set<std::string>());
	REQUIRE(readSet == std::unordered_set<std::string>());
	REQUIRE(variableSet == std::unordered_set<std::string>());
	REQUIRE(whileSet == std::unordered_set<std::string>());
	REQUIRE(stmtSet == std::unordered_set<std::string>());

	// Retreiving entities from the storage
	REQUIRE(printSet.find(print_value_one) != printSet.end());
	REQUIRE(printSet.find(print_value_two) != printSet.end());
	REQUIRE(printSet.find(print_value_three) == printSet.end());
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
	std::unordered_set<std::string> assignSet = procedureEntityStorage->getAllEntity(DesignEntity::ASSIGN);
	std::unordered_set<std::string> constantSet = procedureEntityStorage->getAllEntity(DesignEntity::CONSTANT);
	std::unordered_set<std::string> callSet = procedureEntityStorage->getAllEntity(DesignEntity::CALL);
	std::unordered_set<std::string> ifSet = procedureEntityStorage->getAllEntity(DesignEntity::IF);
	std::unordered_set<std::string> printSet = procedureEntityStorage->getAllEntity(DesignEntity::PRINT);
	std::unordered_set<std::string> procedureSet = procedureEntityStorage->getAllEntity(DesignEntity::PROCEDURE);
	std::unordered_set<std::string> readSet = procedureEntityStorage->getAllEntity(DesignEntity::READ);
	std::unordered_set<std::string> variableSet = procedureEntityStorage->getAllEntity(DesignEntity::VARIABLE);
	std::unordered_set<std::string> whileSet = procedureEntityStorage->getAllEntity(DesignEntity::WHILE);
	std::unordered_set<std::string> stmtSet = procedureEntityStorage->getAllEntity(DesignEntity::STMT);

	// Correct TokenType should return the set instead of nullptr
	REQUIRE(procedureSet != std::unordered_set<std::string>());

	// Incorrect TokenType should return nullptr instead of the set
	REQUIRE(assignSet == std::unordered_set<std::string>());
	REQUIRE(constantSet == std::unordered_set<std::string>());
	REQUIRE(callSet == std::unordered_set<std::string>());
	REQUIRE(ifSet == std::unordered_set<std::string>());
	REQUIRE(printSet == std::unordered_set<std::string>());
	REQUIRE(readSet == std::unordered_set<std::string>());
	REQUIRE(variableSet == std::unordered_set<std::string>());
	REQUIRE(whileSet == std::unordered_set<std::string>());
	REQUIRE(stmtSet == std::unordered_set<std::string>());

	// Retreiving entities from the storage
	REQUIRE(procedureSet.find(procedure_value_one) != procedureSet.end());
	REQUIRE(procedureSet.find(procedure_value_two) != procedureSet.end());
	REQUIRE(procedureSet.find(procedure_value_three) == procedureSet.end());
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
	std::unordered_set<std::string> assignSet = readEntityStorage->getAllEntity(DesignEntity::ASSIGN);
	std::unordered_set<std::string> constantSet = readEntityStorage->getAllEntity(DesignEntity::CONSTANT);
	std::unordered_set<std::string> callSet = readEntityStorage->getAllEntity(DesignEntity::CALL);
	std::unordered_set<std::string> ifSet = readEntityStorage->getAllEntity(DesignEntity::IF);
	std::unordered_set<std::string> printSet = readEntityStorage->getAllEntity(DesignEntity::PRINT);
	std::unordered_set<std::string> procedureSet = readEntityStorage->getAllEntity(DesignEntity::PROCEDURE);
	std::unordered_set<std::string> readSet = readEntityStorage->getAllEntity(DesignEntity::READ);
	std::unordered_set<std::string> variableSet = readEntityStorage->getAllEntity(DesignEntity::VARIABLE);
	std::unordered_set<std::string> whileSet = readEntityStorage->getAllEntity(DesignEntity::WHILE);
	std::unordered_set<std::string> stmtSet = readEntityStorage->getAllEntity(DesignEntity::STMT);

	// Correct TokenType should return the set instead of nullptr
	REQUIRE(readSet != std::unordered_set<std::string>());

	// Incorrect TokenType should return nullptr instead of the set
	REQUIRE(assignSet == std::unordered_set<std::string>());
	REQUIRE(constantSet == std::unordered_set<std::string>());
	REQUIRE(callSet == std::unordered_set<std::string>());
	REQUIRE(ifSet == std::unordered_set<std::string>());
	REQUIRE(printSet == std::unordered_set<std::string>());
	REQUIRE(procedureSet == std::unordered_set<std::string>());
	REQUIRE(variableSet == std::unordered_set<std::string>());
	REQUIRE(whileSet == std::unordered_set<std::string>());
	REQUIRE(stmtSet == std::unordered_set<std::string>());

	// Retreiving entities from the storage
	REQUIRE(readSet.find(read_value_one) != readSet.end());
	REQUIRE(readSet.find(read_value_two) != readSet.end());
	REQUIRE(readSet.find(read_value_three) == readSet.end());
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
	std::unordered_set<std::string> assignSet = variableEntityStorage->getAllEntity(DesignEntity::ASSIGN);
	std::unordered_set<std::string> constantSet = variableEntityStorage->getAllEntity(DesignEntity::CONSTANT);
	std::unordered_set<std::string> callSet = variableEntityStorage->getAllEntity(DesignEntity::CALL);
	std::unordered_set<std::string> ifSet = variableEntityStorage->getAllEntity(DesignEntity::IF);
	std::unordered_set<std::string> printSet = variableEntityStorage->getAllEntity(DesignEntity::PRINT);
	std::unordered_set<std::string> procedureSet = variableEntityStorage->getAllEntity(DesignEntity::PROCEDURE);
	std::unordered_set<std::string> readSet = variableEntityStorage->getAllEntity(DesignEntity::READ);
	std::unordered_set<std::string> variableSet = variableEntityStorage->getAllEntity(DesignEntity::VARIABLE);
	std::unordered_set<std::string> whileSet = variableEntityStorage->getAllEntity(DesignEntity::WHILE);
	std::unordered_set<std::string> stmtSet = variableEntityStorage->getAllEntity(DesignEntity::STMT);

	// Correct TokenType should return the set instead of nullptr
	REQUIRE(variableSet != std::unordered_set<std::string>());

	// Incorrect TokenType should return nullptr instead of the set
	REQUIRE(assignSet == std::unordered_set<std::string>());
	REQUIRE(constantSet == std::unordered_set<std::string>());
	REQUIRE(callSet == std::unordered_set<std::string>());
	REQUIRE(ifSet == std::unordered_set<std::string>());
	REQUIRE(printSet == std::unordered_set<std::string>());
	REQUIRE(procedureSet == std::unordered_set<std::string>());
	REQUIRE(readSet == std::unordered_set<std::string>());
	REQUIRE(whileSet == std::unordered_set<std::string>());
	REQUIRE(stmtSet == std::unordered_set<std::string>());

	// Retreiving entities from the storage
	REQUIRE(variableSet.find(variable_value_one) != variableSet.end());
	REQUIRE(variableSet.find(variable_value_two) != variableSet.end());
	REQUIRE(variableSet.find(variable_value_three) == variableSet.end());
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
	std::unordered_set<std::string> assignSet = whileEntityStorage->getAllEntity(DesignEntity::ASSIGN);
	std::unordered_set<std::string> constantSet = whileEntityStorage->getAllEntity(DesignEntity::CONSTANT);
	std::unordered_set<std::string> callSet = whileEntityStorage->getAllEntity(DesignEntity::CALL);
	std::unordered_set<std::string> ifSet = whileEntityStorage->getAllEntity(DesignEntity::IF);
	std::unordered_set<std::string> printSet = whileEntityStorage->getAllEntity(DesignEntity::PRINT);
	std::unordered_set<std::string> procedureSet = whileEntityStorage->getAllEntity(DesignEntity::PROCEDURE);
	std::unordered_set<std::string> readSet = whileEntityStorage->getAllEntity(DesignEntity::READ);
	std::unordered_set<std::string> variableSet = whileEntityStorage->getAllEntity(DesignEntity::VARIABLE);
	std::unordered_set<std::string> whileSet = whileEntityStorage->getAllEntity(DesignEntity::WHILE);
	std::unordered_set<std::string> stmtSet = whileEntityStorage->getAllEntity(DesignEntity::STMT);

	// Correct TokenType should return the set instead of nullptr
	REQUIRE(whileSet != std::unordered_set<std::string>());

	// Incorrect TokenType should return nullptr instead of the set
	REQUIRE(assignSet == std::unordered_set<std::string>());
	REQUIRE(constantSet == std::unordered_set<std::string>());
	REQUIRE(callSet == std::unordered_set<std::string>());
	REQUIRE(ifSet == std::unordered_set<std::string>());
	REQUIRE(printSet == std::unordered_set<std::string>());
	REQUIRE(procedureSet == std::unordered_set<std::string>());
	REQUIRE(readSet == std::unordered_set<std::string>());
	REQUIRE(variableSet == std::unordered_set<std::string>());
	REQUIRE(stmtSet == std::unordered_set<std::string>());

	// Retreiving entities from the storage
	REQUIRE(whileSet.find(while_value_one) != whileSet.end());
	REQUIRE(whileSet.find(while_value_two) != whileSet.end());
	REQUIRE(whileSet.find(while_value_three) == whileSet.end());
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
	std::unordered_set<std::string> assignSet = statementEntityStorage->getAllEntity(DesignEntity::ASSIGN);
	std::unordered_set<std::string> constantSet = statementEntityStorage->getAllEntity(DesignEntity::CONSTANT);
	std::unordered_set<std::string> callSet = statementEntityStorage->getAllEntity(DesignEntity::CALL);
	std::unordered_set<std::string> ifSet = statementEntityStorage->getAllEntity(DesignEntity::IF);
	std::unordered_set<std::string> printSet = statementEntityStorage->getAllEntity(DesignEntity::PRINT);
	std::unordered_set<std::string> procedureSet = statementEntityStorage->getAllEntity(DesignEntity::PROCEDURE);
	std::unordered_set<std::string> readSet = statementEntityStorage->getAllEntity(DesignEntity::READ);
	std::unordered_set<std::string> variableSet = statementEntityStorage->getAllEntity(DesignEntity::VARIABLE);
	std::unordered_set<std::string> whileSet = statementEntityStorage->getAllEntity(DesignEntity::WHILE);
	std::unordered_set<std::string> stmtSet = statementEntityStorage->getAllEntity(DesignEntity::STMT);

	// Correct TokenType should return the set instead of nullptr
	REQUIRE(stmtSet != std::unordered_set<std::string>());

	// Incorrect TokenType should return nullptr instead of the set
	REQUIRE(assignSet == std::unordered_set<std::string>());
	REQUIRE(constantSet == std::unordered_set<std::string>());
	REQUIRE(callSet == std::unordered_set<std::string>());
	REQUIRE(ifSet == std::unordered_set<std::string>());
	REQUIRE(printSet == std::unordered_set<std::string>());
	REQUIRE(procedureSet == std::unordered_set<std::string>());
	REQUIRE(readSet == std::unordered_set<std::string>());
	REQUIRE(variableSet == std::unordered_set<std::string>());
	REQUIRE(whileSet == std::unordered_set<std::string>());

	// Retreiving entities from the storage
	REQUIRE(stmtSet.find(assign_value_one) != stmtSet.end());
	REQUIRE(stmtSet.find(assign_value_two) != stmtSet.end());
	REQUIRE(stmtSet.find(assign_value_three) != stmtSet.end());

	REQUIRE(stmtSet.find(print_value_one) != stmtSet.end());
	REQUIRE(stmtSet.find(print_value_two) != stmtSet.end());
	REQUIRE(stmtSet.find(print_value_three) != stmtSet.end());

	REQUIRE(stmtSet.find(call_value_one) != stmtSet.end());
	REQUIRE(stmtSet.find(call_value_two) != stmtSet.end());
	REQUIRE(stmtSet.find(call_value_three) != stmtSet.end());

	// Retreiving entities from the storage and trying to retreive different entities with same value
	REQUIRE(stmtSet.find(read_value_one) != stmtSet.end());
	REQUIRE(stmtSet.find(read_value_two) != stmtSet.end());
	REQUIRE(stmtSet.find(read_value_three) == stmtSet.end());

	//REQUIRE(stmtSet.find(readEntity) != stmtSet.end());
	//REQUIRE(stmtSet.find(readEntityTwo) != stmtSet.end());
	//REQUIRE(stmtSet.find(readEntityThree) == stmtSet.end());

	REQUIRE(stmtSet.find(if_value_one) != stmtSet.end());
	REQUIRE(stmtSet.find(if_value_two) != stmtSet.end());
	REQUIRE(stmtSet.find(if_value_three) == stmtSet.end());

	REQUIRE(stmtSet.find(while_value_one) != stmtSet.end());
	REQUIRE(stmtSet.find(while_value_two) != stmtSet.end());
	REQUIRE(stmtSet.find(while_value_three) == stmtSet.end());
}
