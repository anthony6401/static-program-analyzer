#include <catch.hpp>

#include "components/pkb/storage/RelationshipStorage/RelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/UsesRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/ModifyRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/ParentRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/ParentTRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/FollowsRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/FollowsTRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/NextTRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/NextRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/CallsRelationshipStorage.h"

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

	std::unordered_set<std::string> getUsesRelationshipByStmt1 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject1, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt2 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject2, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt3 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject3, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt4 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject4, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt5 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject5, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt6 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject6, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt7 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject7, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt8 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject8, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt9 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject9, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt10 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject10, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt11 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject11, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt12 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject12, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt13 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject13, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt14 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject14, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt15 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject15, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt16 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject16, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt17 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject17, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByStmt18 = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject18, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByProcOne = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, procedureTokenObject, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByProcTwo = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, procedureTokenObjectTwo, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getUsesRelationshipByProcThree = usesRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, procedureTokenObjectThree, DesignEntity::VARIABLE);

	REQUIRE(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject1, DesignEntity::VARIABLE) == expectedResult3);
	REQUIRE(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS, stmtTokenObject1, DesignEntity::VARIABLE) == expectedResult3);
	REQUIRE(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS_T, stmtTokenObject1, DesignEntity::VARIABLE) == expectedResult3);
	REQUIRE(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject1, DesignEntity::VARIABLE) == expectedResult3);
	REQUIRE(usesRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject1, DesignEntity::VARIABLE) == expectedResult3);

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

	std::unordered_set<std::string> getUsesAssignRelationshipByVarOne = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, DesignEntity::ASSIGN, variableTokenObject);
	std::unordered_set<std::string> getUsesAssignRelationshipByVarTwo = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, DesignEntity::ASSIGN, variableTokenObjectTwo);
	std::unordered_set<std::string> getUsesAssignRelationshipByVarThree = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, DesignEntity::ASSIGN, variableTokenObjectThree);
	std::unordered_set<std::string> getUsesProcRelationshipByVarOne = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, DesignEntity::PROCEDURE, variableTokenObject);
	std::unordered_set<std::string> getUsesProcRelationshipByVarTwo = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, DesignEntity::PROCEDURE, variableTokenObjectTwo);
	std::unordered_set<std::string> getUsesProcRelationshipByVarThree = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, DesignEntity::PROCEDURE, variableTokenObjectThree);
	std::unordered_set<std::string> getUsesPrintRelationshipByVarOne = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, DesignEntity::PRINT, variableTokenObject);
	std::unordered_set<std::string> getUsesPrintRelationshipByVarTwo = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, DesignEntity::PRINT, variableTokenObjectTwo);
	std::unordered_set<std::string> getUsesPrintRelationshipByVarThree = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, DesignEntity::PRINT, variableTokenObjectThree);
	std::unordered_set<std::string> getUsesWhileRelationshipByVarOne = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, DesignEntity::WHILE, variableTokenObject);
	std::unordered_set<std::string> getUsesWhileRelationshipByVarTwo = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, DesignEntity::WHILE, variableTokenObjectTwo);
	std::unordered_set<std::string> getUsesWhileRelationshipByVarThree = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, DesignEntity::WHILE, variableTokenObjectThree);
	std::unordered_set<std::string> getUsesIfRelationshipByVarOne = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, DesignEntity::IF, variableTokenObject);
	std::unordered_set<std::string> getUsesIfRelationshipByVarTwo = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, DesignEntity::IF, variableTokenObjectTwo);
	std::unordered_set<std::string> getUsesIfRelationshipByVarThree = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, DesignEntity::IF, variableTokenObjectThree);
	std::unordered_set<std::string> getUsesStmtRelationshipByVarOne = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, DesignEntity::STMT, variableTokenObject);
	std::unordered_set<std::string> getUsesStmtRelationshipByVarTwo = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, DesignEntity::STMT, variableTokenObjectTwo);
	std::unordered_set<std::string> getUsesStmtRelationshipByVarThree = usesRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, DesignEntity::STMT, variableTokenObjectThree);

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
	std::unordered_set<std::string> expectedResultStmtByVarOne({ assign_value_one, assign_value_two, print_value_one, print_value_two, while_value_one, while_value_two, if_value_one, if_value_two });
	std::unordered_set<std::string> expectedResultStmtByVarTwo({ assign_value_two, print_value_two, while_value_two, if_value_two});
	std::unordered_set<std::string> expectedResultStmtByVarThree({ assign_value_one, print_value_one, while_value_one, if_value_one });

	REQUIRE(usesRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::ASSIGN, variableTokenObject) == expectedResult3);
	REQUIRE(usesRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS, DesignEntity::ASSIGN, variableTokenObject) == expectedResult3);
	REQUIRE(usesRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS_T, DesignEntity::ASSIGN, variableTokenObject) == expectedResult3);
	REQUIRE(usesRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::ASSIGN, variableTokenObject) == expectedResult3);
	REQUIRE(usesRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::ASSIGN, variableTokenObject) == expectedResult3);

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
	REQUIRE(getUsesStmtRelationshipByVarOne == expectedResultStmtByVarOne);
	REQUIRE(getUsesStmtRelationshipByVarTwo == expectedResultStmtByVarTwo);
	REQUIRE(getUsesStmtRelationshipByVarThree == expectedResultStmtByVarThree);

	std::unordered_map<std::string, std::unordered_set<std::string>> getAllAssignUsesRelationship = usesRelationshipStorage->getAllRelationship(RelationshipType::USES, DesignEntity::ASSIGN, DesignEntity::VARIABLE);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllProcUsesRelationship = usesRelationshipStorage->getAllRelationship(RelationshipType::USES, DesignEntity::PROCEDURE, DesignEntity::VARIABLE);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllPrintUsesRelationship = usesRelationshipStorage->getAllRelationship(RelationshipType::USES, DesignEntity::PRINT, DesignEntity::VARIABLE);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllWhileUsesRelationship = usesRelationshipStorage->getAllRelationship(RelationshipType::USES, DesignEntity::WHILE, DesignEntity::VARIABLE);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllIfUsesRelationship = usesRelationshipStorage->getAllRelationship(RelationshipType::USES, DesignEntity::IF, DesignEntity::VARIABLE);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllStmtUsesRelationship = usesRelationshipStorage->getAllRelationship(RelationshipType::USES, DesignEntity::STMT, DesignEntity::VARIABLE);

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAllUsesNone({});
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAllUsesAssign{ { assign_value_one, std::unordered_set<std::string>({variable_value_one, variable_value_three}) },
																									{ assign_value_two, std::unordered_set<std::string>({variable_value_one, variable_value_two})} };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAllUsesProc{ { procedure_value_one, std::unordered_set<std::string>({variable_value_one, variable_value_three}) },
																									{ procedure_value_two, std::unordered_set<std::string>({variable_value_one, variable_value_two}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAllUsesPrint{ { print_value_one, std::unordered_set<std::string>({variable_value_one, variable_value_three}) },
																									{ print_value_two, std::unordered_set<std::string>({variable_value_one, variable_value_two}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAllUsesWhile{ { while_value_one, std::unordered_set<std::string>({variable_value_one, variable_value_three}) },
																									{ while_value_two, std::unordered_set<std::string>({variable_value_one, variable_value_two}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAllUsesIf{ { if_value_one, std::unordered_set<std::string>({variable_value_one, variable_value_three}) },
																									{ if_value_two, std::unordered_set<std::string>({variable_value_one, variable_value_two}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAllUsesStmt;
	expectedResultAllUsesStmt.insert(expectedResultAllUsesAssign.begin(), expectedResultAllUsesAssign.end());
	expectedResultAllUsesStmt.insert(expectedResultAllUsesPrint.begin(), expectedResultAllUsesPrint.end());
	expectedResultAllUsesStmt.insert(expectedResultAllUsesWhile.begin(), expectedResultAllUsesWhile.end());
	expectedResultAllUsesStmt.insert(expectedResultAllUsesIf.begin(), expectedResultAllUsesIf.end());

	REQUIRE(usesRelationshipStorage->getAllRelationship(RelationshipType::MODIFIES, DesignEntity::ASSIGN, DesignEntity::VARIABLE) == expectedResultAllUsesNone);
	REQUIRE(usesRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS, DesignEntity::ASSIGN, DesignEntity::VARIABLE) == expectedResultAllUsesNone);
	REQUIRE(usesRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS_T, DesignEntity::ASSIGN, DesignEntity::VARIABLE) == expectedResultAllUsesNone);
	REQUIRE(usesRelationshipStorage->getAllRelationship(RelationshipType::PARENT, DesignEntity::ASSIGN, DesignEntity::VARIABLE) == expectedResultAllUsesNone);
	REQUIRE(usesRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T, DesignEntity::ASSIGN, DesignEntity::VARIABLE) == expectedResultAllUsesNone);

	REQUIRE(getAllAssignUsesRelationship == expectedResultAllUsesAssign);
	REQUIRE(getAllProcUsesRelationship == expectedResultAllUsesProc);
	REQUIRE(getAllPrintUsesRelationship == expectedResultAllUsesPrint);
	REQUIRE(getAllWhileUsesRelationship == expectedResultAllUsesWhile);
	REQUIRE(getAllIfUsesRelationship == expectedResultAllUsesIf);
	REQUIRE(getAllStmtUsesRelationship == expectedResultAllUsesStmt);
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

	std::unordered_set<std::string> getModifyRelationshipByStmt1 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject1, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt2 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject2, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt3 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject3, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt4 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject4, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt5 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject5, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt6 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject6, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt7 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject7, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt8 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject8, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt9 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject9, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt10 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject10, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt11 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject11, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt12 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject12, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt13 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject13, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt14 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject14, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt15 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject15, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt16 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject16, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt17 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject17, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByStmt18 = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject18, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByProcOne = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, procedureTokenObject, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByProcTwo = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, procedureTokenObjectTwo, DesignEntity::VARIABLE);
	std::unordered_set<std::string> getModifyRelationshipByProcThree = modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::MODIFIES, procedureTokenObjectThree, DesignEntity::VARIABLE);

	REQUIRE(modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::USES, stmtTokenObject1, DesignEntity::VARIABLE) == expectedResult3);
	REQUIRE(modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS, stmtTokenObject1, DesignEntity::VARIABLE) == expectedResult3);
	REQUIRE(modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS_T, stmtTokenObject1, DesignEntity::VARIABLE) == expectedResult3);
	REQUIRE(modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject1, DesignEntity::VARIABLE) == expectedResult3);
	REQUIRE(modifyRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject1, DesignEntity::VARIABLE) == expectedResult3);

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

	std::unordered_set<std::string> getModifyAssignRelationshipByVarOne = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::ASSIGN, variableTokenObject);
	std::unordered_set<std::string> getModifyAssignRelationshipByVarTwo = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::ASSIGN, variableTokenObjectTwo);
	std::unordered_set<std::string> getModifyAssignRelationshipByVarThree = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::ASSIGN, variableTokenObjectThree);
	std::unordered_set<std::string> getModifyProcRelationshipByVarOne = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::PROCEDURE, variableTokenObject);
	std::unordered_set<std::string> getModifyProcRelationshipByVarTwo = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::PROCEDURE, variableTokenObjectTwo);
	std::unordered_set<std::string> getModifyProcRelationshipByVarThree = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::PROCEDURE, variableTokenObjectThree);
	std::unordered_set<std::string> getModifyReadRelationshipByVarOne = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::READ, variableTokenObject);
	std::unordered_set<std::string> getModifyReadRelationshipByVarTwo = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::READ, variableTokenObjectTwo);
	std::unordered_set<std::string> getModifyReadRelationshipByVarThree = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::READ, variableTokenObjectThree);
	std::unordered_set<std::string> getModifyWhileRelationshipByVarOne = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::WHILE, variableTokenObject);
	std::unordered_set<std::string> getModifyWhileRelationshipByVarTwo = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::WHILE, variableTokenObjectTwo);
	std::unordered_set<std::string> getModifyWhileRelationshipByVarThree = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::WHILE, variableTokenObjectThree);
	std::unordered_set<std::string> getModifyIfRelationshipByVarOne = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::IF, variableTokenObject);
	std::unordered_set<std::string> getModifyIfRelationshipByVarTwo = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::IF, variableTokenObjectTwo);
	std::unordered_set<std::string> getModifyIfRelationshipByVarThree = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::IF, variableTokenObjectThree);
	std::unordered_set<std::string> getModifyStmtRelationshipByVarOne = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::STMT, variableTokenObject);
	std::unordered_set<std::string> getModifyStmtRelationshipByVarTwo = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::STMT, variableTokenObjectTwo);
	std::unordered_set<std::string> getModifyStmtRelationshipByVarThree = modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::STMT, variableTokenObjectThree);

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
	std::unordered_set<std::string> expectedResultStmtByVarOne({ assign_value_one, assign_value_two, read_value_one, read_value_two, while_value_one, while_value_two, if_value_one, if_value_two });
	std::unordered_set<std::string> expectedResultStmtByVarTwo({ assign_value_two, read_value_two, while_value_two, if_value_two });
	std::unordered_set<std::string> expectedResultStmtByVarThree({ assign_value_one, read_value_one, while_value_one, if_value_one });

	REQUIRE(modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::USES, DesignEntity::ASSIGN, variableTokenObject) == expectedResult3);
	REQUIRE(modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS, DesignEntity::ASSIGN, variableTokenObject) == expectedResult3);
	REQUIRE(modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS_T, DesignEntity::ASSIGN, variableTokenObject) == expectedResult3);
	REQUIRE(modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::ASSIGN, variableTokenObject) == expectedResult3);
	REQUIRE(modifyRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::ASSIGN, variableTokenObject) == expectedResult3);

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
	REQUIRE(getModifyStmtRelationshipByVarOne == expectedResultStmtByVarOne);
	REQUIRE(getModifyStmtRelationshipByVarTwo == expectedResultStmtByVarTwo);
	REQUIRE(getModifyStmtRelationshipByVarThree == expectedResultStmtByVarThree);

	std::unordered_map<std::string, std::unordered_set<std::string>> getAllAssignModifyRelationship = modifyRelationshipStorage->getAllRelationship(RelationshipType::MODIFIES, DesignEntity::ASSIGN, DesignEntity::VARIABLE);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllProcModifyRelationship = modifyRelationshipStorage->getAllRelationship(RelationshipType::MODIFIES, DesignEntity::PROCEDURE, DesignEntity::VARIABLE);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllReadModifyRelationship = modifyRelationshipStorage->getAllRelationship(RelationshipType::MODIFIES, DesignEntity::READ, DesignEntity::VARIABLE);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllWhileModifyRelationship = modifyRelationshipStorage->getAllRelationship(RelationshipType::MODIFIES, DesignEntity::WHILE, DesignEntity::VARIABLE);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllIfModifyRelationship = modifyRelationshipStorage->getAllRelationship(RelationshipType::MODIFIES, DesignEntity::IF, DesignEntity::VARIABLE);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllStmtModifyRelationship = modifyRelationshipStorage->getAllRelationship(RelationshipType::MODIFIES, DesignEntity::STMT, DesignEntity::VARIABLE);

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAllModifyNone({});
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAllModifyAssign{ { assign_value_one, std::unordered_set<std::string>({variable_value_one, variable_value_three}) },
																									{ assign_value_two, std::unordered_set<std::string>({variable_value_one, variable_value_two})} };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAllModifyProc{ { procedure_value_one, std::unordered_set<std::string>({variable_value_one, variable_value_three}) },
																									{ procedure_value_two, std::unordered_set<std::string>({variable_value_one, variable_value_two}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAllModifyRead{ { read_value_one, std::unordered_set<std::string>({variable_value_one, variable_value_three}) },
																									{ read_value_two, std::unordered_set<std::string>({variable_value_one, variable_value_two}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAllModifyWhile{ { while_value_one, std::unordered_set<std::string>({variable_value_one, variable_value_three}) },
																									{ while_value_two, std::unordered_set<std::string>({variable_value_one, variable_value_two}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAllModifyIf{ { if_value_one, std::unordered_set<std::string>({variable_value_one, variable_value_three}) },
																									{ if_value_two, std::unordered_set<std::string>({variable_value_one, variable_value_two}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAllModifyStmt;
	expectedResultAllModifyStmt.insert(expectedResultAllModifyAssign.begin(), expectedResultAllModifyAssign.end());
	expectedResultAllModifyStmt.insert(expectedResultAllModifyRead.begin(), expectedResultAllModifyRead.end());
	expectedResultAllModifyStmt.insert(expectedResultAllModifyWhile.begin(), expectedResultAllModifyWhile.end());
	expectedResultAllModifyStmt.insert(expectedResultAllModifyIf.begin(), expectedResultAllModifyIf.end());

	REQUIRE(modifyRelationshipStorage->getAllRelationship(RelationshipType::USES, DesignEntity::ASSIGN, DesignEntity::VARIABLE) == expectedResultAllModifyNone);
	REQUIRE(modifyRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS, DesignEntity::ASSIGN, DesignEntity::VARIABLE) == expectedResultAllModifyNone);
	REQUIRE(modifyRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS_T, DesignEntity::ASSIGN, DesignEntity::VARIABLE) == expectedResultAllModifyNone);
	REQUIRE(modifyRelationshipStorage->getAllRelationship(RelationshipType::PARENT, DesignEntity::ASSIGN, DesignEntity::VARIABLE) == expectedResultAllModifyNone);
	REQUIRE(modifyRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T, DesignEntity::ASSIGN, DesignEntity::VARIABLE) == expectedResultAllModifyNone);

	REQUIRE(getAllAssignModifyRelationship == expectedResultAllModifyAssign);
	REQUIRE(getAllProcModifyRelationship == expectedResultAllModifyProc);
	REQUIRE(getAllReadModifyRelationship == expectedResultAllModifyRead);
	REQUIRE(getAllWhileModifyRelationship == expectedResultAllModifyWhile);
	REQUIRE(getAllIfModifyRelationship == expectedResultAllModifyIf);
	REQUIRE(getAllStmtModifyRelationship == expectedResultAllModifyStmt);
}


TEST_CASE("Parent Relationship Storage Test") {
	RelationshipStorage* parentRelationshipStorage = new ParentRelationshipStorage();

	// TESTING FOR STORING

	//Test While Entity
	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipWhileReadOne));
	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipWhileReadTwo));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipWhileReadDupOne));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipWhileReadDupTwo));

	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipWhilePrintOne));
	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipWhilePrintTwo));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipWhilePrintDupOne));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipWhilePrintDupTwo));

	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipWhileAssignOne));
	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipWhileAssignTwo));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipWhileAssignDupOne));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipWhileAssignDupTwo));

	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipWhileCallOne));
	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipWhileCallTwo));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipWhileCallDupOne));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipWhileCallDupTwo));

	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipWhileWhileOne));
	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipWhileWhileTwo));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipWhileWhileDupOne));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipWhileWhileDupTwo));

	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipWhileIfOne));
	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipWhileIfTwo));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipWhileIfDupOne));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipWhileIfDupTwo));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Test If Entity
	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipIfReadOne));
	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipIfReadTwo));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipIfReadDupOne));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipIfReadDupTwo));

	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipIfPrintOne));
	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipIfPrintTwo));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipIfPrintDupOne));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipIfPrintDupTwo));

	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipIfAssignOne));
	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipIfAssignTwo));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipIfAssignDupOne));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipIfAssignDupTwo));

	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipIfCallOne));
	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipIfCallTwo));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipIfCallDupOne));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipIfCallDupTwo));

	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipIfWhileOne));
	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipIfWhileTwo));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipIfWhileDupOne));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipIfWhileDupTwo));

	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipIfIfOne));
	REQUIRE(parentRelationshipStorage->storeRelationship(parentRelationshipIfIfTwo));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipIfIfDupOne));
	REQUIRE(!parentRelationshipStorage->storeRelationship(parentRelationshipIfIfDupTwo));

	REQUIRE(!parentRelationshipStorage->storeRelationship(modifyRelationshipAssignOne));

	//Testing for Parent(1,2) query
	//Testing for Whie entity
	REQUIRE(parentRelationshipStorage->getRelationship(RelationshipType::PARENT, stmtTokenObject6, stmtTokenObject5));
	REQUIRE(parentRelationshipStorage->getRelationship(RelationshipType::PARENT, stmtTokenObject6, stmtTokenObject4));
	REQUIRE(parentRelationshipStorage->getRelationship(RelationshipType::PARENT, stmtTokenObject6, stmtTokenObject1));
	REQUIRE(parentRelationshipStorage->getRelationship(RelationshipType::PARENT, stmtTokenObject6, stmtTokenObject2));
	REQUIRE(parentRelationshipStorage->getRelationship(RelationshipType::PARENT, stmtTokenObject6, stmtTokenObject12));
	REQUIRE(parentRelationshipStorage->getRelationship(RelationshipType::PARENT, stmtTokenObject6, stmtTokenObject3));

	//Testing for If entity
	REQUIRE(parentRelationshipStorage->getRelationship(RelationshipType::PARENT, stmtTokenObject3, stmtTokenObject5));
	REQUIRE(parentRelationshipStorage->getRelationship(RelationshipType::PARENT, stmtTokenObject3, stmtTokenObject4));
	REQUIRE(parentRelationshipStorage->getRelationship(RelationshipType::PARENT, stmtTokenObject3, stmtTokenObject1));
	REQUIRE(parentRelationshipStorage->getRelationship(RelationshipType::PARENT, stmtTokenObject3, stmtTokenObject2));
	REQUIRE(parentRelationshipStorage->getRelationship(RelationshipType::PARENT, stmtTokenObject3, stmtTokenObject6));
	REQUIRE(parentRelationshipStorage->getRelationship(RelationshipType::PARENT, stmtTokenObject3, stmtTokenObject9));

	//Testing for Parent(1,a), Parent(1,pr), etc
	//Test for While Entity
	std::unordered_set<std::string> whileReadTest{ read_value_one };
	std::unordered_set<std::string> whilePrintTest{ print_value_one };
	std::unordered_set<std::string> whileAssignTest{ assign_value_one };
	std::unordered_set<std::string> whileCallTest{ call_value_one };
	std::unordered_set<std::string> whileWhileTest{ while_value_two };
	std::unordered_set<std::string> whileIfTest{ if_value_one };
	std::unordered_set<std::string> whileStmtTest{ read_value_one, print_value_one, assign_value_one, call_value_one, while_value_two,
												   if_value_one };

	REQUIRE(parentRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject6, DesignEntity::READ) == whileReadTest);
	REQUIRE(parentRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject6, DesignEntity::PRINT) == whilePrintTest);
	REQUIRE(parentRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject6, DesignEntity::ASSIGN) == whileAssignTest);
	REQUIRE(parentRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject6, DesignEntity::CALL) == whileCallTest);
	REQUIRE(parentRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject6, DesignEntity::WHILE) == whileWhileTest);
	REQUIRE(parentRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject6, DesignEntity::IF) == whileIfTest);
	REQUIRE(parentRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject6, DesignEntity::STMT) == whileStmtTest);

	//Test for If Entity
	std::unordered_set<std::string> ifReadTest{ read_value_one };
	std::unordered_set<std::string> ifPrintTest{ print_value_one };
	std::unordered_set<std::string> ifAssignTest{ assign_value_one };
	std::unordered_set<std::string> ifCallTest{ call_value_one };
	std::unordered_set<std::string> ifWhileTest{ while_value_one };
	std::unordered_set<std::string> ifIfTest{ if_value_two };
	std::unordered_set<std::string> ifStmtTest{ read_value_one, print_value_one, assign_value_one, call_value_one, while_value_one,
												if_value_two };

	REQUIRE(parentRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject3, DesignEntity::READ) == ifReadTest);
	REQUIRE(parentRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject3, DesignEntity::PRINT) == ifPrintTest);
	REQUIRE(parentRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject3, DesignEntity::ASSIGN) == ifAssignTest);
	REQUIRE(parentRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject3, DesignEntity::CALL) == ifCallTest);
	REQUIRE(parentRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject3, DesignEntity::WHILE) == ifWhileTest);
	REQUIRE(parentRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject3, DesignEntity::IF) == ifIfTest);
	REQUIRE(parentRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject3, DesignEntity::STMT) == ifStmtTest);

	//Testing for Parent(s,2), Parent(w,2), and Parent(if,2)
	//Looking for w
	std::unordered_set<std::string> whileResult{ while_value_one };
	//
	REQUIRE(parentRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::WHILE, stmtTokenObject5) == whileResult);
	REQUIRE(parentRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::WHILE, stmtTokenObject4) == whileResult);
	REQUIRE(parentRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::WHILE, stmtTokenObject1) == whileResult);
	REQUIRE(parentRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::WHILE, stmtTokenObject2) == whileResult);
	REQUIRE(parentRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::WHILE, stmtTokenObject12) == whileResult);
	REQUIRE(parentRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::WHILE, stmtTokenObject3) == whileResult);

	////Looking for if
	std::unordered_set<std::string> ifResult{ if_value_one };

	REQUIRE(parentRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::IF, stmtTokenObject5) == ifResult);
	REQUIRE(parentRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::IF, stmtTokenObject4) == ifResult);
	REQUIRE(parentRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::IF, stmtTokenObject1) == ifResult);
	REQUIRE(parentRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::IF, stmtTokenObject2) == ifResult);
	REQUIRE(parentRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::IF, stmtTokenObject6) == ifResult);
	REQUIRE(parentRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::IF, stmtTokenObject9) == ifResult);


	//Looking for s
	std::unordered_set<std::string> statementResult{ while_value_one,if_value_one };

	REQUIRE(parentRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::STMT, stmtTokenObject5) == statementResult);
	REQUIRE(parentRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::STMT, stmtTokenObject4) == statementResult);
	REQUIRE(parentRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::STMT, stmtTokenObject1) == statementResult);
	REQUIRE(parentRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::STMT, stmtTokenObject2) == statementResult);


	//Testing for Parent(s,a),...,Parent(w,a),...,Parent(if,a),..., etc

	//Test While Entity


	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultWhileReadAll{ {while_value_one, std::unordered_set<std::string>({read_value_one}) },
																								 {while_value_two, std::unordered_set<std::string>({read_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultWhilePrintAll{ {while_value_one, std::unordered_set<std::string>({print_value_one}) },
																								  {while_value_two, std::unordered_set<std::string>({print_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultWhileAssignAll{ {while_value_one, std::unordered_set<std::string>({assign_value_one}) },
																								   {while_value_two, std::unordered_set<std::string>({assign_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultWhileCallAll{ {while_value_one, std::unordered_set<std::string>({call_value_one}) },
																								   {while_value_two, std::unordered_set<std::string>({call_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultWhileWhileAll{ {while_value_one, std::unordered_set<std::string>({while_value_two}) },
																								   {while_value_two, std::unordered_set<std::string>({while_value_three}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultWhileIfAll{ {while_value_one, std::unordered_set<std::string>({if_value_one})},
																								   {while_value_two, std::unordered_set<std::string>({if_value_two})} };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultWhileStmtAll{
										{while_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_one, call_value_one, while_value_two, if_value_one})},
										{while_value_two, std::unordered_set<std::string>({read_value_two, print_value_two, assign_value_two, call_value_two, while_value_three, if_value_two}) } };


	std::unordered_map<std::string, std::unordered_set<std::string>> whileReadAllResult = parentRelationshipStorage->getAllRelationship(RelationshipType::PARENT,
		DesignEntity::WHILE, DesignEntity::READ);

	std::unordered_map<std::string, std::unordered_set<std::string>> whilePrintAllResult = parentRelationshipStorage->getAllRelationship(RelationshipType::PARENT,
		DesignEntity::WHILE, DesignEntity::PRINT);
	std::unordered_map<std::string, std::unordered_set<std::string>> whileAssignAllResult = parentRelationshipStorage->getAllRelationship(RelationshipType::PARENT,
		DesignEntity::WHILE, DesignEntity::ASSIGN);
	std::unordered_map<std::string, std::unordered_set<std::string>> whileCallAllResult = parentRelationshipStorage->getAllRelationship(RelationshipType::PARENT,
		DesignEntity::WHILE, DesignEntity::CALL);
	std::unordered_map<std::string, std::unordered_set<std::string>> whileWhileAllResult = parentRelationshipStorage->getAllRelationship(RelationshipType::PARENT,
		DesignEntity::WHILE, DesignEntity::WHILE);
	std::unordered_map<std::string, std::unordered_set<std::string>> whileIfAllResult = parentRelationshipStorage->getAllRelationship(RelationshipType::PARENT,
		DesignEntity::WHILE, DesignEntity::IF);
	std::unordered_map<std::string, std::unordered_set<std::string>> whileStmtAllResult = parentRelationshipStorage->getAllRelationship(RelationshipType::PARENT,
		DesignEntity::WHILE, DesignEntity::STMT);
	//for (auto const& k : whileReadAllResult) {
	//	std::cout << k.first << "= (";
	//	for (auto const& v : k.second) {
	//		std::cout << v << " , ";
	//	}
	//	std::cout << ")" << std::endl;
	//}

	//for (auto const& k : expectedResultWhileReadAll) {
	//	std::cout << k.first << "= (";
	//	for (auto const& v : k.second) {
	//		std::cout << v << " , ";
	//	}
	//	std::cout << ")" << std::endl;
	//}

	REQUIRE(whileReadAllResult == expectedResultWhileReadAll);
	REQUIRE(whilePrintAllResult == expectedResultWhilePrintAll);
	REQUIRE(whileAssignAllResult == expectedResultWhileAssignAll);
	REQUIRE(whileCallAllResult == expectedResultWhileCallAll);
	REQUIRE(whileWhileAllResult == expectedResultWhileWhileAll);
	REQUIRE(whileIfAllResult == expectedResultWhileIfAll);
	REQUIRE(whileStmtAllResult == expectedResultWhileStmtAll);


	//Test for If Entity
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultIfReadAll{ {if_value_one, std::unordered_set<std::string>({read_value_one}) },
																								 {if_value_two, std::unordered_set<std::string>({read_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultIfPrintAll{ {if_value_one, std::unordered_set<std::string>({print_value_one}) },
																								  {if_value_two, std::unordered_set<std::string>({print_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultIfAssignAll{ {if_value_one, std::unordered_set<std::string>({assign_value_one}) },
																								   {if_value_two, std::unordered_set<std::string>({assign_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultIfCallAll{ {if_value_one, std::unordered_set<std::string>({call_value_one}) },
																								   {if_value_two, std::unordered_set<std::string>({call_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultIfWhileAll{ {if_value_one, std::unordered_set<std::string>({while_value_one}) },
																								   {if_value_two, std::unordered_set<std::string>({while_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultIfIfAll{ {if_value_one, std::unordered_set<std::string>({if_value_two})},
																								   {if_value_two, std::unordered_set<std::string>({if_value_three})} };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultIfStmtAll{
										{if_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_one, call_value_one, while_value_one, if_value_two})},
										{if_value_two, std::unordered_set<std::string>({read_value_two, print_value_two, assign_value_two, call_value_two, while_value_two, if_value_three}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> ifReadAllResult = parentRelationshipStorage->getAllRelationship(RelationshipType::PARENT,
		DesignEntity::IF, DesignEntity::READ);

	std::unordered_map<std::string, std::unordered_set<std::string>> ifPrintAllResult = parentRelationshipStorage->getAllRelationship(RelationshipType::PARENT,
		DesignEntity::IF, DesignEntity::PRINT);
	std::unordered_map<std::string, std::unordered_set<std::string>> ifAssignAllResult = parentRelationshipStorage->getAllRelationship(RelationshipType::PARENT,
		DesignEntity::IF, DesignEntity::ASSIGN);
	std::unordered_map<std::string, std::unordered_set<std::string>> ifCallAllResult = parentRelationshipStorage->getAllRelationship(RelationshipType::PARENT,
		DesignEntity::IF, DesignEntity::CALL);
	std::unordered_map<std::string, std::unordered_set<std::string>> ifWhileAllResult = parentRelationshipStorage->getAllRelationship(RelationshipType::PARENT,
		DesignEntity::IF, DesignEntity::WHILE);
	std::unordered_map<std::string, std::unordered_set<std::string>> ifIfAllResult = parentRelationshipStorage->getAllRelationship(RelationshipType::PARENT,
		DesignEntity::IF, DesignEntity::IF);
	std::unordered_map<std::string, std::unordered_set<std::string>> ifStmtAllResult = parentRelationshipStorage->getAllRelationship(RelationshipType::PARENT,
		DesignEntity::IF, DesignEntity::STMT);

	REQUIRE(ifReadAllResult == expectedResultIfReadAll);
	REQUIRE(ifPrintAllResult == expectedResultIfPrintAll);
	REQUIRE(ifAssignAllResult == expectedResultIfAssignAll);
	REQUIRE(ifCallAllResult == expectedResultIfCallAll);
	REQUIRE(ifWhileAllResult == expectedResultIfWhileAll);
	REQUIRE(ifIfAllResult == expectedResultIfIfAll);
	REQUIRE(ifStmtAllResult == expectedResultIfStmtAll);

	//Test for StatementEntity
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultStmtReadAll{
		{while_value_one, std::unordered_set<std::string>({read_value_one}) },
		{while_value_two, std::unordered_set<std::string>({read_value_two}) },
		{if_value_one, std::unordered_set<std::string>({read_value_one}) },
		{if_value_two, std::unordered_set<std::string>({read_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultStmtPrintAll{
		{while_value_one, std::unordered_set<std::string>({print_value_one}) },
		{while_value_two, std::unordered_set<std::string>({print_value_two}) },
		{if_value_one, std::unordered_set<std::string>({print_value_one}) },
		{if_value_two, std::unordered_set<std::string>({print_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultStmtAssignAll{
		{while_value_one, std::unordered_set<std::string>({assign_value_one}) },
		{while_value_two, std::unordered_set<std::string>({assign_value_two}) },
		{if_value_one, std::unordered_set<std::string>({assign_value_one}) },
		{if_value_two, std::unordered_set<std::string>({assign_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultStmtCallAll{
		{while_value_one, std::unordered_set<std::string>({call_value_one}) },
		{while_value_two, std::unordered_set<std::string>({call_value_two}) },
		{if_value_one, std::unordered_set<std::string>({call_value_one}) },
		{if_value_two, std::unordered_set<std::string>({call_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultStmtWhileAll{
		{while_value_one, std::unordered_set<std::string>({while_value_two}) },
		{while_value_two, std::unordered_set<std::string>({while_value_three}) },
		{if_value_one, std::unordered_set<std::string>({while_value_one}) },
		{if_value_two, std::unordered_set<std::string>({while_value_two}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultStmtIfAll{
		{while_value_one, std::unordered_set<std::string>({if_value_one}) },
		{while_value_two, std::unordered_set<std::string>({if_value_two}) },
		{if_value_one, std::unordered_set<std::string>({if_value_two}) },
		{if_value_two, std::unordered_set<std::string>({if_value_three}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultStmtStmtAll{
		{while_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_one, call_value_one, while_value_two, if_value_one})},
		{while_value_two, std::unordered_set<std::string>({read_value_two, print_value_two, assign_value_two, call_value_two, while_value_three, if_value_two}) },
		{if_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_one, call_value_one, while_value_one, if_value_two})},
		{if_value_two, std::unordered_set<std::string>({read_value_two, print_value_two, assign_value_two, call_value_two, while_value_two, if_value_three}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> stmtReadAllResult = parentRelationshipStorage->getAllRelationship(RelationshipType::PARENT,
		DesignEntity::STMT, DesignEntity::READ);

	std::unordered_map<std::string, std::unordered_set<std::string>> stmtPrintAllResult = parentRelationshipStorage->getAllRelationship(RelationshipType::PARENT,
		DesignEntity::STMT, DesignEntity::PRINT);
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtAssignAllResult = parentRelationshipStorage->getAllRelationship(RelationshipType::PARENT,
		DesignEntity::STMT, DesignEntity::ASSIGN);
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtCallAllResult = parentRelationshipStorage->getAllRelationship(RelationshipType::PARENT,
		DesignEntity::STMT, DesignEntity::CALL);
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtWhileAllResult = parentRelationshipStorage->getAllRelationship(RelationshipType::PARENT,
		DesignEntity::STMT, DesignEntity::WHILE);
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtIfAllResult = parentRelationshipStorage->getAllRelationship(RelationshipType::PARENT,
		DesignEntity::STMT, DesignEntity::IF);
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtStmtAllResult = parentRelationshipStorage->getAllRelationship(RelationshipType::PARENT,
		DesignEntity::STMT, DesignEntity::STMT);

	REQUIRE(stmtReadAllResult == expectedResultStmtReadAll);
	REQUIRE(stmtPrintAllResult == expectedResultStmtPrintAll);
	REQUIRE(stmtAssignAllResult == expectedResultStmtAssignAll);
	REQUIRE(stmtCallAllResult == expectedResultStmtCallAll);
	REQUIRE(stmtWhileAllResult == expectedResultStmtWhileAll);
	REQUIRE(stmtIfAllResult == expectedResultStmtIfAll);
	REQUIRE(stmtStmtAllResult == expectedResultStmtStmtAll);
}	

TEST_CASE("ParentT Relationship Storage Test") {
	RelationshipStorage* parentTRelationshipStorage = new ParentTRelationshipStorage();

	// TESTING FOR STORING

	//Test While Entity
	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipWhileReadOne));
	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipWhileReadTwo));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipWhileReadDupOne));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipWhileReadDupTwo));

	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipWhilePrintOne));
	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipWhilePrintTwo));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipWhilePrintDupOne));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipWhilePrintDupTwo));

	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipWhileAssignOne));
	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipWhileAssignTwo));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipWhileAssignDupOne));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipWhileAssignDupTwo));

	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipWhileCallOne));
	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipWhileCallTwo));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipWhileCallDupOne));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipWhileCallDupTwo));

	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipWhileWhileOne));
	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipWhileWhileTwo));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipWhileWhileDupOne));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipWhileWhileDupTwo));

	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipWhileIfOne));
	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipWhileIfTwo));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipWhileIfDupOne));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipWhileIfDupTwo));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Test If Entity
	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipIfReadOne));
	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipIfReadTwo));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipIfReadDupOne));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipIfReadDupTwo));

	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipIfPrintOne));
	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipIfPrintTwo));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipIfPrintDupOne));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipIfPrintDupTwo));

	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipIfAssignOne));
	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipIfAssignTwo));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipIfAssignDupOne));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipIfAssignDupTwo));

	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipIfCallOne));
	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipIfCallTwo));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipIfCallDupOne));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipIfCallDupTwo));

	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipIfWhileOne));
	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipIfWhileTwo));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipIfWhileDupOne));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipIfWhileDupTwo));

	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipIfIfOne));
	REQUIRE(parentTRelationshipStorage->storeRelationship(parentTRelationshipIfIfTwo));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipIfIfDupOne));
	REQUIRE(!parentTRelationshipStorage->storeRelationship(parentTRelationshipIfIfDupTwo));

	REQUIRE(!parentTRelationshipStorage->storeRelationship(modifyRelationshipAssignOne));

	//Testing for ParentT(1,2) query
	//Testing for Whie entity
	REQUIRE(parentTRelationshipStorage->getRelationship(RelationshipType::PARENT_T, stmtTokenObject6, stmtTokenObject5));
	REQUIRE(parentTRelationshipStorage->getRelationship(RelationshipType::PARENT_T, stmtTokenObject6, stmtTokenObject4));
	REQUIRE(parentTRelationshipStorage->getRelationship(RelationshipType::PARENT_T, stmtTokenObject6, stmtTokenObject1));
	REQUIRE(parentTRelationshipStorage->getRelationship(RelationshipType::PARENT_T, stmtTokenObject6, stmtTokenObject2));
	REQUIRE(parentTRelationshipStorage->getRelationship(RelationshipType::PARENT_T, stmtTokenObject6, stmtTokenObject12));
	REQUIRE(parentTRelationshipStorage->getRelationship(RelationshipType::PARENT_T, stmtTokenObject6, stmtTokenObject3));

	//Testing for If entity
	REQUIRE(parentTRelationshipStorage->getRelationship(RelationshipType::PARENT_T, stmtTokenObject3, stmtTokenObject5));
	REQUIRE(parentTRelationshipStorage->getRelationship(RelationshipType::PARENT_T, stmtTokenObject3, stmtTokenObject4));
	REQUIRE(parentTRelationshipStorage->getRelationship(RelationshipType::PARENT_T, stmtTokenObject3, stmtTokenObject1));
	REQUIRE(parentTRelationshipStorage->getRelationship(RelationshipType::PARENT_T, stmtTokenObject3, stmtTokenObject2));
	REQUIRE(parentTRelationshipStorage->getRelationship(RelationshipType::PARENT_T, stmtTokenObject3, stmtTokenObject6));
	REQUIRE(parentTRelationshipStorage->getRelationship(RelationshipType::PARENT_T, stmtTokenObject3, stmtTokenObject9));

	//Testing for ParentT(1,a), ParentT(1,pr), etc
	//Test for While Entity
	std::unordered_set<std::string> whileReadTest{ read_value_one };
	std::unordered_set<std::string> whilePrintTest{ print_value_one };
	std::unordered_set<std::string> whileAssignTest{ assign_value_one };
	std::unordered_set<std::string> whileCallTest{ call_value_one };
	std::unordered_set<std::string> whileWhileTest{ while_value_two };
	std::unordered_set<std::string> whileIfTest{ if_value_one };
	std::unordered_set<std::string> whileStmtTest{ read_value_one, print_value_one, assign_value_one, call_value_one, while_value_two,
												   if_value_one };

	REQUIRE(parentTRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject6, DesignEntity::READ) == whileReadTest);
	REQUIRE(parentTRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject6, DesignEntity::PRINT) == whilePrintTest);
	REQUIRE(parentTRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject6, DesignEntity::ASSIGN) == whileAssignTest);
	REQUIRE(parentTRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject6, DesignEntity::CALL) == whileCallTest);
	REQUIRE(parentTRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject6, DesignEntity::WHILE) == whileWhileTest);
	REQUIRE(parentTRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject6, DesignEntity::IF) == whileIfTest);
	REQUIRE(parentTRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject6, DesignEntity::STMT) == whileStmtTest);

	//Test for If Entity
	std::unordered_set<std::string> ifReadTest{ read_value_one };
	std::unordered_set<std::string> ifPrintTest{ print_value_one };
	std::unordered_set<std::string> ifAssignTest{ assign_value_one };
	std::unordered_set<std::string> ifCallTest{ call_value_one };
	std::unordered_set<std::string> ifWhileTest{ while_value_one };
	std::unordered_set<std::string> ifIfTest{ if_value_two };
	std::unordered_set<std::string> ifStmtTest{ read_value_one, print_value_one, assign_value_one, call_value_one, while_value_one,
												if_value_two };

	REQUIRE(parentTRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject3, DesignEntity::READ) == ifReadTest);
	REQUIRE(parentTRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject3, DesignEntity::PRINT) == ifPrintTest);
	REQUIRE(parentTRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject3, DesignEntity::ASSIGN) == ifAssignTest);
	REQUIRE(parentTRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject3, DesignEntity::CALL) == ifCallTest);
	REQUIRE(parentTRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject3, DesignEntity::WHILE) == ifWhileTest);
	REQUIRE(parentTRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject3, DesignEntity::IF) == ifIfTest);
	REQUIRE(parentTRelationshipStorage->getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject3, DesignEntity::STMT) == ifStmtTest);

	//Testing for ParentT(s,2), ParentT(w,2), and ParentT(if,2)
	//Looking for w
	std::unordered_set<std::string> whileResult{ while_value_one };
	//
	REQUIRE(parentTRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::WHILE, stmtTokenObject5) == whileResult);
	REQUIRE(parentTRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::WHILE, stmtTokenObject4) == whileResult);
	REQUIRE(parentTRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::WHILE, stmtTokenObject1) == whileResult);
	REQUIRE(parentTRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::WHILE, stmtTokenObject2) == whileResult);
	REQUIRE(parentTRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::WHILE, stmtTokenObject12) == whileResult);
	REQUIRE(parentTRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::WHILE, stmtTokenObject3) == whileResult);

	////Looking for if
	std::unordered_set<std::string> ifResult{ if_value_one };

	REQUIRE(parentTRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::IF, stmtTokenObject5) == ifResult);
	REQUIRE(parentTRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::IF, stmtTokenObject4) == ifResult);
	REQUIRE(parentTRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::IF, stmtTokenObject1) == ifResult);
	REQUIRE(parentTRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::IF, stmtTokenObject2) == ifResult);
	REQUIRE(parentTRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::IF, stmtTokenObject6) == ifResult);
	REQUIRE(parentTRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::IF, stmtTokenObject9) == ifResult);


	//Looking for s
	std::unordered_set<std::string> statementResult{ while_value_one,if_value_one };

	REQUIRE(parentTRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::STMT, stmtTokenObject5) == statementResult);
	REQUIRE(parentTRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::STMT, stmtTokenObject4) == statementResult);
	REQUIRE(parentTRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::STMT, stmtTokenObject1) == statementResult);
	REQUIRE(parentTRelationshipStorage->getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::STMT, stmtTokenObject2) == statementResult);


	//Testing for ParentT(s,a),...,ParentT(w,a),...,ParentT(if,a),..., etc

	//Test While Entity


	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultWhileReadAll{ {while_value_one, std::unordered_set<std::string>({read_value_one}) },
																								 {while_value_two, std::unordered_set<std::string>({read_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultWhilePrintAll{ {while_value_one, std::unordered_set<std::string>({print_value_one}) },
																								  {while_value_two, std::unordered_set<std::string>({print_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultWhileAssignAll{ {while_value_one, std::unordered_set<std::string>({assign_value_one}) },
																								   {while_value_two, std::unordered_set<std::string>({assign_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultWhileCallAll{ {while_value_one, std::unordered_set<std::string>({call_value_one}) },
																								   {while_value_two, std::unordered_set<std::string>({call_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultWhileWhileAll{ {while_value_one, std::unordered_set<std::string>({while_value_two}) },
																								   {while_value_two, std::unordered_set<std::string>({while_value_three}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultWhileIfAll{ {while_value_one, std::unordered_set<std::string>({if_value_one})},
																								   {while_value_two, std::unordered_set<std::string>({if_value_two})} };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultWhileStmtAll{
										{while_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_one, call_value_one, while_value_two, if_value_one})},
										{while_value_two, std::unordered_set<std::string>({read_value_two, print_value_two, assign_value_two, call_value_two, while_value_three, if_value_two}) } };


	std::unordered_map<std::string, std::unordered_set<std::string>> whileReadAllResult = parentTRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T,
		DesignEntity::WHILE, DesignEntity::READ);

	std::unordered_map<std::string, std::unordered_set<std::string>> whilePrintAllResult = parentTRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T,
		DesignEntity::WHILE, DesignEntity::PRINT);
	std::unordered_map<std::string, std::unordered_set<std::string>> whileAssignAllResult = parentTRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T,
		DesignEntity::WHILE, DesignEntity::ASSIGN);
	std::unordered_map<std::string, std::unordered_set<std::string>> whileCallAllResult = parentTRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T,
		DesignEntity::WHILE, DesignEntity::CALL);
	std::unordered_map<std::string, std::unordered_set<std::string>> whileWhileAllResult = parentTRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T,
		DesignEntity::WHILE, DesignEntity::WHILE);
	std::unordered_map<std::string, std::unordered_set<std::string>> whileIfAllResult = parentTRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T,
		DesignEntity::WHILE, DesignEntity::IF);
	std::unordered_map<std::string, std::unordered_set<std::string>> whileStmtAllResult = parentTRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T,
		DesignEntity::WHILE, DesignEntity::STMT);

	REQUIRE(whileReadAllResult == expectedResultWhileReadAll);
	REQUIRE(whilePrintAllResult == expectedResultWhilePrintAll);
	REQUIRE(whileAssignAllResult == expectedResultWhileAssignAll);
	REQUIRE(whileCallAllResult == expectedResultWhileCallAll);
	REQUIRE(whileWhileAllResult == expectedResultWhileWhileAll);
	REQUIRE(whileIfAllResult == expectedResultWhileIfAll);
	REQUIRE(whileStmtAllResult == expectedResultWhileStmtAll);


	//Test for If Entity
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultIfReadAll{ {if_value_one, std::unordered_set<std::string>({read_value_one}) },
																								 {if_value_two, std::unordered_set<std::string>({read_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultIfPrintAll{ {if_value_one, std::unordered_set<std::string>({print_value_one}) },
																								  {if_value_two, std::unordered_set<std::string>({print_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultIfAssignAll{ {if_value_one, std::unordered_set<std::string>({assign_value_one}) },
																								   {if_value_two, std::unordered_set<std::string>({assign_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultIfCallAll{ {if_value_one, std::unordered_set<std::string>({call_value_one}) },
																								   {if_value_two, std::unordered_set<std::string>({call_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultIfWhileAll{ {if_value_one, std::unordered_set<std::string>({while_value_one}) },
																								   {if_value_two, std::unordered_set<std::string>({while_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultIfIfAll{ {if_value_one, std::unordered_set<std::string>({if_value_two})},
																								   {if_value_two, std::unordered_set<std::string>({if_value_three})} };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultIfStmtAll{
										{if_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_one, call_value_one, while_value_one, if_value_two})},
										{if_value_two, std::unordered_set<std::string>({read_value_two, print_value_two, assign_value_two, call_value_two, while_value_two, if_value_three}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> ifReadAllResult = parentTRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T,
		DesignEntity::IF, DesignEntity::READ);

	std::unordered_map<std::string, std::unordered_set<std::string>> ifPrintAllResult = parentTRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T,
		DesignEntity::IF, DesignEntity::PRINT);
	std::unordered_map<std::string, std::unordered_set<std::string>> ifAssignAllResult = parentTRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T,
		DesignEntity::IF, DesignEntity::ASSIGN);
	std::unordered_map<std::string, std::unordered_set<std::string>> ifCallAllResult = parentTRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T,
		DesignEntity::IF, DesignEntity::CALL);
	std::unordered_map<std::string, std::unordered_set<std::string>> ifWhileAllResult = parentTRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T,
		DesignEntity::IF, DesignEntity::WHILE);
	std::unordered_map<std::string, std::unordered_set<std::string>> ifIfAllResult = parentTRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T,
		DesignEntity::IF, DesignEntity::IF);
	std::unordered_map<std::string, std::unordered_set<std::string>> ifStmtAllResult = parentTRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T,
		DesignEntity::IF, DesignEntity::STMT);

	REQUIRE(ifReadAllResult == expectedResultIfReadAll);
	REQUIRE(ifPrintAllResult == expectedResultIfPrintAll);
	REQUIRE(ifAssignAllResult == expectedResultIfAssignAll);
	REQUIRE(ifCallAllResult == expectedResultIfCallAll);
	REQUIRE(ifWhileAllResult == expectedResultIfWhileAll);
	REQUIRE(ifIfAllResult == expectedResultIfIfAll);
	REQUIRE(ifStmtAllResult == expectedResultIfStmtAll);

	//Test for StatementEntity
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultStmtReadAll{
		{while_value_one, std::unordered_set<std::string>({read_value_one}) },
		{while_value_two, std::unordered_set<std::string>({read_value_two}) },
		{if_value_one, std::unordered_set<std::string>({read_value_one}) },
		{if_value_two, std::unordered_set<std::string>({read_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultStmtPrintAll{
		{while_value_one, std::unordered_set<std::string>({print_value_one}) },
		{while_value_two, std::unordered_set<std::string>({print_value_two}) },
		{if_value_one, std::unordered_set<std::string>({print_value_one}) },
		{if_value_two, std::unordered_set<std::string>({print_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultStmtAssignAll{
		{while_value_one, std::unordered_set<std::string>({assign_value_one}) },
		{while_value_two, std::unordered_set<std::string>({assign_value_two}) },
		{if_value_one, std::unordered_set<std::string>({assign_value_one}) },
		{if_value_two, std::unordered_set<std::string>({assign_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultStmtCallAll{
		{while_value_one, std::unordered_set<std::string>({call_value_one}) },
		{while_value_two, std::unordered_set<std::string>({call_value_two}) },
		{if_value_one, std::unordered_set<std::string>({call_value_one}) },
		{if_value_two, std::unordered_set<std::string>({call_value_two}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultStmtWhileAll{
		{while_value_one, std::unordered_set<std::string>({while_value_two}) },
		{while_value_two, std::unordered_set<std::string>({while_value_three}) },
		{if_value_one, std::unordered_set<std::string>({while_value_one}) },
		{if_value_two, std::unordered_set<std::string>({while_value_two}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultStmtIfAll{
		{while_value_one, std::unordered_set<std::string>({if_value_one}) },
		{while_value_two, std::unordered_set<std::string>({if_value_two}) },
		{if_value_one, std::unordered_set<std::string>({if_value_two}) },
		{if_value_two, std::unordered_set<std::string>({if_value_three}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultStmtStmtAll{
		{while_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_one, call_value_one, while_value_two, if_value_one})},
		{while_value_two, std::unordered_set<std::string>({read_value_two, print_value_two, assign_value_two, call_value_two, while_value_three, if_value_two}) },
		{if_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_one, call_value_one, while_value_one, if_value_two})},
		{if_value_two, std::unordered_set<std::string>({read_value_two, print_value_two, assign_value_two, call_value_two, while_value_two, if_value_three}) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> stmtReadAllResult = parentTRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T,
		DesignEntity::STMT, DesignEntity::READ);

	std::unordered_map<std::string, std::unordered_set<std::string>> stmtPrintAllResult = parentTRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T,
		DesignEntity::STMT, DesignEntity::PRINT);
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtAssignAllResult = parentTRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T,
		DesignEntity::STMT, DesignEntity::ASSIGN);
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtCallAllResult = parentTRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T,
		DesignEntity::STMT, DesignEntity::CALL);
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtWhileAllResult = parentTRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T,
		DesignEntity::STMT, DesignEntity::WHILE);
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtIfAllResult = parentTRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T,
		DesignEntity::STMT, DesignEntity::IF);
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtStmtAllResult = parentTRelationshipStorage->getAllRelationship(RelationshipType::PARENT_T,
		DesignEntity::STMT, DesignEntity::STMT);

	REQUIRE(stmtReadAllResult == expectedResultStmtReadAll);
	REQUIRE(stmtPrintAllResult == expectedResultStmtPrintAll);
	REQUIRE(stmtAssignAllResult == expectedResultStmtAssignAll);
	REQUIRE(stmtCallAllResult == expectedResultStmtCallAll);
	REQUIRE(stmtWhileAllResult == expectedResultStmtWhileAll);
	REQUIRE(stmtIfAllResult == expectedResultStmtIfAll);
	REQUIRE(stmtStmtAllResult == expectedResultStmtStmtAll);
}


TEST_CASE("Follows Relationship Storage Test") {
	RelationshipStorage* followsRelationshipStorage = new FollowsRelationshipStorage();

	// TESTING FOR STORING

	//Test Read Entity
	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipReadReadOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipReadReadDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipReadPrintOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipReadPrintDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipReadAssignOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipReadAssignDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipReadCallOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipReadCallDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipReadWhileOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipReadWhileDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipReadIfOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipReadIfDupOne));

	//Test Print Entity
	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipPrintReadOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipPrintReadDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipPrintPrintOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipPrintPrintDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipPrintAssignOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipPrintAssignDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipPrintCallOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipPrintCallDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipPrintWhileOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipPrintWhileDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipPrintIfOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipPrintIfDupOne));

	//Test Assign Entity
	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipAssignReadOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipAssignReadDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipAssignPrintOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipAssignPrintDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipAssignAssignOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipAssignAssignDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipAssignCallOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipAssignCallDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipAssignWhileOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipAssignWhileDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipAssignIfOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipAssignIfDupOne));

	//Test Call Entity
	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipCallReadOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipCallReadDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipCallPrintOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipCallPrintDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipCallAssignOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipCallAssignDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipCallCallOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipCallCallDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipCallWhileOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipCallWhileDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipCallIfOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipCallIfDupOne));

	//Test While Entity
	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipWhileReadOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipWhileReadDupOne));


	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipWhilePrintOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipWhilePrintDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipWhileAssignOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipWhileAssignDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipWhileCallOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipWhileCallDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipWhileWhileOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipWhileWhileDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipWhileIfOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipWhileIfDupOne));

	//Test If Entity
	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipIfReadOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipIfReadDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipIfPrintOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipIfPrintDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipIfAssignOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipIfAssignDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipIfCallOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipIfCallDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipIfWhileOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipIfWhileDupOne));

	REQUIRE(followsRelationshipStorage->storeRelationship(followsRelationshipIfIfOne));
	REQUIRE(!followsRelationshipStorage->storeRelationship(followsRelationshipIfIfDupOne));

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	REQUIRE(!followsRelationshipStorage->storeRelationship(modifyRelationshipAssignOne));

	//Testing for Parent(1,2) query
	// 

	//Testing for Read entity	
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject5, stmtTokenObject11));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject5, stmtTokenObject4));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject5, stmtTokenObject1));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject5, stmtTokenObject2));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject5, stmtTokenObject6));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject5, stmtTokenObject3));

	//Testing for Print entity	
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject4, stmtTokenObject5));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject4, stmtTokenObject10));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject4, stmtTokenObject1));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject4, stmtTokenObject2));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject4, stmtTokenObject6));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject4, stmtTokenObject3));

	//Testing for Assign entity	
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject1, stmtTokenObject5));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject1, stmtTokenObject4));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject1, stmtTokenObject7));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject1, stmtTokenObject2));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject1, stmtTokenObject6));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject1, stmtTokenObject3));

	//Testing for Call entity	
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject2, stmtTokenObject5));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject2, stmtTokenObject4));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject2, stmtTokenObject1));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject2, stmtTokenObject8));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject2, stmtTokenObject6));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject2, stmtTokenObject3));

	//Testing for While entity	
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject6, stmtTokenObject5));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject6, stmtTokenObject4));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject6, stmtTokenObject1));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject6, stmtTokenObject2));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject6, stmtTokenObject12));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject6, stmtTokenObject3));

	//Testing for If entity	
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject3, stmtTokenObject5));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject3, stmtTokenObject4));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject3, stmtTokenObject1));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject3, stmtTokenObject2));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject3, stmtTokenObject6));
	REQUIRE(followsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, stmtTokenObject3, stmtTokenObject9));


	//Testing for Parent(1,a), Parent(1,pr), etc
	//Test for While Entity
	std::unordered_set<std::string> readPrintTest{ print_value_one };
	std::unordered_set<std::string> printAssignTest{ assign_value_one };
	std::unordered_set<std::string> assignCallTest{ call_value_one };
	std::unordered_set<std::string> callWhileTest{ while_value_one };
	std::unordered_set<std::string> whileIfTest{ if_value_one };
	std::unordered_set<std::string> ifReadTest{ read_value_one };
	std::unordered_set<std::string> readStmtTest{ read_value_two, print_value_one, assign_value_one, call_value_one, while_value_one,
												   if_value_one };

	REQUIRE(followsRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS, stmtTokenObject5, DesignEntity::PRINT) == readPrintTest);
	REQUIRE(followsRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS, stmtTokenObject4, DesignEntity::ASSIGN) == printAssignTest);
	REQUIRE(followsRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS, stmtTokenObject1, DesignEntity::CALL) == assignCallTest);
	REQUIRE(followsRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS, stmtTokenObject2, DesignEntity::WHILE) == callWhileTest);
	REQUIRE(followsRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS, stmtTokenObject6, DesignEntity::IF) == whileIfTest);
	REQUIRE(followsRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS, stmtTokenObject3, DesignEntity::READ) == ifReadTest);
	REQUIRE(followsRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS, stmtTokenObject5, DesignEntity::STMT) == readStmtTest);


	//Testing for Parent(s,2), Parent(w,2), and Parent(if,2)
	//Looking for w
	std::unordered_set<std::string> readPrintResult{ read_value_one };
	std::unordered_set<std::string> printAssignResult{ print_value_one };
	std::unordered_set<std::string> assignCallResult{ assign_value_one };
	std::unordered_set<std::string> callWhileResult{ call_value_one };
	std::unordered_set<std::string> whileIfResult{ while_value_one };
	std::unordered_set<std::string> ifReadResult{ if_value_one };
	std::unordered_set<std::string> stmtReadResult{ while_value_one, print_value_one, assign_value_one, call_value_one, if_value_one };

	REQUIRE(followsRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS, DesignEntity::READ, stmtTokenObject4) == readPrintResult);
	REQUIRE(followsRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS, DesignEntity::PRINT, stmtTokenObject1) == printAssignResult);
	REQUIRE(followsRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS, DesignEntity::ASSIGN, stmtTokenObject2) == assignCallResult);
	REQUIRE(followsRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS, DesignEntity::CALL, stmtTokenObject6) == callWhileResult);
	REQUIRE(followsRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS, DesignEntity::WHILE, stmtTokenObject3) == whileIfResult);
	REQUIRE(followsRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS, DesignEntity::IF, stmtTokenObject5) == ifReadResult);
	REQUIRE(followsRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS, DesignEntity::STMT, stmtTokenObject5) == stmtReadResult);


	//Testing for Parent(s,a),...,Parent(w,a),...,Parent(if,a),..., etc
	//Test While Entity

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultReadPrintAll{ { read_value_one, std::unordered_set<std::string>({ print_value_one }) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultPrintAssigntAll{ {print_value_one, std::unordered_set<std::string>({ assign_value_one }) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAssignCallAll{ {assign_value_one, std::unordered_set<std::string>({ call_value_one }) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultCallWhileAll{ {call_value_one, std::unordered_set<std::string>({ while_value_one }) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultWhileIfAll{ {while_value_one, std::unordered_set<std::string>({ if_value_one }) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultIfReadAll{ {if_value_one, std::unordered_set<std::string>({ read_value_one }) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedStmtStmtAll{
										{ while_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_one, call_value_one, while_value_two, if_value_one})},
										{ read_value_one, std::unordered_set<std::string>({read_value_two, print_value_one, assign_value_one, call_value_one, while_value_one, if_value_one})},
										{ print_value_one, std::unordered_set<std::string>({read_value_one, print_value_two, assign_value_one, call_value_one, while_value_one, if_value_one})},
										{ assign_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_two, call_value_one, while_value_one, if_value_one})},
										{ call_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_one, call_value_two, while_value_one, if_value_one})},
										{ if_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_one, call_value_one, while_value_one, if_value_two})}, };


	std::unordered_map<std::string, std::unordered_set<std::string>> readPrintAllResult = followsRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS,
		DesignEntity::READ, DesignEntity::PRINT);

	std::unordered_map<std::string, std::unordered_set<std::string>> printAssignAllResult = followsRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS,
		DesignEntity::PRINT, DesignEntity::ASSIGN);
	std::unordered_map<std::string, std::unordered_set<std::string>> assignCallAllResult = followsRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS,
		DesignEntity::ASSIGN, DesignEntity::CALL);
	std::unordered_map<std::string, std::unordered_set<std::string>> callWhileAllResult = followsRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS,
		DesignEntity::CALL, DesignEntity::WHILE);
	std::unordered_map<std::string, std::unordered_set<std::string>> whileIfAllResult = followsRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS,
		DesignEntity::WHILE, DesignEntity::IF);
	std::unordered_map<std::string, std::unordered_set<std::string>> ifReadAllResult = followsRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS,
		DesignEntity::IF, DesignEntity::READ);
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtStmtAllResult = followsRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS,
		DesignEntity::STMT, DesignEntity::STMT);

	REQUIRE(readPrintAllResult == expectedResultReadPrintAll);
	REQUIRE(printAssignAllResult == expectedResultPrintAssigntAll);
	REQUIRE(assignCallAllResult == expectedResultAssignCallAll);
	REQUIRE(callWhileAllResult == expectedResultCallWhileAll);
	REQUIRE(whileIfAllResult == expectedResultWhileIfAll);
	REQUIRE(ifReadAllResult == expectedResultIfReadAll);
	REQUIRE(stmtStmtAllResult == expectedStmtStmtAll);
}

