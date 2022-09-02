#include <catch.hpp>
#include "./EntityObject.h"
#include "components/pkb/storage/EntityStorage.h"
#include "components/pkb/storage/AssignEntityStorage.h"
#include <iostream>

TEST_CASE("Assign Entity Storage Test") {
	EntityStorage* assignEntityStorage = new AssignEntityStorage();

	REQUIRE(assignEntityStorage->storeEntity(assignEntity));
	REQUIRE(!assignEntityStorage->storeEntity(constantEntity));
	REQUIRE(!assignEntityStorage->storeEntity(callEntity));
	REQUIRE(!assignEntityStorage->storeEntity(ifEntity));
	REQUIRE(!assignEntityStorage->storeEntity(printEntity));
	REQUIRE(!assignEntityStorage->storeEntity(readEntity));
	REQUIRE(!assignEntityStorage->storeEntity(variableEntity));
	REQUIRE(!assignEntityStorage->storeEntity(whileEntity));

	REQUIRE(assignEntityStorage->getSize() == 1);

	REQUIRE(assignEntityStorage->storeEntity(assignEntityTwo));

	REQUIRE(assignEntityStorage->getSize() == 2);

	REQUIRE(assignEntityStorage->getSet()->find(assignEntity) != assignEntityStorage->getSet()->end());
	REQUIRE(assignEntityStorage->getSet()->find(assignEntityTwo) != assignEntityStorage->getSet()->end());
	REQUIRE(assignEntityStorage->getSet()->find(assignEntityThree) == assignEntityStorage->getSet()->end());
}