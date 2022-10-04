#include "models/Relationship/Relationship.h"
#include "models/Relationship/ModifyRelationship.h"
#include "models/Relationship/UsesRelationship.h"
#include "models/Relationship/ParentRelationship.h"
#include "models/Relationship/ParentTRelationship.h"
#include "models/Relationship/FollowsRelationship.h"
#include "models/Relationship/FollowsTRelationship.h"
#include "models/Relationship/RelationshipType.h"

#include "components/pkb/manager/RelationshipManager.h"

#include "../RelationshipObject.h"
#include "../ReuseableTokenObject.h"

#include <catch.hpp>

TEST_CASE("Relationship Manager Test") {
	RelationshipManager relManager = RelationshipManager();

	REQUIRE(relManager.storeRelationship(usesRelationshipAssignOne));
	REQUIRE(relManager.storeRelationship(usesRelationshipProcOne));
	REQUIRE(relManager.storeRelationship(usesRelationshipPrintOne));
	REQUIRE(relManager.storeRelationship(usesRelationshipWhileOne));
	REQUIRE(relManager.storeRelationship(usesRelationshipIfOne));
	
	REQUIRE(!relManager.storeRelationship(usesRelationshipReadOne));

	REQUIRE(relManager.storeRelationship(modifyRelationshipAssignOne));
	REQUIRE(relManager.storeRelationship(modifyRelationshipProcOne));
	REQUIRE(relManager.storeRelationship(modifyRelationshipReadOne));
	REQUIRE(relManager.storeRelationship(modifyRelationshipWhileOne));
	
	REQUIRE(!relManager.storeRelationship(modifyRelationshipPrintOne));

	REQUIRE(relManager.storeRelationship(parentRelationshipWhileReadOne));
	REQUIRE(relManager.storeRelationship(parentRelationshipWhilePrintOne));
	REQUIRE(relManager.storeRelationship(parentRelationshipIfAssignOne));
	REQUIRE(relManager.storeRelationship(parentRelationshipIfCallOne));

	REQUIRE(relManager.storeRelationship(parentTRelationshipWhileReadOne));
	REQUIRE(relManager.storeRelationship(parentTRelationshipWhilePrintOne));
	REQUIRE(relManager.storeRelationship(parentTRelationshipIfAssignOne));
	REQUIRE(relManager.storeRelationship(parentTRelationshipIfCallOne));

	REQUIRE(relManager.storeRelationship(followsRelationshipReadPrintOne));
	REQUIRE(relManager.storeRelationship(followsRelationshipPrintAssignOne));
	REQUIRE(relManager.storeRelationship(followsRelationshipAssignCallOne));
	REQUIRE(relManager.storeRelationship(followsRelationshipCallWhileOne));
	REQUIRE(relManager.storeRelationship(followsRelationshipWhileIfOne));
	REQUIRE(relManager.storeRelationship(followsRelationshipIfReadOne));

	REQUIRE(relManager.storeRelationship(followsTRelationshipReadPrintOne));
	REQUIRE(relManager.storeRelationship(followsTRelationshipPrintAssignOne));
	REQUIRE(relManager.storeRelationship(followsTRelationshipAssignCallOne));
	REQUIRE(relManager.storeRelationship(followsTRelationshipCallWhileOne));
	REQUIRE(relManager.storeRelationship(followsTRelationshipWhileIfOne));
	REQUIRE(relManager.storeRelationship(followsTRelationshipIfReadOne));

	REQUIRE(relManager.storeRelationship(nextRelationshipReadPrintOne));
	REQUIRE(relManager.storeRelationship(nextRelationshipPrintAssignOne));
	REQUIRE(relManager.storeRelationship(nextRelationshipAssignCallOne));
	REQUIRE(relManager.storeRelationship(nextRelationshipCallWhileOne));
	REQUIRE(relManager.storeRelationship(nextRelationshipWhileIfOne));
	REQUIRE(relManager.storeRelationship(nextRelationshipIfReadOne));
	
	REQUIRE(relManager.storeRelationship(nextTRelationshipReadPrintOne));
	REQUIRE(relManager.storeRelationship(nextTRelationshipPrintAssignOne));
	REQUIRE(relManager.storeRelationship(nextTRelationshipAssignCallOne));
	REQUIRE(relManager.storeRelationship(nextTRelationshipCallWhileOne));
	REQUIRE(relManager.storeRelationship(nextTRelationshipWhileIfOne));
	REQUIRE(relManager.storeRelationship(nextTRelationshipIfReadOne));

	REQUIRE(relManager.storeRelationship(callsRelationshipOne));
	REQUIRE(relManager.storeRelationship(callsRelationshipTwo));
	REQUIRE(relManager.storeRelationship(callsRelationshipThree));

	REQUIRE(relManager.storeRelationship(callsTRelationshipOne));
	REQUIRE(relManager.storeRelationship(callsTRelationshipTwo));
	REQUIRE(relManager.storeRelationship(callsTRelationshipThree));


	REQUIRE(relManager.getRelationship(RelationshipType::USES, stmtTokenObject1, variableTokenObject));
	REQUIRE(relManager.getRelationship(RelationshipType::MODIFIES, stmtTokenObject1, variableTokenObject));
	REQUIRE(relManager.getRelationship(RelationshipType::PARENT, stmtTokenObject6, stmtTokenObject5));
	REQUIRE(relManager.getRelationship(RelationshipType::PARENT_T, stmtTokenObject6, stmtTokenObject5));
	REQUIRE(relManager.getRelationship(RelationshipType::FOLLOWS, stmtTokenObject5, stmtTokenObject4));
	REQUIRE(relManager.getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject5, stmtTokenObject4));
	REQUIRE(relManager.getRelationship(RelationshipType::NEXT, stmtTokenObject1, stmtTokenObject2));
	REQUIRE(relManager.getRelationship(RelationshipType::NEXT_T, stmtTokenObject1, stmtTokenObject2));
	REQUIRE(relManager.getRelationship(RelationshipType::CALLS, procedureTokenObject, procedureTokenObjectTwo));
	REQUIRE(relManager.getRelationship(RelationshipType::CALLS_T, procedureTokenObject, procedureTokenObjectTwo));


	std::unordered_set<std::string> usesExpectedResult({ variable_value_one });
	std::unordered_set<std::string> modifiesExpectedResult({ variable_value_one });
	std::unordered_set<std::string> parentExpectedResult({ read_value_one });
	std::unordered_set<std::string> parentTExpectedResult({ read_value_one });
	std::unordered_set<std::string> followsExpectedResult({ print_value_one });
	std::unordered_set<std::string> followsTExpectedResult({ print_value_one });
	std::unordered_set<std::string> nextExpectedResult({ print_value_one });
	std::unordered_set<std::string> nextTExpectedResult({ print_value_one });
	std::unordered_set<std::string> callsExpectedResult{ procedure_value_two, procedure_value_three };
	std::unordered_set<std::string> callsTExpectedResult{ procedure_value_two, procedure_value_three };


	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::USES, stmtTokenObject1, DesignEntity::VARIABLE) == usesExpectedResult);
	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject1, DesignEntity::VARIABLE) == modifiesExpectedResult);
	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject6, DesignEntity::READ) == parentExpectedResult);
	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject6, DesignEntity::READ) == parentTExpectedResult);
	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::FOLLOWS, stmtTokenObject5, DesignEntity::PRINT) == followsExpectedResult);
	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::FOLLOWS_T, stmtTokenObject5, DesignEntity::PRINT) == followsTExpectedResult);
	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::NEXT, stmtTokenObject5, DesignEntity::PRINT) == nextExpectedResult);
	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::NEXT_T, stmtTokenObject5, DesignEntity::PRINT) == nextTExpectedResult);
	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::CALLS, procedureTokenObject, DesignEntity::PROCEDURE) == callsExpectedResult);
	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::CALLS_T, procedureTokenObject, DesignEntity::PROCEDURE) == callsTExpectedResult);

	
	std::unordered_set<std::string> usesExpectedResultTwo({ assign_value_one });
	std::unordered_set<std::string> modifiesExpectedResultTwo({ assign_value_one });
	std::unordered_set<std::string> parentExpectedResultTwo({ while_value_one });
	std::unordered_set<std::string> parentTExpectedResultTwo({ while_value_one });
	std::unordered_set<std::string> followsExpectedResultTwo({ read_value_one });
	std::unordered_set<std::string> followsTExpectedResultTwo({ read_value_one });
	std::unordered_set<std::string> nextExpectedResultTwo({ read_value_one });
	std::unordered_set<std::string> nextTExpectedResultTwo({ read_value_one });
	std::unordered_set<std::string> callsExpectedResultTwo{ procedure_value_one, procedure_value_two };
	std::unordered_set<std::string> callsTExpectedResultTwo{ procedure_value_one, procedure_value_two };
	

	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::USES, DesignEntity::ASSIGN, variableTokenObject) == usesExpectedResultTwo);
	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::ASSIGN, variableTokenObject) == modifiesExpectedResultTwo);
	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::WHILE, stmtTokenObject5) == parentExpectedResultTwo);
	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::WHILE, stmtTokenObject5) == parentTExpectedResultTwo);
	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::FOLLOWS, DesignEntity::READ, stmtTokenObject4) == followsExpectedResultTwo);
	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::FOLLOWS_T, DesignEntity::READ, stmtTokenObject4) == followsTExpectedResultTwo);
	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::NEXT, DesignEntity::READ, stmtTokenObject4) == nextExpectedResultTwo);
	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::NEXT_T, DesignEntity::READ, stmtTokenObject4) == nextTExpectedResultTwo);
	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::CALLS, DesignEntity::PROCEDURE, procedureTokenObjectThree) == callsExpectedResultTwo);
	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::CALLS_T, DesignEntity::PROCEDURE, procedureTokenObjectThree) == callsTExpectedResultTwo);
	

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultUsesAll{ { assign_value_one, std::unordered_set<std::string>({variable_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultModifiesAll{ { assign_value_one, std::unordered_set<std::string>({variable_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultParentAll{ { while_value_one, std::unordered_set<std::string>({read_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultParentTAll{ { while_value_one, std::unordered_set<std::string>({read_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultFollowsAll{ { read_value_one, std::unordered_set<std::string>({print_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultFollowsTAll{ { read_value_one, std::unordered_set<std::string>({print_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultNextAll{ { read_value_one, std::unordered_set<std::string>({print_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultNextTAll{ { read_value_one, std::unordered_set<std::string>({print_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultCallsAll{
										{ procedure_value_one, std::unordered_set<std::string>({procedure_value_two, procedure_value_three})},
										{ procedure_value_two, std::unordered_set<std::string>({procedure_value_three})}, };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultCallsTAll{
									{ procedure_value_one, std::unordered_set<std::string>({procedure_value_two, procedure_value_three})},
									{ procedure_value_two, std::unordered_set<std::string>({procedure_value_three})}, };


	REQUIRE(relManager.getAllRelationship(RelationshipType::USES, DesignEntity::ASSIGN, DesignEntity::VARIABLE) == expectedResultUsesAll);
	REQUIRE(relManager.getAllRelationship(RelationshipType::MODIFIES, DesignEntity::ASSIGN, DesignEntity::VARIABLE) == expectedResultModifiesAll);
	REQUIRE(relManager.getAllRelationship(RelationshipType::PARENT, DesignEntity::WHILE, DesignEntity::READ) == expectedResultParentAll);
	REQUIRE(relManager.getAllRelationship(RelationshipType::PARENT_T, DesignEntity::WHILE, DesignEntity::READ) == expectedResultParentTAll);
	REQUIRE(relManager.getAllRelationship(RelationshipType::FOLLOWS, DesignEntity::READ, DesignEntity::PRINT) == expectedResultFollowsAll);
	REQUIRE(relManager.getAllRelationship(RelationshipType::FOLLOWS_T, DesignEntity::READ, DesignEntity::PRINT) == expectedResultFollowsTAll);
	REQUIRE(relManager.getAllRelationship(RelationshipType::NEXT, DesignEntity::READ, DesignEntity::PRINT) == expectedResultNextAll);
	REQUIRE(relManager.getAllRelationship(RelationshipType::NEXT_T, DesignEntity::READ, DesignEntity::PRINT) == expectedResultNextTAll);
	REQUIRE(relManager.getAllRelationship(RelationshipType::CALLS, DesignEntity::PROCEDURE, DesignEntity::PROCEDURE) == expectedResultCallsAll);
	REQUIRE(relManager.getAllRelationship(RelationshipType::CALLS_T, DesignEntity::PROCEDURE, DesignEntity::PROCEDURE) == expectedResultCallsTAll);
}