TEST_CASE("FollowsT Relationship Storage Test") {
	RelationshipStorage* followsTRelationshipStorage = new FollowsTRelationshipStorage();

	// TESTING FOR STORING

	//Test Read Entity
	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipReadReadOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipReadReadDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipReadPrintOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipReadPrintDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipReadAssignOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipReadAssignDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipReadCallOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipReadCallDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipReadWhileOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipReadWhileDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipReadIfOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipReadIfDupOne));

	//Test Print EntityT
	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipPrintReadOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipPrintReadDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipPrintPrintOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipPrintPrintDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipPrintAssignOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipPrintAssignDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipPrintCallOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipPrintCallDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipPrintWhileOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipPrintWhileDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipPrintIfOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipPrintIfDupOne));

	//Test Assign Entity
	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipAssignReadOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipAssignReadDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipAssignPrintOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipAssignPrintDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipAssignAssignOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipAssignAssignDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipAssignCallOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipAssignCallDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipAssignWhileOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipAssignWhileDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipAssignIfOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipAssignIfDupOne));

	//Test Call Entity
	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipCallReadOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipCallReadDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipCallPrintOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipCallPrintDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipCallAssignOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipCallAssignDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipCallCallOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipCallCallDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipCallWhileOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipCallWhileDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipCallIfOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipCallIfDupOne));

	//Test While Entity
	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipWhileReadOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipWhileReadDupOne));


	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipWhilePrintOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipWhilePrintDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipWhileAssignOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipWhileAssignDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipWhileCallOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipWhileCallDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipWhileWhileOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipWhileWhileDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipWhileIfOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipWhileIfDupOne));
	
	//Test If Entity
	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipIfReadOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipIfReadDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipIfPrintOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipIfPrintDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipIfAssignOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipIfAssignDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipIfCallOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipIfCallDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipIfWhileOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipIfWhileDupOne));

	REQUIRE(followsTRelationshipStorage->storeRelationship(followsTRelationshipIfIfOne));
	REQUIRE(!followsTRelationshipStorage->storeRelationship(followsTRelationshipIfIfDupOne));

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	REQUIRE(!followsTRelationshipStorage->storeRelationship(modifyRelationshipAssignOne));

	//Testing for Parent(1,2) query
	// 
	
	//Testing for Read entity	
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject5, stmtTokenObject11));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject5, stmtTokenObject4));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject5, stmtTokenObject1));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject5, stmtTokenObject2));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject5, stmtTokenObject6));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject5, stmtTokenObject3));

	//Testing for Print entity	
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject4, stmtTokenObject5));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject4, stmtTokenObject10));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject4, stmtTokenObject1));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject4, stmtTokenObject2));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject4, stmtTokenObject6));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject4, stmtTokenObject3));

	//Testing for Assign entity	
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject1, stmtTokenObject5));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject1, stmtTokenObject4));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject1, stmtTokenObject7));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject1, stmtTokenObject2));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject1, stmtTokenObject6));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject1, stmtTokenObject3));

	//Testing for Call entity	
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject2, stmtTokenObject5));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject2, stmtTokenObject4));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject2, stmtTokenObject1));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject2, stmtTokenObject8));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject2, stmtTokenObject6));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject2, stmtTokenObject3));

	//Testing for While entity	
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject6, stmtTokenObject5));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject6, stmtTokenObject4));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject6, stmtTokenObject1));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject6, stmtTokenObject2));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject6, stmtTokenObject12));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject6, stmtTokenObject3));

	//Testing for If entity	
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject3, stmtTokenObject5));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject3, stmtTokenObject4));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject3, stmtTokenObject1));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject3, stmtTokenObject2));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject3, stmtTokenObject6));
	REQUIRE(followsTRelationshipStorage->getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject3, stmtTokenObject9));


	//Testing for Parent(1,a), Parent(1,pr), etc
	//Test for While Entity
	std::unordered_set<std::string> readPrintTest{ print_value_one };
	std::unordered_set<std::string> printAssignTest{ assign_value_one };
	std::unordered_set<std::string> assignCallTest{ call_value_one };
	std::unordered_set<std::string> callWhileTest{ while_value_one };
	std::unordered_set<std::string> whileIfTest{ if_value_one };
	std::unordered_set<std::string> ifReadTest{ read_value_one };
	std::unordered_set<std::string> readStmtTest{ read_value_two, print_value_one, assign_value_one, call_value_one, while_value_one,
												   if_value_one };

	REQUIRE(followsTRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS_T, stmtTokenObject5, DesignEntity::PRINT) == readPrintTest);
	REQUIRE(followsTRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS_T, stmtTokenObject4, DesignEntity::ASSIGN) == printAssignTest);
	REQUIRE(followsTRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS_T, stmtTokenObject1, DesignEntity::CALL) == assignCallTest);
	REQUIRE(followsTRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS_T, stmtTokenObject2, DesignEntity::WHILE) == callWhileTest);
	REQUIRE(followsTRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS_T, stmtTokenObject6, DesignEntity::IF) == whileIfTest);
	REQUIRE(followsTRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS_T, stmtTokenObject3, DesignEntity::READ) == ifReadTest);
	REQUIRE(followsTRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS_T, stmtTokenObject5, DesignEntity::STMT) == readStmtTest);


	//Testing for Parent(s,2), Parent(w,2), and Parent(if,2)
	//Looking for w
	std::unordered_set<std::string> readPrintResult{ read_value_one };
	std::unordered_set<std::string> printAssignResult{ print_value_one };
	std::unordered_set<std::string> assignCallResult{ assign_value_one };
	std::unordered_set<std::string> callWhileResult{ call_value_one };
	std::unordered_set<std::string> whileIfResult{ while_value_one };
	std::unordered_set<std::string> ifReadResult{ if_value_one };
	std::unordered_set<std::string> stmtReadResult{ while_value_one, print_value_one, assign_value_one, call_value_one, if_value_one };

	REQUIRE(followsTRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS_T, DesignEntity::READ, stmtTokenObject4) == readPrintResult);
	REQUIRE(followsTRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS_T, DesignEntity::PRINT, stmtTokenObject1) == printAssignResult);
	REQUIRE(followsTRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS_T, DesignEntity::ASSIGN, stmtTokenObject2) == assignCallResult);
	REQUIRE(followsTRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS_T, DesignEntity::CALL, stmtTokenObject6) == callWhileResult);
	REQUIRE(followsTRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS_T, DesignEntity::WHILE, stmtTokenObject3) == whileIfResult);
	REQUIRE(followsTRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS_T, DesignEntity::IF, stmtTokenObject5) == ifReadResult);
	REQUIRE(followsTRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS_T, DesignEntity::STMT, stmtTokenObject5) == stmtReadResult);


	//Testing for Parent(s,a),...,Parent(w,a),...,Parent(if,a),..., etc
	//Test While Entity

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultReadPrintAll{ { read_value_one, std::unordered_set<std::string>({ print_value_one }) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultPrintAssigntAll{ {print_value_one, std::unordered_set<std::string>({ assign_value_one }) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAssignCallAll{ {assign_value_one, std::unordered_set<std::string>({ call_value_one }) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultCallWhileAll{ {call_value_one, std::unordered_set<std::string>({ while_value_one }) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultWhileIfAll{ {while_value_one, std::unordered_set<std::string>({ if_value_one }) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultIfReadAll{ {if_value_one, std::unordered_set<std::string>({ read_value_one }) } };
																					  
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedStmtStmtAll{
										{ while_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_one, call_value_one, while_value_two, if_value_one})},
										{ read_value_one, std::unordered_set<std::string>({read_value_two, print_value_one, assign_value_one, call_value_one, while_value_one, if_value_one})},
										{ print_value_one, std::unordered_set<std::string>({read_value_one, print_value_two, assign_value_one, call_value_one, while_value_one, if_value_one})},
										{ assign_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_two, call_value_one, while_value_one, if_value_one})},
										{ call_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_one, call_value_two, while_value_one, if_value_one})},
										{ if_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_one, call_value_one, while_value_one, if_value_two})}, };


	std::unordered_map<std::string, std::unordered_set<std::string>> readPrintAllResult = followsTRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS_T,
		DesignEntity::READ, DesignEntity::PRINT);

	std::unordered_map<std::string, std::unordered_set<std::string>> printAssignAllResult = followsTRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS_T,
		DesignEntity::PRINT, DesignEntity::ASSIGN);
	std::unordered_map<std::string, std::unordered_set<std::string>> assignCallAllResult = followsTRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS_T,
		DesignEntity::ASSIGN, DesignEntity::CALL);
	std::unordered_map<std::string, std::unordered_set<std::string>> callWhileAllResult = followsTRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS_T,
		DesignEntity::CALL, DesignEntity::WHILE);
	std::unordered_map<std::string, std::unordered_set<std::string>> whileIfAllResult = followsTRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS_T,
		DesignEntity::WHILE, DesignEntity::IF);
	std::unordered_map<std::string, std::unordered_set<std::string>> ifReadAllResult = followsTRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS_T,
		DesignEntity::IF, DesignEntity::READ);
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtStmtAllResult = followsTRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS_T,
		DesignEntity::STMT, DesignEntity::STMT);


	REQUIRE(readPrintAllResult == expectedResultReadPrintAll);
	REQUIRE(printAssignAllResult == expectedResultPrintAssigntAll);
	REQUIRE(assignCallAllResult == expectedResultAssignCallAll);
	REQUIRE(callWhileAllResult == expectedResultCallWhileAll);
	REQUIRE(whileIfAllResult == expectedResultWhileIfAll);
	REQUIRE(ifReadAllResult == expectedResultIfReadAll);
	REQUIRE(stmtStmtAllResult == expectedStmtStmtAll);
}

