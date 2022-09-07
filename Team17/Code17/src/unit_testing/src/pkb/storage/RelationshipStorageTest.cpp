#include <catch.hpp>

#include "components/pkb/storage/RelationshipStorage/RelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/UsesRelationshipStorage.h"
#include "../RelationshipObject.h"
#include "../ReuseableTokenObject.h"
#include <iostream>

TEST_CASE("Uses Relationship Storage Test") {
	RelationshipStorage* usesRelationshipStorage = new UsesRelationshipStorage();

	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipAssignOne));
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipAssignTwo));
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipAssignOneDuplicate));
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipAssignTwoDuplicate));

	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipProcOne));
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipProcTwo));
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipProcOneDuplicate));
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipProcTwoDuplicate));

	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipPrintOne));
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipPrintTwo));
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipPrintOneDuplicate));
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipPrintTwoDuplicate));

	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipWhileOne));
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipWhileTwo));
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipWhileOneDuplicate));
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipWhileTwoDuplicate));

	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipIfOne));
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipIfTwo));
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipIfOneDuplicate));
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipIfTwoDuplicate));

	REQUIRE(!usesRelationshipStorage->storeRelationship(modifyRelationshipAssignOne));

	REQUIRE(usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject1, variableTokenObject));
	REQUIRE(usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject1, variableTokenObjectThree));
	REQUIRE(usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject7, variableTokenObject));
	REQUIRE(usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject7, variableTokenObjectTwo));

	REQUIRE(usesRelationshipStorage->getRelationship(RelationshipType::USES, procedureTokenObject, variableTokenObject));
	REQUIRE(usesRelationshipStorage->getRelationship(RelationshipType::USES, procedureTokenObject, variableTokenObjectThree));
	REQUIRE(usesRelationshipStorage->getRelationship(RelationshipType::USES, procedureTokenObjectTwo, variableTokenObject));
	REQUIRE(usesRelationshipStorage->getRelationship(RelationshipType::USES, procedureTokenObjectTwo, variableTokenObjectTwo));

	REQUIRE(usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject3, variableTokenObject));
	REQUIRE(usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject3, variableTokenObjectThree));
	REQUIRE(usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject9, variableTokenObject));
	REQUIRE(usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject9, variableTokenObjectTwo));

	REQUIRE(usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject4, variableTokenObject));
	REQUIRE(usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject4, variableTokenObjectThree));
	REQUIRE(usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject10, variableTokenObject));
	REQUIRE(usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject10, variableTokenObjectTwo));

	REQUIRE(usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject6, variableTokenObject));
	REQUIRE(usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject6, variableTokenObjectThree));
	REQUIRE(usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject12, variableTokenObject));
	REQUIRE(usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject12, variableTokenObjectTwo));

	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject1, variableTokenObject));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject1, variableTokenObject));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject1, variableTokenObject));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::PARENT, stmtTokenObject1, variableTokenObject));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::PARENT_T, stmtTokenObject1, variableTokenObject));

	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject1, variableTokenObjectTwo));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject7, variableTokenObjectThree));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject13, variableTokenObject));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject13, variableTokenObjectTwo));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject13, variableTokenObjectThree));

	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, procedureTokenObject, variableTokenObjectTwo));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, procedureTokenObjectTwo, variableTokenObjectThree));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, procedureTokenObjectThree, variableTokenObject));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, procedureTokenObjectThree, variableTokenObjectTwo));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, procedureTokenObjectThree, variableTokenObjectThree));

	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject3, variableTokenObjectTwo));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject9, variableTokenObjectThree));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject15, variableTokenObject));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject15, variableTokenObjectTwo));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject15, variableTokenObjectThree));

	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject4, variableTokenObjectTwo));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject10, variableTokenObjectThree));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject16, variableTokenObject));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject16, variableTokenObjectTwo));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject16, variableTokenObjectThree));

	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject6, variableTokenObjectTwo));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject12, variableTokenObjectThree));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject18, variableTokenObject));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject18, variableTokenObjectTwo));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject18, variableTokenObjectThree));

	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject2, variableTokenObjectTwo));
	REQUIRE(!usesRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject5, variableTokenObjectThree));

	std::unordered_set<std::string> expectedResult1({ variable_value_one, variable_value_three });
	std::unordered_set<std::string> expectedResult2({ variable_value_one, variable_value_two });
	std::unordered_set<std::string> expectedResult3({});

	std::unordered_set<std::string> getRelationshipByStmt1 = *(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject1, TokenType::VARIABLE));
	std::unordered_set<std::string> getRelationshipByStmt2 = *(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject2, TokenType::VARIABLE));
	std::unordered_set<std::string> getRelationshipByStmt3 = *(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject3, TokenType::VARIABLE));
	std::unordered_set<std::string> getRelationshipByStmt4 = *(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject4, TokenType::VARIABLE));
	std::unordered_set<std::string> getRelationshipByStmt5 = *(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject5, TokenType::VARIABLE));
	std::unordered_set<std::string> getRelationshipByStmt6 = *(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject6, TokenType::VARIABLE));
	std::unordered_set<std::string> getRelationshipByStmt7 = *(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject7, TokenType::VARIABLE));
	std::unordered_set<std::string> getRelationshipByStmt8 = *(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject8, TokenType::VARIABLE));
	std::unordered_set<std::string> getRelationshipByStmt9 = *(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject9, TokenType::VARIABLE));
	std::unordered_set<std::string> getRelationshipByStmt10 = *(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject10, TokenType::VARIABLE));
	std::unordered_set<std::string> getRelationshipByStmt11 = *(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject11, TokenType::VARIABLE));
	std::unordered_set<std::string> getRelationshipByStmt12 = *(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject12, TokenType::VARIABLE));
	std::unordered_set<std::string> getRelationshipByStmt13 = *(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject13, TokenType::VARIABLE));
	std::unordered_set<std::string> getRelationshipByStmt14 = *(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject14, TokenType::VARIABLE));
	std::unordered_set<std::string> getRelationshipByStmt15 = *(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject15, TokenType::VARIABLE));
	std::unordered_set<std::string> getRelationshipByStmt16 = *(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject16, TokenType::VARIABLE));
	std::unordered_set<std::string> getRelationshipByStmt17 = *(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject17, TokenType::VARIABLE));
	std::unordered_set<std::string> getRelationshipByStmt18 = *(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject18, TokenType::VARIABLE));

	REQUIRE(getRelationshipByStmt1 == expectedResult1);
	REQUIRE(getRelationshipByStmt2 == expectedResult3);

}