#include <catch.hpp>
#include "./EntityObject.h"
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
#include <iostream>

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
	REQUIRE(!assignEntityStorage->storeEntity(readEntity));
	REQUIRE(!assignEntityStorage->storeEntity(variableEntity));
	REQUIRE(!assignEntityStorage->storeEntity(whileEntity));

	// Check size to make sure only the correct entity is stored
	REQUIRE(assignEntityStorage->getSize() == 1);

	// Storing second correct entity
	REQUIRE(assignEntityStorage->storeEntity(assignEntityTwo));

	// Check size to make sure both of the correct entities is stored
	REQUIRE(assignEntityStorage->getSize() == 2);

	// Retreiving entities from the storage
	REQUIRE(assignEntityStorage->getSet()->find(assignEntity) != assignEntityStorage->getSet()->end());
	REQUIRE(assignEntityStorage->getSet()->find(assignEntityTwo) != assignEntityStorage->getSet()->end());
	REQUIRE(assignEntityStorage->getSet()->find(assignEntityThree) == assignEntityStorage->getSet()->end());
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
	REQUIRE(!constantEntityStorage->storeEntity(readEntity));
	REQUIRE(!constantEntityStorage->storeEntity(variableEntity));
	REQUIRE(!constantEntityStorage->storeEntity(whileEntity));

	// Check size to make sure only the correct entity is stored
	REQUIRE(constantEntityStorage->getSize() == 1);

	// Storing second correct entity
	REQUIRE(constantEntityStorage->storeEntity(constantEntityTwo));

	// Check size to make sure both of the correct entities is stored
	REQUIRE(constantEntityStorage->getSize() == 2);

	// Retreiving entities from the storage
	REQUIRE(constantEntityStorage->getSet()->find(constantEntity) != constantEntityStorage->getSet()->end());
	REQUIRE(constantEntityStorage->getSet()->find(constantEntityTwo) != constantEntityStorage->getSet()->end());
	REQUIRE(constantEntityStorage->getSet()->find(constantEntityThree) == constantEntityStorage->getSet()->end());
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
	REQUIRE(!callEntityStorage->storeEntity(readEntity));
	REQUIRE(!callEntityStorage->storeEntity(variableEntity));
	REQUIRE(!callEntityStorage->storeEntity(whileEntity));

	// Check size to make sure only the correct entity is stored
	REQUIRE(callEntityStorage->getSize() == 1);

	// Storing second correct entity
	REQUIRE(callEntityStorage->storeEntity(callEntityTwo));

	// Check size to make sure both of the correct entities is stored
	REQUIRE(callEntityStorage->getSize() == 2);

	// Retreiving entities from the storage
	REQUIRE(callEntityStorage->getSet()->find(callEntity) != callEntityStorage->getSet()->end());
	REQUIRE(callEntityStorage->getSet()->find(callEntityTwo) != callEntityStorage->getSet()->end());
	REQUIRE(callEntityStorage->getSet()->find(callEntityThree) == callEntityStorage->getSet()->end());
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
	REQUIRE(!ifEntityStorage->storeEntity(readEntity));
	REQUIRE(!ifEntityStorage->storeEntity(variableEntity));
	REQUIRE(!ifEntityStorage->storeEntity(whileEntity));

	// Check size to make sure only the correct entity is stored
	REQUIRE(ifEntityStorage->getSize() == 1);

	// Storing second correct entity
	REQUIRE(ifEntityStorage->storeEntity(ifEntityTwo));


	// Check size to make sure both of the correct entities is stored
	REQUIRE(ifEntityStorage->getSize() == 2);

	// Retreiving entities from the storage
	REQUIRE(ifEntityStorage->getSet()->find(ifEntity) != ifEntityStorage->getSet()->end());
	REQUIRE(ifEntityStorage->getSet()->find(ifEntityTwo) != ifEntityStorage->getSet()->end());
	REQUIRE(ifEntityStorage->getSet()->find(ifEntityThree) == ifEntityStorage->getSet()->end());
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
	REQUIRE(!printEntityStorage->storeEntity(readEntity));
	REQUIRE(!printEntityStorage->storeEntity(variableEntity));
	REQUIRE(!printEntityStorage->storeEntity(whileEntity));

	// Check size to make sure only the correct entity is stored
	REQUIRE(printEntityStorage->getSize() == 1);

	// Storing second correct entity
	REQUIRE(printEntityStorage->storeEntity(printEntityTwo));

	// Check size to make sure both of the correct entities is stored
	REQUIRE(printEntityStorage->getSize() == 2);

	// Retreiving entities from the storage
	REQUIRE(printEntityStorage->getSet()->find(printEntity) != printEntityStorage->getSet()->end());
	REQUIRE(printEntityStorage->getSet()->find(printEntityTwo) != printEntityStorage->getSet()->end());
	REQUIRE(printEntityStorage->getSet()->find(printEntityThree) == printEntityStorage->getSet()->end());
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

	// Retreiving entities from the storage
	REQUIRE(procedureEntityStorage->getSet()->find(procedureEntity) != procedureEntityStorage->getSet()->end());
	REQUIRE(procedureEntityStorage->getSet()->find(procedureEntityTwo) != procedureEntityStorage->getSet()->end());
	REQUIRE(procedureEntityStorage->getSet()->find(procedureEntityThree) == procedureEntityStorage->getSet()->end());
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

	// Retreiving entities from the storage
	REQUIRE(readEntityStorage->getSet()->find(readEntity) != readEntityStorage->getSet()->end());
	REQUIRE(readEntityStorage->getSet()->find(readEntityTwo) != readEntityStorage->getSet()->end());
	REQUIRE(readEntityStorage->getSet()->find(readEntityThree) == readEntityStorage->getSet()->end());
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

	// Retreiving entities from the storage
	REQUIRE(variableEntityStorage->getSet()->find(variableEntity) != variableEntityStorage->getSet()->end());
	REQUIRE(variableEntityStorage->getSet()->find(variableEntityTwo) != variableEntityStorage->getSet()->end());
	REQUIRE(variableEntityStorage->getSet()->find(variableEntityThree) == variableEntityStorage->getSet()->end());
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

	// Retreiving entities from the storage
	REQUIRE(whileEntityStorage->getSet()->find(whileEntity) != whileEntityStorage->getSet()->end());
	REQUIRE(whileEntityStorage->getSet()->find(whileEntityTwo) != whileEntityStorage->getSet()->end());
	REQUIRE(whileEntityStorage->getSet()->find(whileEntityThree) == whileEntityStorage->getSet()->end());
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

	// Retreiving entities from the storage
	REQUIRE(statementEntityStorage->getSet()->find(assignEntity) != statementEntityStorage->getSet()->end());
	REQUIRE(statementEntityStorage->getSet()->find(assignEntityTwo) != statementEntityStorage->getSet()->end());
	REQUIRE(statementEntityStorage->getSet()->find(assignEntityThree) != statementEntityStorage->getSet()->end());

	REQUIRE(statementEntityStorage->getSet()->find(printEntity) != statementEntityStorage->getSet()->end());
	REQUIRE(statementEntityStorage->getSet()->find(printEntityTwo) != statementEntityStorage->getSet()->end());
	REQUIRE(statementEntityStorage->getSet()->find(printEntityThree) != statementEntityStorage->getSet()->end());

	REQUIRE(statementEntityStorage->getSet()->find(callEntity) != statementEntityStorage->getSet()->end());
	REQUIRE(statementEntityStorage->getSet()->find(callEntityTwo) != statementEntityStorage->getSet()->end());
	REQUIRE(statementEntityStorage->getSet()->find(callEntityThree) != statementEntityStorage->getSet()->end());

	// Retreiving entities from the storage and trying to retreive different entities with same value
	REQUIRE(statementEntityStorage->getSet()->find(readEntity) != statementEntityStorage->getSet()->end());
	REQUIRE(statementEntityStorage->getSet()->find(readEntityTwo) != statementEntityStorage->getSet()->end());
	REQUIRE(statementEntityStorage->getSet()->find(readEntityThree) == statementEntityStorage->getSet()->end());

	REQUIRE(statementEntityStorage->getSet()->find(readEntity) != statementEntityStorage->getSet()->end());
	REQUIRE(statementEntityStorage->getSet()->find(readEntityTwo) != statementEntityStorage->getSet()->end());
	REQUIRE(statementEntityStorage->getSet()->find(readEntityThree) == statementEntityStorage->getSet()->end());

	REQUIRE(statementEntityStorage->getSet()->find(ifEntity) != statementEntityStorage->getSet()->end());
	REQUIRE(statementEntityStorage->getSet()->find(ifEntityTwo) != statementEntityStorage->getSet()->end());
	REQUIRE(statementEntityStorage->getSet()->find(ifEntityThree) == statementEntityStorage->getSet()->end());

	REQUIRE(statementEntityStorage->getSet()->find(whileEntity) != statementEntityStorage->getSet()->end());
	REQUIRE(statementEntityStorage->getSet()->find(whileEntityTwo) != statementEntityStorage->getSet()->end());
	REQUIRE(statementEntityStorage->getSet()->find(whileEntityThree) == statementEntityStorage->getSet()->end());
}