TEST_CASE("Next Relationship Storage Test") {
	RelationshipStorage* nextRelationshipStorage = new NextRelationshipStorage();

	// TESTING FOR STORING

	//Test Read Entity
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipReadReadOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipReadReadDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipReadPrintOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipReadPrintDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipReadAssignOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipReadAssignDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipReadCallOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipReadCallDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipReadWhileOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipReadWhileDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipReadIfOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipReadIfDupOne));

	//Test Print Entity
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipPrintReadOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipPrintReadDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipPrintPrintOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipPrintPrintDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipPrintAssignOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipPrintAssignDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipPrintCallOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipPrintCallDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipPrintWhileOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipPrintWhileDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipPrintIfOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipPrintIfDupOne));

	//Test Assign Entity
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipAssignReadOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipAssignReadDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipAssignPrintOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipAssignPrintDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipAssignAssignOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipAssignAssignDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipAssignCallOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipAssignCallDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipAssignWhileOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipAssignWhileDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipAssignIfOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipAssignIfDupOne));

	//Test Call Entity
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipCallReadOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipCallReadDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipCallPrintOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipCallPrintDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipCallAssignOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipCallAssignDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipCallCallOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipCallCallDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipCallWhileOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipCallWhileDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipCallIfOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipCallIfDupOne));

	//Test While Entity
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipWhileReadOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipWhileReadDupOne));


	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipWhilePrintOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipWhilePrintDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipWhileAssignOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipWhileAssignDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipWhileCallOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipWhileCallDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipWhileWhileOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipWhileWhileDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipWhileIfOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipWhileIfDupOne));

	//Test If Entity
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipIfReadOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipIfReadDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipIfPrintOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipIfPrintDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipIfAssignOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipIfAssignDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipIfCallOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipIfCallDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipIfWhileOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipIfWhileDupOne));

	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipIfIfOne));
	REQUIRE(!nextRelationshipStorage->storeRelationship(nextRelationshipIfIfDupOne));

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	REQUIRE(!nextRelationshipStorage->storeRelationship(modifyRelationshipAssignOne));

	//Testing for Next(1,2) query
	// 

	//Testing for Read entity	
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject5, stmtTokenObject11));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject5, stmtTokenObject4));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject5, stmtTokenObject1));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject5, stmtTokenObject2));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject5, stmtTokenObject6));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject5, stmtTokenObject3));

	//Testing for Print entity	
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject4, stmtTokenObject5));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject4, stmtTokenObject10));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject4, stmtTokenObject1));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject4, stmtTokenObject2));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject4, stmtTokenObject6));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject4, stmtTokenObject3));

	//Testing for Assign entity	
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject1, stmtTokenObject5));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject1, stmtTokenObject4));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject1, stmtTokenObject7));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject1, stmtTokenObject2));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject1, stmtTokenObject6));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject1, stmtTokenObject3));

	//Testing for Call entity	
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject2, stmtTokenObject5));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject2, stmtTokenObject4));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject2, stmtTokenObject1));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject2, stmtTokenObject8));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject2, stmtTokenObject6));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject2, stmtTokenObject3));

	//Testing for While entity	
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject6, stmtTokenObject5));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject6, stmtTokenObject4));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject6, stmtTokenObject1));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject6, stmtTokenObject2));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject6, stmtTokenObject12));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject6, stmtTokenObject3));

	//Testing for If entity	
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject3, stmtTokenObject5));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject3, stmtTokenObject4));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject3, stmtTokenObject1));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject3, stmtTokenObject2));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject3, stmtTokenObject6));
	REQUIRE(nextRelationshipStorage->getRelationship(RelationshipType::NEXT, stmtTokenObject3, stmtTokenObject9));


	//Testing for Next(1,a), Next(1,if), etc
	//Test for While Entity
	std::unordered_set<std::string> readPrintTest{ print_value_one };
	std::unordered_set<std::string> printAssignTest{ assign_value_one };
	std::unordered_set<std::string> assignCallTest{ call_value_one };
	std::unordered_set<std::string> callWhileTest{ while_value_one };
	std::unordered_set<std::string> whileIfTest{ if_value_one };
	std::unordered_set<std::string> ifReadTest{ read_value_one };
	std::unordered_set<std::string> readStmtTest{ read_value_two, print_value_one, assign_value_one, call_value_one, while_value_one,
												   if_value_one };

	REQUIRE(nextRelationshipStorage->getRelationshipByFirst(RelationshipType::NEXT, stmtTokenObject5, DesignEntity::PRINT) == readPrintTest);
	REQUIRE(nextRelationshipStorage->getRelationshipByFirst(RelationshipType::NEXT, stmtTokenObject4, DesignEntity::ASSIGN) == printAssignTest);
	REQUIRE(nextRelationshipStorage->getRelationshipByFirst(RelationshipType::NEXT, stmtTokenObject1, DesignEntity::CALL) == assignCallTest);
	REQUIRE(nextRelationshipStorage->getRelationshipByFirst(RelationshipType::NEXT, stmtTokenObject2, DesignEntity::WHILE) == callWhileTest);
	REQUIRE(nextRelationshipStorage->getRelationshipByFirst(RelationshipType::NEXT, stmtTokenObject6, DesignEntity::IF) == whileIfTest);
	REQUIRE(nextRelationshipStorage->getRelationshipByFirst(RelationshipType::NEXT, stmtTokenObject3, DesignEntity::READ) == ifReadTest);
	REQUIRE(nextRelationshipStorage->getRelationshipByFirst(RelationshipType::NEXT, stmtTokenObject5, DesignEntity::STMT) == readStmtTest);


	//Testing for Next(s,2), Next(a,2), Next(pr,2), etc
	//Looking for w
	std::unordered_set<std::string> readPrintResult{ read_value_one };
	std::unordered_set<std::string> printAssignResult{ print_value_one };
	std::unordered_set<std::string> assignCallResult{ assign_value_one };
	std::unordered_set<std::string> callWhileResult{ call_value_one };
	std::unordered_set<std::string> whileIfResult{ while_value_one };
	std::unordered_set<std::string> ifReadResult{ if_value_one };
	std::unordered_set<std::string> stmtReadResult{ while_value_one, print_value_one, assign_value_one, call_value_one, if_value_one };

	REQUIRE(nextRelationshipStorage->getRelationshipBySecond(RelationshipType::NEXT, DesignEntity::READ, stmtTokenObject4) == readPrintResult);
	REQUIRE(nextRelationshipStorage->getRelationshipBySecond(RelationshipType::NEXT, DesignEntity::PRINT, stmtTokenObject1) == printAssignResult);
	REQUIRE(nextRelationshipStorage->getRelationshipBySecond(RelationshipType::NEXT, DesignEntity::ASSIGN, stmtTokenObject2) == assignCallResult);
	REQUIRE(nextRelationshipStorage->getRelationshipBySecond(RelationshipType::NEXT, DesignEntity::CALL, stmtTokenObject6) == callWhileResult);
	REQUIRE(nextRelationshipStorage->getRelationshipBySecond(RelationshipType::NEXT, DesignEntity::WHILE, stmtTokenObject3) == whileIfResult);
	REQUIRE(nextRelationshipStorage->getRelationshipBySecond(RelationshipType::NEXT, DesignEntity::IF, stmtTokenObject5) == ifReadResult);
	REQUIRE(nextRelationshipStorage->getRelationshipBySecond(RelationshipType::NEXT, DesignEntity::STMT, stmtTokenObject5) == stmtReadResult);


	//Testing for Next(s,a),...,Next(w,a),...,Next(if,a),..., etc
	//Test While Entity

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultReadPrintAll{ { read_value_one, std::unordered_set<std::string>({ print_value_one }) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultPrintAssigntAll{ {print_value_one, std::unordered_set<std::string>({ assign_value_one }) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAssignCallAll{ {assign_value_one, std::unordered_set<std::string>({ call_value_one }) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultCallWhileAll{ {call_value_one, std::unordered_set<std::string>({ while_value_one }) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultWhileIfAll{ {while_value_one, std::unordered_set<std::string>({ if_value_one }) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultIfReadAll{ {if_value_one, std::unordered_set<std::string>({ read_value_one }) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedStmtStmtAll{
										{ while_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_one, call_value_one, while_value_two, if_value_one})},
										{ read_value_one, std::unordered_set<std::string>({read_value_two, print_value_one, assign_value_one, call_value_one, while_value_one, if_value_one})},
										{ print_value_one, std::unordered_set<std::string>({read_value_one, print_value_two, assign_value_one, call_value_one, while_value_one, if_value_one})},
										{ assign_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_two, call_value_one, while_value_one, if_value_one})},
										{ call_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_one, call_value_two, while_value_one, if_value_one})},
										{ if_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_one, call_value_one, while_value_one, if_value_two})}, };


	std::unordered_map<std::string, std::unordered_set<std::string>> readPrintAllResult = nextRelationshipStorage->getAllRelationship(RelationshipType::NEXT,
		DesignEntity::READ, DesignEntity::PRINT);

	std::unordered_map<std::string, std::unordered_set<std::string>> printAssignAllResult = nextRelationshipStorage->getAllRelationship(RelationshipType::NEXT,
		DesignEntity::PRINT, DesignEntity::ASSIGN);
	std::unordered_map<std::string, std::unordered_set<std::string>> assignCallAllResult = nextRelationshipStorage->getAllRelationship(RelationshipType::NEXT,
		DesignEntity::ASSIGN, DesignEntity::CALL);
	std::unordered_map<std::string, std::unordered_set<std::string>> callWhileAllResult = nextRelationshipStorage->getAllRelationship(RelationshipType::NEXT,
		DesignEntity::CALL, DesignEntity::WHILE);
	std::unordered_map<std::string, std::unordered_set<std::string>> whileIfAllResult = nextRelationshipStorage->getAllRelationship(RelationshipType::NEXT,
		DesignEntity::WHILE, DesignEntity::IF);
	std::unordered_map<std::string, std::unordered_set<std::string>> ifReadAllResult = nextRelationshipStorage->getAllRelationship(RelationshipType::NEXT,
		DesignEntity::IF, DesignEntity::READ);
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtStmtAllResult = nextRelationshipStorage->getAllRelationship(RelationshipType::NEXT,
		DesignEntity::STMT, DesignEntity::STMT);

	REQUIRE(readPrintAllResult == expectedResultReadPrintAll);
	REQUIRE(printAssignAllResult == expectedResultPrintAssigntAll);
	REQUIRE(assignCallAllResult == expectedResultAssignCallAll);
	REQUIRE(callWhileAllResult == expectedResultCallWhileAll);
	REQUIRE(whileIfAllResult == expectedResultWhileIfAll);
	REQUIRE(ifReadAllResult == expectedResultIfReadAll);
	REQUIRE(stmtStmtAllResult == expectedStmtStmtAll);
}

TEST_CASE("NextT Relationship Storage Test") {
	RelationshipStorage* nextTRelationshipStorage = new NextTRelationshipStorage();

	// TESTING FOR STORING

	//Test Read Entity
	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipReadReadOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipReadReadDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipReadPrintOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipReadPrintDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipReadAssignOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipReadAssignDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipReadCallOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipReadCallDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipReadWhileOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipReadWhileDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipReadIfOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipReadIfDupOne));

	//Test Print EntityT
	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipPrintReadOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipPrintReadDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipPrintPrintOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipPrintPrintDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipPrintAssignOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipPrintAssignDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipPrintCallOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipPrintCallDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipPrintWhileOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipPrintWhileDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipPrintIfOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipPrintIfDupOne));

	//Test Assign Entity
	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipAssignReadOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipAssignReadDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipAssignPrintOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipAssignPrintDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipAssignAssignOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipAssignAssignDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipAssignCallOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipAssignCallDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipAssignWhileOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipAssignWhileDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipAssignIfOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipAssignIfDupOne));

	//Test Call Entity
	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipCallReadOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipCallReadDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipCallPrintOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipCallPrintDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipCallAssignOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipCallAssignDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipCallCallOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipCallCallDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipCallWhileOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipCallWhileDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipCallIfOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipCallIfDupOne));

	//Test While Entity
	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipWhileReadOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipWhileReadDupOne));


	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipWhilePrintOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipWhilePrintDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipWhileAssignOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipWhileAssignDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipWhileCallOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipWhileCallDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipWhileWhileOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipWhileWhileDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipWhileIfOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipWhileIfDupOne));

	//Test If Entity
	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipIfReadOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipIfReadDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipIfPrintOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipIfPrintDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipIfAssignOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipIfAssignDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipIfCallOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipIfCallDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipIfWhileOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipIfWhileDupOne));

	REQUIRE(nextTRelationshipStorage->storeRelationship(nextTRelationshipIfIfOne));
	REQUIRE(!nextTRelationshipStorage->storeRelationship(nextTRelationshipIfIfDupOne));

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	REQUIRE(!nextTRelationshipStorage->storeRelationship(modifyRelationshipAssignOne));

	//Testing for Parent(1,2) query
	// 

	//Testing for Read entity	
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject5, stmtTokenObject11));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject5, stmtTokenObject4));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject5, stmtTokenObject1));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject5, stmtTokenObject2));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject5, stmtTokenObject6));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject5, stmtTokenObject3));

	//Testing for Print entity	
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject4, stmtTokenObject5));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject4, stmtTokenObject10));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject4, stmtTokenObject1));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject4, stmtTokenObject2));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject4, stmtTokenObject6));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject4, stmtTokenObject3));

	//Testing for Assign entity	
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject1, stmtTokenObject5));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject1, stmtTokenObject4));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject1, stmtTokenObject7));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject1, stmtTokenObject2));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject1, stmtTokenObject6));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject1, stmtTokenObject3));

	//Testing for Call entity	
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject2, stmtTokenObject5));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject2, stmtTokenObject4));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject2, stmtTokenObject1));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject2, stmtTokenObject8));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject2, stmtTokenObject6));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject2, stmtTokenObject3));

	//Testing for While entity	
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject6, stmtTokenObject5));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject6, stmtTokenObject4));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject6, stmtTokenObject1));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject6, stmtTokenObject2));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject6, stmtTokenObject12));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject6, stmtTokenObject3));

	//Testing for If entity	
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject3, stmtTokenObject5));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject3, stmtTokenObject4));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject3, stmtTokenObject1));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject3, stmtTokenObject2));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject3, stmtTokenObject6));
	REQUIRE(nextTRelationshipStorage->getRelationship(RelationshipType::NEXT_T, stmtTokenObject3, stmtTokenObject9));


	//Testing for Parent(1,a), Parent(1,pr), etc
	//Test for While Entity
	std::unordered_set<std::string> readPrintTest{ print_value_one };
	std::unordered_set<std::string> printAssignTest{ assign_value_one };
	std::unordered_set<std::string> assignCallTest{ call_value_one };
	std::unordered_set<std::string> callWhileTest{ while_value_one };
	std::unordered_set<std::string> whileIfTest{ if_value_one };
	std::unordered_set<std::string> ifReadTest{ read_value_one };
	std::unordered_set<std::string> readStmtTest{ read_value_two, print_value_one, assign_value_one, call_value_one, while_value_one,
												   if_value_one };

	REQUIRE(nextTRelationshipStorage->getRelationshipByFirst(RelationshipType::NEXT_T, stmtTokenObject5, DesignEntity::PRINT) == readPrintTest);
	REQUIRE(nextTRelationshipStorage->getRelationshipByFirst(RelationshipType::NEXT_T, stmtTokenObject4, DesignEntity::ASSIGN) == printAssignTest);
	REQUIRE(nextTRelationshipStorage->getRelationshipByFirst(RelationshipType::NEXT_T, stmtTokenObject1, DesignEntity::CALL) == assignCallTest);
	REQUIRE(nextTRelationshipStorage->getRelationshipByFirst(RelationshipType::NEXT_T, stmtTokenObject2, DesignEntity::WHILE) == callWhileTest);
	REQUIRE(nextTRelationshipStorage->getRelationshipByFirst(RelationshipType::NEXT_T, stmtTokenObject6, DesignEntity::IF) == whileIfTest);
	REQUIRE(nextTRelationshipStorage->getRelationshipByFirst(RelationshipType::NEXT_T, stmtTokenObject3, DesignEntity::READ) == ifReadTest);
	REQUIRE(nextTRelationshipStorage->getRelationshipByFirst(RelationshipType::NEXT_T, stmtTokenObject5, DesignEntity::STMT) == readStmtTest);


	//Testing for Parent(s,2), Parent(w,2), and Parent(if,2)
	//Looking for w
	std::unordered_set<std::string> readPrintResult{ read_value_one };
	std::unordered_set<std::string> printAssignResult{ print_value_one };
	std::unordered_set<std::string> assignCallResult{ assign_value_one };
	std::unordered_set<std::string> callWhileResult{ call_value_one };
	std::unordered_set<std::string> whileIfResult{ while_value_one };
	std::unordered_set<std::string> ifReadResult{ if_value_one };
	std::unordered_set<std::string> stmtReadResult{ while_value_one, print_value_one, assign_value_one, call_value_one, if_value_one };

	REQUIRE(nextTRelationshipStorage->getRelationshipBySecond(RelationshipType::NEXT_T, DesignEntity::READ, stmtTokenObject4) == readPrintResult);
	REQUIRE(nextTRelationshipStorage->getRelationshipBySecond(RelationshipType::NEXT_T, DesignEntity::PRINT, stmtTokenObject1) == printAssignResult);
	REQUIRE(nextTRelationshipStorage->getRelationshipBySecond(RelationshipType::NEXT_T, DesignEntity::ASSIGN, stmtTokenObject2) == assignCallResult);
	REQUIRE(nextTRelationshipStorage->getRelationshipBySecond(RelationshipType::NEXT_T, DesignEntity::CALL, stmtTokenObject6) == callWhileResult);
	REQUIRE(nextTRelationshipStorage->getRelationshipBySecond(RelationshipType::NEXT_T, DesignEntity::WHILE, stmtTokenObject3) == whileIfResult);
	REQUIRE(nextTRelationshipStorage->getRelationshipBySecond(RelationshipType::NEXT_T, DesignEntity::IF, stmtTokenObject5) == ifReadResult);
	REQUIRE(nextTRelationshipStorage->getRelationshipBySecond(RelationshipType::NEXT_T, DesignEntity::STMT, stmtTokenObject5) == stmtReadResult);


	//Testing for Parent(s,a),...,Parent(w,a),...,Parent(if,a),..., etc
	//Test While Entity

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultReadPrintAll{ { read_value_one, std::unordered_set<std::string>({ print_value_one }) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultPrintAssigntAll{ {print_value_one, std::unordered_set<std::string>({ assign_value_one }) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAssignCallAll{ {assign_value_one, std::unordered_set<std::string>({ call_value_one }) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultCallWhileAll{ {call_value_one, std::unordered_set<std::string>({ while_value_one }) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultWhileIfAll{ {while_value_one, std::unordered_set<std::string>({ if_value_one }) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultIfReadAll{ {if_value_one, std::unordered_set<std::string>({ read_value_one }) } };

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedStmtStmtAll{
										{ while_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_one, call_value_one, while_value_two, if_value_one})},
										{ read_value_one, std::unordered_set<std::string>({read_value_two, print_value_one, assign_value_one, call_value_one, while_value_one, if_value_one})},
										{ print_value_one, std::unordered_set<std::string>({read_value_one, print_value_two, assign_value_one, call_value_one, while_value_one, if_value_one})},
										{ assign_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_two, call_value_one, while_value_one, if_value_one})},
										{ call_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_one, call_value_two, while_value_one, if_value_one})},
										{ if_value_one, std::unordered_set<std::string>({read_value_one, print_value_one, assign_value_one, call_value_one, while_value_one, if_value_two})}, };


	std::unordered_map<std::string, std::unordered_set<std::string>> readPrintAllResult = nextTRelationshipStorage->getAllRelationship(RelationshipType::NEXT_T,
		DesignEntity::READ, DesignEntity::PRINT);

	std::unordered_map<std::string, std::unordered_set<std::string>> printAssignAllResult = nextTRelationshipStorage->getAllRelationship(RelationshipType::NEXT_T,
		DesignEntity::PRINT, DesignEntity::ASSIGN);
	std::unordered_map<std::string, std::unordered_set<std::string>> assignCallAllResult = nextTRelationshipStorage->getAllRelationship(RelationshipType::NEXT_T,
		DesignEntity::ASSIGN, DesignEntity::CALL);
	std::unordered_map<std::string, std::unordered_set<std::string>> callWhileAllResult = nextTRelationshipStorage->getAllRelationship(RelationshipType::NEXT_T,
		DesignEntity::CALL, DesignEntity::WHILE);
	std::unordered_map<std::string, std::unordered_set<std::string>> whileIfAllResult = nextTRelationshipStorage->getAllRelationship(RelationshipType::NEXT_T,
		DesignEntity::WHILE, DesignEntity::IF);
	std::unordered_map<std::string, std::unordered_set<std::string>> ifReadAllResult = nextTRelationshipStorage->getAllRelationship(RelationshipType::NEXT_T,
		DesignEntity::IF, DesignEntity::READ);
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtStmtAllResult = nextTRelationshipStorage->getAllRelationship(RelationshipType::NEXT_T,
		DesignEntity::STMT, DesignEntity::STMT);


	REQUIRE(readPrintAllResult == expectedResultReadPrintAll);
	REQUIRE(printAssignAllResult == expectedResultPrintAssigntAll);
	REQUIRE(assignCallAllResult == expectedResultAssignCallAll);
	REQUIRE(callWhileAllResult == expectedResultCallWhileAll);
	REQUIRE(whileIfAllResult == expectedResultWhileIfAll);
	REQUIRE(ifReadAllResult == expectedResultIfReadAll);
	REQUIRE(stmtStmtAllResult == expectedStmtStmtAll);
}

TEST_CASE("Calls Relationship Storage Test") {
	RelationshipStorage* callsRelationshipStorage = new CallsRelationshipStorage();

	// TESTING FOR STORING

	REQUIRE(callsRelationshipStorage->storeRelationship(callsRelationshipOne));
	REQUIRE(!callsRelationshipStorage->storeRelationship(callsRelationshipOneDup));
	REQUIRE(callsRelationshipStorage->storeRelationship(callsRelationshipTwo));
	REQUIRE(!callsRelationshipStorage->storeRelationship(callsRelationshipTwoDup));
	REQUIRE(callsRelationshipStorage->storeRelationship(callsRelationshipThree));
	REQUIRE(!callsRelationshipStorage->storeRelationship(callsRelationshipThreeDup));

	REQUIRE(!callsRelationshipStorage->storeRelationship(followsRelationshipAssignAssignOne));

	// Testing for Calls("proc1", "proc2") query
	REQUIRE(callsRelationshipStorage->getRelationship(RelationshipType::CALLS, procedureTokenObject, procedureTokenObjectTwo));
	REQUIRE(callsRelationshipStorage->getRelationship(RelationshipType::CALLS, procedureTokenObject, procedureTokenObjectThree));
	REQUIRE(callsRelationshipStorage->getRelationship(RelationshipType::CALLS, procedureTokenObjectTwo, procedureTokenObjectThree));
	REQUIRE(!callsRelationshipStorage->getRelationship(RelationshipType::CALLS, procedureTokenObject, procedureTokenObjectFour));

	REQUIRE(!callsRelationshipStorage->getRelationship(RelationshipType::FOLLOWS, procedureTokenObject, procedureTokenObjectTwo));

	//Testing for Calls("proc1", p)
	std::unordered_set<std::string> emptySet{};

	std::unordered_set<std::string> getRelationshipByFirstTest1{ procedure_value_two, procedure_value_three };
	std::unordered_set<std::string> getRelationshipByFirstTest2{ procedure_value_three };

	REQUIRE(callsRelationshipStorage->getRelationshipByFirst(RelationshipType::CALLS, procedureTokenObject, DesignEntity::PROCEDURE) == getRelationshipByFirstTest1);
	REQUIRE(callsRelationshipStorage->getRelationshipByFirst(RelationshipType::CALLS, procedureTokenObjectTwo, DesignEntity::PROCEDURE) == getRelationshipByFirstTest2);
	REQUIRE(callsRelationshipStorage->getRelationshipByFirst(RelationshipType::CALLS, procedureTokenObjectThree, DesignEntity::PROCEDURE) == emptySet);

	REQUIRE(callsRelationshipStorage->getRelationshipByFirst(RelationshipType::FOLLOWS, procedureTokenObject, DesignEntity::PROCEDURE) == emptySet);

	//Testing for Calls(p, "proc2")
	std::unordered_set<std::string> getRelationshipBySecondTest1{ procedure_value_one, procedure_value_two };
	std::unordered_set<std::string> getRelationshipBySecondTest2{ procedure_value_one };

	REQUIRE(callsRelationshipStorage->getRelationshipBySecond(RelationshipType::CALLS, DesignEntity::PROCEDURE, procedureTokenObject) == emptySet);
	REQUIRE(callsRelationshipStorage->getRelationshipBySecond(RelationshipType::CALLS, DesignEntity::PROCEDURE, procedureTokenObjectTwo) == getRelationshipBySecondTest2);
	REQUIRE(callsRelationshipStorage->getRelationshipBySecond(RelationshipType::CALLS, DesignEntity::PROCEDURE, procedureTokenObjectThree) == getRelationshipBySecondTest1);

	REQUIRE(callsRelationshipStorage->getRelationshipBySecond(RelationshipType::FOLLOWS, DesignEntity::PROCEDURE, procedureTokenObjectThree) == emptySet);

	//Testing for Calls(p1, p2)
	std::unordered_map<std::string, std::unordered_set<std::string>> emptyMap{};
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllRelationshipTestAll{
										{ procedure_value_one, std::unordered_set<std::string>({procedure_value_two, procedure_value_three})},
										{ procedure_value_two, std::unordered_set<std::string>({procedure_value_three})}, };


	std::unordered_map<std::string, std::unordered_set<std::string>> getAllRelationshipResult = callsRelationshipStorage->getAllRelationship(RelationshipType::CALLS,
		DesignEntity::PROCEDURE, DesignEntity::PROCEDURE);

	std::unordered_map<std::string, std::unordered_set<std::string>> getAllRelationshipEmptyResult = callsRelationshipStorage->getAllRelationship(RelationshipType::FOLLOWS,
		DesignEntity::PROCEDURE, DesignEntity::PROCEDURE);


	REQUIRE(getAllRelationshipResult == getAllRelationshipTestAll);
	REQUIRE(getAllRelationshipEmptyResult == emptyMap);
}
