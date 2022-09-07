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

	std::unordered_set<std::string> getUsesRelationshipByStmt1 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject1, TokenType::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt2 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject2, TokenType::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt3 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject3, TokenType::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt4 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject4, TokenType::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt5 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject5, TokenType::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt6 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject6, TokenType::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt7 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject7, TokenType::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt8 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject8, TokenType::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt9 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject9, TokenType::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt10 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject10, TokenType::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt11 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject11, TokenType::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt12 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject12, TokenType::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt13 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject13, TokenType::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt14 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject14, TokenType::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt15 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject15, TokenType::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt16 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject16, TokenType::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt17 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject17, TokenType::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt18 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject18, TokenType::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByProcOne = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, procedureTokenObject, TokenType::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByProcTwo = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, procedureTokenObjectTwo, TokenType::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByProcThree = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, procedureTokenObjectThree, TokenType::VARIABLE);

	REQUIRE(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject1, TokenType::VARIABLE) == expectedResult3);
	REQUIRE(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS, stmtTokenObject1, TokenType::VARIABLE) == expectedResult3);
	REQUIRE(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS_T, stmtTokenObject1, TokenType::VARIABLE) == expectedResult3);
	REQUIRE(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject1, TokenType::VARIABLE) == expectedResult3);
	REQUIRE(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject1, TokenType::VARIABLE) == expectedResult3);

	REQUIRE(getUsesRelationshipByStmt1 == expectedResult1);
	REQUIRE(getUsesRelationshipByStmt2 == expectedResult3);
	REQUIRE(getUsesRelationshipByStmt3 == expectedResult1);
	REQUIRE(getUsesRelationshipByStmt4 == expectedResult1);
	REQUIRE(getUsesRelationshipByStmt5 == expectedResult3);
	REQUIRE(getUsesRelationshipByStmt6 == expectedResult1);
	REQUIRE(getUsesRelationshipByStmt7 == expectedResult2);
	REQUIRE(getUsesRelationshipByStmt8 == expectedResult3);
	REQUIRE(getUsesRelationshipByStmt9 == expectedResult2);
	REQUIRE(getUsesRelationshipByStmt10 == expectedResult2);
	REQUIRE(getUsesRelationshipByStmt11 == expectedResult3);
	REQUIRE(getUsesRelationshipByStmt12 == expectedResult2);
	REQUIRE(getUsesRelationshipByStmt13 == expectedResult3);
	REQUIRE(getUsesRelationshipByStmt14 == expectedResult3);
	REQUIRE(getUsesRelationshipByStmt15 == expectedResult3);
	REQUIRE(getUsesRelationshipByStmt16 == expectedResult3);
	REQUIRE(getUsesRelationshipByStmt17 == expectedResult3);
	REQUIRE(getUsesRelationshipByStmt18 == expectedResult3);
	REQUIRE(getUsesRelationshipByProcOne == expectedResult1);
	REQUIRE(getUsesRelationshipByProcTwo == expectedResult2);
	REQUIRE(getUsesRelationshipByProcThree == expectedResult3);

	std::unordered_set<std::string> getUsesAssignRelationshipByVarOne = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, TokenType::ASSIGN, variableTokenObject);
	std::unordered_set<std::string> getUsesAssignRelationshipByVarTwo = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, TokenType::ASSIGN, variableTokenObjectTwo);
	std::unordered_set<std::string> getUsesAssignRelationshipByVarThree = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, TokenType::ASSIGN, variableTokenObjectThree);
	std::unordered_set<std::string> getUsesProcRelationshipByVarOne = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, TokenType::PROCEDURE, variableTokenObject);
	std::unordered_set<std::string> getUsesProcRelationshipByVarTwo = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, TokenType::PROCEDURE, variableTokenObjectTwo);
	std::unordered_set<std::string> getUsesProcRelationshipByVarThree = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, TokenType::PROCEDURE, variableTokenObjectThree);
	std::unordered_set<std::string> getUsesPrintRelationshipByVarOne = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, TokenType::PRINT, variableTokenObject);
	std::unordered_set<std::string> getUsesPrintRelationshipByVarTwo = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, TokenType::PRINT, variableTokenObjectTwo);
	std::unordered_set<std::string> getUsesPrintRelationshipByVarThree = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, TokenType::PRINT, variableTokenObjectThree);
	std::unordered_set<std::string> getUsesWhileRelationshipByVarOne = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, TokenType::WHILE, variableTokenObject);
	std::unordered_set<std::string> getUsesWhileRelationshipByVarTwo = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, TokenType::WHILE, variableTokenObjectTwo);
	std::unordered_set<std::string> getUsesWhileRelationshipByVarThree = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, TokenType::WHILE, variableTokenObjectThree);
	std::unordered_set<std::string> getUsesIfRelationshipByVarOne = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, TokenType::IF, variableTokenObject);
	std::unordered_set<std::string> getUsesIfRelationshipByVarTwo = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, TokenType::IF, variableTokenObjectTwo);
	std::unordered_set<std::string> getUsesIfRelationshipByVarThree = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, TokenType::IF, variableTokenObjectThree);

	std::unordered_set<std::string> expectedResultAssignByVarOne({ assign_value_one, assign_value_two });
	std::unordered_set<std::string> expectedResultAssignByVarTwo({ assign_value_two });
	std::unordered_set<std::string> expectedResultAssignByVarThree({ assign_value_one });
	std::unordered_set<std::string> expectedResultProcByVarOne({ procedure_value_one, procedure_value_two });
	std::unordered_set<std::string> expectedResultProcByVarTwo({ procedure_value_two });
	std::unordered_set<std::string> expectedResultProcByVarThree({ procedure_value_one });
	std::unordered_set<std::string> expectedResultPrintByVarOne({ print_value_one, print_value_two });
	std::unordered_set<std::string> expectedResultPrintByVarTwo({ print_value_two });
	std::unordered_set<std::string> expectedResultPrintByVarThree({ print_value_one });
	std::unordered_set<std::string> expectedResultWhileByVarOne({ while_value_one, while_value_two });
	std::unordered_set<std::string> expectedResultWhileByVarTwo({ while_value_two });
	std::unordered_set<std::string> expectedResultWhileByVarThree({ while_value_one });
	std::unordered_set<std::string> expectedResultIfByVarOne({ if_value_one, if_value_two });
	std::unordered_set<std::string> expectedResultIfByVarTwo({ if_value_two });
	std::unordered_set<std::string> expectedResultIfByVarThree({ if_value_one });

	REQUIRE(usesRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, TokenType::ASSIGN, variableTokenObject) == expectedResult3);
	REQUIRE(usesRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS, TokenType::ASSIGN, variableTokenObject) == expectedResult3);
	REQUIRE(usesRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS_T, TokenType::ASSIGN, variableTokenObject) == expectedResult3);
	REQUIRE(usesRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT, TokenType::ASSIGN, variableTokenObject) == expectedResult3);
	REQUIRE(usesRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT_T, TokenType::ASSIGN, variableTokenObject) == expectedResult3);

	REQUIRE(getUsesAssignRelationshipByVarOne == expectedResultAssignByVarOne);
	REQUIRE(getUsesAssignRelationshipByVarTwo == expectedResultAssignByVarTwo);
	REQUIRE(getUsesAssignRelationshipByVarThree == expectedResultAssignByVarThree);
	REQUIRE(getUsesProcRelationshipByVarOne == expectedResultProcByVarOne);
	REQUIRE(getUsesProcRelationshipByVarTwo == expectedResultProcByVarTwo);
	REQUIRE(getUsesProcRelationshipByVarThree == expectedResultProcByVarThree);
	REQUIRE(getUsesPrintRelationshipByVarOne == expectedResultPrintByVarOne);
	REQUIRE(getUsesPrintRelationshipByVarTwo == expectedResultPrintByVarTwo);
	REQUIRE(getUsesPrintRelationshipByVarThree == expectedResultPrintByVarThree);
	REQUIRE(getUsesWhileRelationshipByVarOne == expectedResultWhileByVarOne);
	REQUIRE(getUsesWhileRelationshipByVarTwo == expectedResultWhileByVarTwo);
	REQUIRE(getUsesWhileRelationshipByVarThree == expectedResultWhileByVarThree);
	REQUIRE(getUsesIfRelationshipByVarOne == expectedResultIfByVarOne);
	REQUIRE(getUsesIfRelationshipByVarTwo == expectedResultIfByVarTwo);
	REQUIRE(getUsesIfRelationshipByVarThree == expectedResultIfByVarThree);

	std::unordered_set<std::string> getAllAssignUsesRelationship = usesRelationshipStorage->getAllRelationship(RelationshipType::USES, TokenType::ASSIGN);
	std::unordered_set<std::string> getAllProcUsesRelationship = usesRelationshipStorage->getAllRelationship(RelationshipType::USES, TokenType::PROCEDURE);
	std::unordered_set<std::string> getAllPrintUsesRelationship = usesRelationshipStorage->getAllRelationship(RelationshipType::USES, TokenType::PRINT);
	std::unordered_set<std::string> getAllWhileUsesRelationship = usesRelationshipStorage->getAllRelationship(RelationshipType::USES, TokenType::WHILE);
	std::unordered_set<std::string> getAllIfUsesRelationship = usesRelationshipStorage->getAllRelationship(RelationshipType::USES, TokenType::IF);

	std::unordered_set<std::string> expectedResultAllUsesAssign({ assign_value_one, assign_value_two });
	std::unordered_set<std::string> expectedResultAllUsesProc({ procedure_value_one, procedure_value_two });
	std::unordered_set<std::string> expectedResultAllUsesPrint({ print_value_one, print_value_two });
	std::unordered_set<std::string> expectedResultAllUsesWhile({ while_value_one, while_value_two });
	std::unordered_set<std::string> expectedResultAllUsesIf({ if_value_one, if_value_two });

	REQUIRE(usesRelationshipStorage->getAllRelationship(RelationshipType::MODIFIES, TokenType::ASSIGN) == expectedResult3);
	REQUIRE(usesRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS, TokenType::ASSIGN) == expectedResult3);
	REQUIRE(usesRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS_T, TokenType::ASSIGN) == expectedResult3);
	REQUIRE(usesRelationshipStorage->getAllRelationship(RelationshipType::PARENT, TokenType::ASSIGN) == expectedResult3);
	REQUIRE(usesRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T, TokenType::ASSIGN) == expectedResult3);

	REQUIRE(getAllAssignUsesRelationship == expectedResultAllUsesAssign);
	REQUIRE(getAllProcUsesRelationship == expectedResultAllUsesProc);
	REQUIRE(getAllPrintUsesRelationship == expectedResultAllUsesPrint);
	REQUIRE(getAllWhileUsesRelationship == expectedResultAllUsesWhile);
	REQUIRE(getAllIfUsesRelationship == expectedResultAllUsesIf);

}