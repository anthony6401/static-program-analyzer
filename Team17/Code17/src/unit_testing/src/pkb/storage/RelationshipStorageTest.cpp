#include <catch.hpp>

#include "components/pkb/storage/RelationshipStorage/RelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/UsesRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/ModifyRelationshipStorage.h"
#include "../RelationshipObject.h"
#include "../ReuseableTokenObject.h"

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

TEST_CASE("modify Relationship Storage Test") {
	RelationshipStorage* modifyRelationshipStorage = new ModifyRelationshipStorage();

	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipAssignOne));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipAssignTwo));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipAssignOneDuplicate));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipAssignTwoDuplicate));

	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipProcOne));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipProcTwo));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipProcOneDuplicate));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipProcTwoDuplicate));

	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipReadOne));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipReadTwo));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipReadOneDuplicate));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipReadTwoDuplicate));

	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipWhileOne));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipWhileTwo));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipWhileOneDuplicate));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipWhileTwoDuplicate));

	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipIfOne));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipIfTwo));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipIfOneDuplicate));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipIfTwoDuplicate));

	REQUIRE(!modifyRelationshipStorage->storeRelationship(modifyRelationshipAssignOne));

	REQUIRE(modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject1, variableTokenObject));
	REQUIRE(modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject1, variableTokenObjectThree));
	REQUIRE(modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject7, variableTokenObject));
	REQUIRE(modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject7, variableTokenObjectTwo));

	REQUIRE(modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, procedureTokenObject, variableTokenObject));
	REQUIRE(modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, procedureTokenObject, variableTokenObjectThree));
	REQUIRE(modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, procedureTokenObjectTwo, variableTokenObject));
	REQUIRE(modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, procedureTokenObjectTwo, variableTokenObjectTwo));

	REQUIRE(modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject3, variableTokenObject));
	REQUIRE(modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject3, variableTokenObjectThree));
	REQUIRE(modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject9, variableTokenObject));
	REQUIRE(modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject9, variableTokenObjectTwo));

	REQUIRE(modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject5, variableTokenObject));
	REQUIRE(modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject5, variableTokenObjectThree));
	REQUIRE(modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject11, variableTokenObject));
	REQUIRE(modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject11, variableTokenObjectTwo));

	REQUIRE(modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject6, variableTokenObject));
	REQUIRE(modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject6, variableTokenObjectThree));
	REQUIRE(modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject12, variableTokenObject));
	REQUIRE(modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject12, variableTokenObjectTwo));

	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::USES, stmtTokenObject1, variableTokenObject));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject1, variableTokenObject));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject1, variableTokenObject));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::PARENT, stmtTokenObject1, variableTokenObject));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::PARENT_T, stmtTokenObject1, variableTokenObject));

	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject1, variableTokenObjectTwo));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject7, variableTokenObjectThree));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject13, variableTokenObject));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject13, variableTokenObjectTwo));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject13, variableTokenObjectThree));

	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, procedureTokenObject, variableTokenObjectTwo));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, procedureTokenObjectTwo, variableTokenObjectThree));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, procedureTokenObjectThree, variableTokenObject));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, procedureTokenObjectThree, variableTokenObjectTwo));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, procedureTokenObjectThree, variableTokenObjectThree));

	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject3, variableTokenObjectTwo));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject9, variableTokenObjectThree));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject15, variableTokenObject));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject15, variableTokenObjectTwo));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject15, variableTokenObjectThree));

	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject4, variableTokenObjectTwo));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject10, variableTokenObjectThree));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject16, variableTokenObject));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject16, variableTokenObjectTwo));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject16, variableTokenObjectThree));

	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject6, variableTokenObjectTwo));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject12, variableTokenObjectThree));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject18, variableTokenObject));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject18, variableTokenObjectTwo));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject18, variableTokenObjectThree));

	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject2, variableTokenObjectTwo));
	REQUIRE(!modifyRelationshipStorage->getRelationship(RelationshipType::MODIFIES, stmtTokenObject4, variableTokenObjectThree));

	std::unordered_set<std::string> expectedResult1({ variable_value_one, variable_value_three });
	std::unordered_set<std::string> expectedResult2({ variable_value_one, variable_value_two });
	std::unordered_set<std::string> expectedResult3({});

	std::unordered_set<std::string> getModifyRelationshipByStmt1 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject1, TokenType::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt2 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject2, TokenType::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt3 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject3, TokenType::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt4 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject4, TokenType::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt5 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject5, TokenType::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt6 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject6, TokenType::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt7 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject7, TokenType::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt8 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject8, TokenType::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt9 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject9, TokenType::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt10 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject10, TokenType::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt11 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject11, TokenType::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt12 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject12, TokenType::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt13 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject13, TokenType::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt14 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject14, TokenType::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt15 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject15, TokenType::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt16 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject16, TokenType::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt17 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject17, TokenType::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt18 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject18, TokenType::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByProcOne = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, procedureTokenObject, TokenType::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByProcTwo = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, procedureTokenObjectTwo, TokenType::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByProcThree = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, procedureTokenObjectThree, TokenType::VARIABLE);

	REQUIRE(modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject1, TokenType::VARIABLE) == expectedResult3);
	REQUIRE(modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS, stmtTokenObject1, TokenType::VARIABLE) == expectedResult3);
	REQUIRE(modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS_T, stmtTokenObject1, TokenType::VARIABLE) == expectedResult3);
	REQUIRE(modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject1, TokenType::VARIABLE) == expectedResult3);
	REQUIRE(modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject1, TokenType::VARIABLE) == expectedResult3);

	REQUIRE(getModifyRelationshipByStmt1 == expectedResult1);
	REQUIRE(getModifyRelationshipByStmt2 == expectedResult3);
	REQUIRE(getModifyRelationshipByStmt3 == expectedResult1);
	REQUIRE(getModifyRelationshipByStmt4 == expectedResult3);
	REQUIRE(getModifyRelationshipByStmt5 == expectedResult1);
	REQUIRE(getModifyRelationshipByStmt6 == expectedResult1);
	REQUIRE(getModifyRelationshipByStmt7 == expectedResult2);
	REQUIRE(getModifyRelationshipByStmt8 == expectedResult3);
	REQUIRE(getModifyRelationshipByStmt9 == expectedResult2);
	REQUIRE(getModifyRelationshipByStmt10 == expectedResult3);
	REQUIRE(getModifyRelationshipByStmt11 == expectedResult2);
	REQUIRE(getModifyRelationshipByStmt12 == expectedResult2);
	REQUIRE(getModifyRelationshipByStmt13 == expectedResult3);
	REQUIRE(getModifyRelationshipByStmt14 == expectedResult3);
	REQUIRE(getModifyRelationshipByStmt15 == expectedResult3);
	REQUIRE(getModifyRelationshipByStmt16 == expectedResult3);
	REQUIRE(getModifyRelationshipByStmt17 == expectedResult3);
	REQUIRE(getModifyRelationshipByStmt18 == expectedResult3);
	REQUIRE(getModifyRelationshipByProcOne == expectedResult1);
	REQUIRE(getModifyRelationshipByProcTwo == expectedResult2);
	REQUIRE(getModifyRelationshipByProcThree == expectedResult3);

	std::unordered_set<std::string> getModifyAssignRelationshipByVarOne = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, TokenType::ASSIGN, variableTokenObject);
	std::unordered_set<std::string> getModifyAssignRelationshipByVarTwo = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, TokenType::ASSIGN, variableTokenObjectTwo);
	std::unordered_set<std::string> getModifyAssignRelationshipByVarThree = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, TokenType::ASSIGN, variableTokenObjectThree);
	std::unordered_set<std::string> getModifyProcRelationshipByVarOne = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, TokenType::PROCEDURE, variableTokenObject);
	std::unordered_set<std::string> getModifyProcRelationshipByVarTwo = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, TokenType::PROCEDURE, variableTokenObjectTwo);
	std::unordered_set<std::string> getModifyProcRelationshipByVarThree = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, TokenType::PROCEDURE, variableTokenObjectThree);
	std::unordered_set<std::string> getModifyReadRelationshipByVarOne = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, TokenType::READ, variableTokenObject);
	std::unordered_set<std::string> getModifyReadRelationshipByVarTwo = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, TokenType::READ, variableTokenObjectTwo);
	std::unordered_set<std::string> getModifyReadRelationshipByVarThree = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, TokenType::READ, variableTokenObjectThree);
	std::unordered_set<std::string> getModifyWhileRelationshipByVarOne = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, TokenType::WHILE, variableTokenObject);
	std::unordered_set<std::string> getModifyWhileRelationshipByVarTwo = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, TokenType::WHILE, variableTokenObjectTwo);
	std::unordered_set<std::string> getModifyWhileRelationshipByVarThree = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, TokenType::WHILE, variableTokenObjectThree);
	std::unordered_set<std::string> getModifyIfRelationshipByVarOne = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, TokenType::IF, variableTokenObject);
	std::unordered_set<std::string> getModifyIfRelationshipByVarTwo = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, TokenType::IF, variableTokenObjectTwo);
	std::unordered_set<std::string> getModifyIfRelationshipByVarThree = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, TokenType::IF, variableTokenObjectThree);

	std::unordered_set<std::string> expectedResultAssignByVarOne({ assign_value_one, assign_value_two });
	std::unordered_set<std::string> expectedResultAssignByVarTwo({ assign_value_two });
	std::unordered_set<std::string> expectedResultAssignByVarThree({ assign_value_one });
	std::unordered_set<std::string> expectedResultProcByVarOne({ procedure_value_one, procedure_value_two });
	std::unordered_set<std::string> expectedResultProcByVarTwo({ procedure_value_two });
	std::unordered_set<std::string> expectedResultProcByVarThree({ procedure_value_one });
	std::unordered_set<std::string> expectedResultReadByVarOne({ read_value_one, read_value_two });
	std::unordered_set<std::string> expectedResultReadByVarTwo({ read_value_two });
	std::unordered_set<std::string> expectedResultReadByVarThree({ read_value_one });
	std::unordered_set<std::string> expectedResultWhileByVarOne({ while_value_one, while_value_two });
	std::unordered_set<std::string> expectedResultWhileByVarTwo({ while_value_two });
	std::unordered_set<std::string> expectedResultWhileByVarThree({ while_value_one });
	std::unordered_set<std::string> expectedResultIfByVarOne({ if_value_one, if_value_two });
	std::unordered_set<std::string> expectedResultIfByVarTwo({ if_value_two });
	std::unordered_set<std::string> expectedResultIfByVarThree({ if_value_one });

	REQUIRE(modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, TokenType::ASSIGN, variableTokenObject) == expectedResult3);
	REQUIRE(modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS, TokenType::ASSIGN, variableTokenObject) == expectedResult3);
	REQUIRE(modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS_T, TokenType::ASSIGN, variableTokenObject) == expectedResult3);
	REQUIRE(modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT, TokenType::ASSIGN, variableTokenObject) == expectedResult3);
	REQUIRE(modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT_T, TokenType::ASSIGN, variableTokenObject) == expectedResult3);

	REQUIRE(getModifyAssignRelationshipByVarOne == expectedResultAssignByVarOne);
	REQUIRE(getModifyAssignRelationshipByVarTwo == expectedResultAssignByVarTwo);
	REQUIRE(getModifyAssignRelationshipByVarThree == expectedResultAssignByVarThree);
	REQUIRE(getModifyProcRelationshipByVarOne == expectedResultProcByVarOne);
	REQUIRE(getModifyProcRelationshipByVarTwo == expectedResultProcByVarTwo);
	REQUIRE(getModifyProcRelationshipByVarThree == expectedResultProcByVarThree);
	REQUIRE(getModifyReadRelationshipByVarOne == expectedResultReadByVarOne);
	REQUIRE(getModifyReadRelationshipByVarTwo == expectedResultReadByVarTwo);
	REQUIRE(getModifyReadRelationshipByVarThree == expectedResultReadByVarThree);
	REQUIRE(getModifyWhileRelationshipByVarOne == expectedResultWhileByVarOne);
	REQUIRE(getModifyWhileRelationshipByVarTwo == expectedResultWhileByVarTwo);
	REQUIRE(getModifyWhileRelationshipByVarThree == expectedResultWhileByVarThree);
	REQUIRE(getModifyIfRelationshipByVarOne == expectedResultIfByVarOne);
	REQUIRE(getModifyIfRelationshipByVarTwo == expectedResultIfByVarTwo);
	REQUIRE(getModifyIfRelationshipByVarThree == expectedResultIfByVarThree);

	std::unordered_set<std::string> getAllAssignmodifyRelationship = modifyRelationshipStorage->getAllRelationship(RelationshipType::MODIFIES, TokenType::ASSIGN);
	std::unordered_set<std::string> getAllProcmodifyRelationship = modifyRelationshipStorage->getAllRelationship(RelationshipType::MODIFIES, TokenType::PROCEDURE);
	std::unordered_set<std::string> getAllReadmodifyRelationship = modifyRelationshipStorage->getAllRelationship(RelationshipType::MODIFIES, TokenType::READ);
	std::unordered_set<std::string> getAllWhilemodifyRelationship = modifyRelationshipStorage->getAllRelationship(RelationshipType::MODIFIES, TokenType::WHILE);
	std::unordered_set<std::string> getAllIfmodifyRelationship = modifyRelationshipStorage->getAllRelationship(RelationshipType::MODIFIES, TokenType::IF);

	std::unordered_set<std::string> expectedResultAllModifyAssign({ assign_value_one, assign_value_two });
	std::unordered_set<std::string> expectedResultAllModifyProc({ procedure_value_one, procedure_value_two });
	std::unordered_set<std::string> expectedResultAllModifyRead({ read_value_one, read_value_two });
	std::unordered_set<std::string> expectedResultAllModifyWhile({ while_value_one, while_value_two });
	std::unordered_set<std::string> expectedResultAllModifyIf({ if_value_one, if_value_two });

	REQUIRE(modifyRelationshipStorage->getAllRelationship(RelationshipType::USES, TokenType::ASSIGN) == expectedResult3);
	REQUIRE(modifyRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS, TokenType::ASSIGN) == expectedResult3);
	REQUIRE(modifyRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS_T, TokenType::ASSIGN) == expectedResult3);
	REQUIRE(modifyRelationshipStorage->getAllRelationship(RelationshipType::PARENT, TokenType::ASSIGN) == expectedResult3);
	REQUIRE(modifyRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T, TokenType::ASSIGN) == expectedResult3);

	REQUIRE(getAllAssignmodifyRelationship == expectedResultAllModifyAssign);
	REQUIRE(getAllProcmodifyRelationship == expectedResultAllModifyProc);
	REQUIRE(getAllReadmodifyRelationship == expectedResultAllModifyRead);
	REQUIRE(getAllWhilemodifyRelationship == expectedResultAllModifyWhile);
	REQUIRE(getAllIfmodifyRelationship == expectedResultAllModifyIf);
}
