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

	REQUIRE(relManager.storeRelationship(nextRelationshipAssignCallOne));
	REQUIRE(relManager.storeRelationship(nextRelationshipCallIfOne));
	REQUIRE(relManager.storeRelationship(nextRelationshipIfPrintOne));
	REQUIRE(relManager.storeRelationship(nextRelationshipPrintReadOne));
	REQUIRE(relManager.storeRelationship(nextRelationshipReadWhileOne));

	REQUIRE(relManager.storeRelationship(callsRelationshipOne));
	REQUIRE(relManager.storeRelationship(callsRelationshipTwo));
	REQUIRE(relManager.storeRelationship(callsRelationshipThree));

	REQUIRE(relManager.storeRelationship(callsTRelationshipOne));
	REQUIRE(relManager.storeRelationship(callsTRelationshipTwo));
	REQUIRE(relManager.storeRelationship(callsTRelationshipThree));

	REQUIRE(relManager.getRelationship(RelationshipType::USES, stmtTokenObject1, variableTokenObject));
	REQUIRE(relManager.getRelationship(RelationshipType::USES, stmtTokenObject1, wildcardTokenObject));

	REQUIRE(relManager.getRelationship(RelationshipType::MODIFIES, stmtTokenObject1, variableTokenObject));
	REQUIRE(relManager.getRelationship(RelationshipType::MODIFIES, stmtTokenObject1, wildcardTokenObject));

	REQUIRE(relManager.getRelationship(RelationshipType::PARENT, stmtTokenObject6, stmtTokenObject5));
	REQUIRE(relManager.getRelationship(RelationshipType::PARENT, wildcardTokenObject, stmtTokenObject5));
	REQUIRE(relManager.getRelationship(RelationshipType::PARENT, stmtTokenObject6, wildcardTokenObject));
	REQUIRE(relManager.getRelationship(RelationshipType::PARENT, wildcardTokenObject, wildcardTokenObject));

	REQUIRE(relManager.getRelationship(RelationshipType::PARENT_T, stmtTokenObject6, stmtTokenObject5));
	REQUIRE(relManager.getRelationship(RelationshipType::PARENT_T, wildcardTokenObject, stmtTokenObject5));
	REQUIRE(relManager.getRelationship(RelationshipType::PARENT_T, stmtTokenObject6, wildcardTokenObject));
	REQUIRE(relManager.getRelationship(RelationshipType::PARENT_T, wildcardTokenObject, wildcardTokenObject));

	REQUIRE(relManager.getRelationship(RelationshipType::FOLLOWS, stmtTokenObject5, stmtTokenObject4));
	REQUIRE(relManager.getRelationship(RelationshipType::FOLLOWS, wildcardTokenObject, stmtTokenObject4));
	REQUIRE(relManager.getRelationship(RelationshipType::FOLLOWS, stmtTokenObject5, wildcardTokenObject));
	REQUIRE(relManager.getRelationship(RelationshipType::FOLLOWS, wildcardTokenObject, wildcardTokenObject));

	REQUIRE(relManager.getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject5, stmtTokenObject4));
	REQUIRE(relManager.getRelationship(RelationshipType::FOLLOWS_T, wildcardTokenObject, stmtTokenObject4));
	REQUIRE(relManager.getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject5, wildcardTokenObject));
	REQUIRE(relManager.getRelationship(RelationshipType::FOLLOWS_T, wildcardTokenObject, wildcardTokenObject));

	REQUIRE(relManager.getRelationship(RelationshipType::NEXT, stmtTokenObject1, stmtTokenObject2));
	REQUIRE(relManager.getRelationship(RelationshipType::NEXT, wildcardTokenObject, stmtTokenObject2));
	REQUIRE(relManager.getRelationship(RelationshipType::NEXT, stmtTokenObject1, wildcardTokenObject));
	REQUIRE(relManager.getRelationship(RelationshipType::NEXT, wildcardTokenObject, wildcardTokenObject));

	REQUIRE(relManager.getRelationship(RelationshipType::CALLS, procedureTokenObject, procedureTokenObjectTwo));
	REQUIRE(relManager.getRelationship(RelationshipType::CALLS, wildcardTokenObject, procedureTokenObjectTwo));
	REQUIRE(relManager.getRelationship(RelationshipType::CALLS, procedureTokenObject, wildcardTokenObject));
	REQUIRE(relManager.getRelationship(RelationshipType::CALLS, wildcardTokenObject, wildcardTokenObject));

	REQUIRE(relManager.getRelationship(RelationshipType::CALLS_T, procedureTokenObject, procedureTokenObjectTwo));
	REQUIRE(relManager.getRelationship(RelationshipType::CALLS_T, wildcardTokenObject, procedureTokenObjectTwo));
	REQUIRE(relManager.getRelationship(RelationshipType::CALLS_T, procedureTokenObject, wildcardTokenObject));
	REQUIRE(relManager.getRelationship(RelationshipType::CALLS_T, wildcardTokenObject, wildcardTokenObject));

	REQUIRE(relManager.getRuntimeRelationship(RelationshipType::NEXT_T, stmtTokenObject1, stmtTokenObject2));

	REQUIRE(relManager.getRuntimeRelationship(RelationshipType::NEXT_T, stmtTokenObject1, wildcardTokenObject));
	REQUIRE(relManager.getRuntimeRelationship(RelationshipType::NEXT_T, wildcardTokenObject, stmtTokenObject2));
	REQUIRE(relManager.getRuntimeRelationship(RelationshipType::NEXT_T, wildcardTokenObject, wildcardTokenObject));


	std::unordered_set<std::string> usesExpectedResult({ variable_value_one });
	std::unordered_set<std::string> modifiesExpectedResult({ variable_value_one });
	std::unordered_set<std::string> parentExpectedResult({ read_value_one });
	std::unordered_set<std::string> parentTExpectedResult({ read_value_one });
	std::unordered_set<std::string> followsExpectedResult({ print_value_one });
	std::unordered_set<std::string> followsTExpectedResult({ print_value_one });
	std::unordered_set<std::string> nextExpectedResult({ while_value_one });
	std::unordered_set<std::string> callsExpectedResult{ procedure_value_two, procedure_value_three };
	std::unordered_set<std::string> callsTExpectedResult{ procedure_value_two, procedure_value_three };


	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::USES, stmtTokenObject1, DesignEntity::VARIABLE) == usesExpectedResult);
	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject1, DesignEntity::VARIABLE) == modifiesExpectedResult);
	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject6, DesignEntity::READ) == parentExpectedResult);
	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject6, DesignEntity::READ) == parentTExpectedResult);
	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::FOLLOWS, stmtTokenObject5, DesignEntity::PRINT) == followsExpectedResult);
	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::FOLLOWS_T, stmtTokenObject5, DesignEntity::PRINT) == followsTExpectedResult);
	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::NEXT, stmtTokenObject5, DesignEntity::WHILE) == nextExpectedResult);
	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::CALLS, procedureTokenObject, DesignEntity::PROCEDURE) == callsExpectedResult);
	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::CALLS_T, procedureTokenObject, DesignEntity::PROCEDURE) == callsTExpectedResult);

	//// For runtime evaluation relationship 
	std::unordered_set<std::string> nextTExpectedResult({ while_value_one });
	std::unordered_set<std::string> nextTExpectedResult2({ read_value_one });
	std::unordered_set<std::string> w_filter = { while_value_one };
	std::unordered_set<std::string> p_filter = { print_value_one };
	std::unordered_set<std::string> r_filter = { read_value_one };
	REQUIRE(relManager.getRuntimeRelationshipByFirst(RelationshipType::NEXT_T, stmtTokenObject5, w_filter) == nextTExpectedResult);

	REQUIRE(relManager.getRuntimeRelationshipWithFirstWildcard(RelationshipType::NEXT_T, p_filter, r_filter) == nextTExpectedResult2);

	
	std::unordered_set<std::string> usesExpectedResultTwo({ assign_value_one });
	std::unordered_set<std::string> modifiesExpectedResultTwo({ assign_value_one });
	std::unordered_set<std::string> parentExpectedResultTwo({ while_value_one });
	std::unordered_set<std::string> parentTExpectedResultTwo({ while_value_one });
	std::unordered_set<std::string> followsExpectedResultTwo({ read_value_one });
	std::unordered_set<std::string> followsTExpectedResultTwo({ read_value_one });
	std::unordered_set<std::string> nextExpectedResultTwo({ if_value_one });
	std::unordered_set<std::string> callsExpectedResultTwo{ procedure_value_one, procedure_value_two };
	std::unordered_set<std::string> callsTExpectedResultTwo{ procedure_value_one, procedure_value_two };
	

	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::USES, DesignEntity::ASSIGN, variableTokenObject) == usesExpectedResultTwo);
	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::ASSIGN, variableTokenObject) == modifiesExpectedResultTwo);
	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::WHILE, stmtTokenObject5) == parentExpectedResultTwo);
	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::WHILE, stmtTokenObject5) == parentTExpectedResultTwo);
	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::FOLLOWS, DesignEntity::READ, stmtTokenObject4) == followsExpectedResultTwo);
	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::FOLLOWS_T, DesignEntity::READ, stmtTokenObject4) == followsTExpectedResultTwo);
	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::NEXT, DesignEntity::IF, stmtTokenObject4) == nextExpectedResultTwo);
	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::CALLS, DesignEntity::PROCEDURE, procedureTokenObjectThree) == callsExpectedResultTwo);
	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::CALLS_T, DesignEntity::PROCEDURE, procedureTokenObjectThree) == callsTExpectedResultTwo);

	// For runtime evaluation relationship
	std::unordered_set<std::string> nextTExpectedResultTwo({ call_value_one });
	std::unordered_set<std::string> nextTExpectedResultTwo2({ print_value_one });
	std::unordered_set<std::string> c_filter = { call_value_one };
	
	REQUIRE(relManager.getRuntimeRelationshipBySecond(RelationshipType::NEXT_T, stmtTokenObject4, c_filter) == nextTExpectedResultTwo);
	
	REQUIRE(relManager.getRuntimeRelationshipWithSecondWildcard(RelationshipType::NEXT_T, p_filter, r_filter) == nextTExpectedResultTwo2);

	std::unordered_set<std::string> parentFirstWildcardExpectedResult({ read_value_one });
	std::unordered_set<std::string> parentTFirstWildcardExpectedResult({ read_value_one });
	std::unordered_set<std::string> followsFirstWildcardExpectedResult({ print_value_one });
	std::unordered_set<std::string> followsTFirstWildcardExpectedResult({ print_value_one });
	std::unordered_set<std::string> nextFirstWildcardExpectedResult({ while_value_one });
	std::unordered_set<std::string> callsFirstWildcardExpectedResult{ procedure_value_two, procedure_value_three };
	std::unordered_set<std::string> callsTFirstWildcardExpectedResult{ procedure_value_two, procedure_value_three };

	REQUIRE(relManager.getRelationshipWithFirstWildcard(RelationshipType::PARENT, DesignEntity::READ) == parentFirstWildcardExpectedResult);
	REQUIRE(relManager.getRelationshipWithFirstWildcard(RelationshipType::PARENT_T, DesignEntity::READ) == parentTFirstWildcardExpectedResult);
	REQUIRE(relManager.getRelationshipWithFirstWildcard(RelationshipType::FOLLOWS, DesignEntity::PRINT) == followsFirstWildcardExpectedResult);
	REQUIRE(relManager.getRelationshipWithFirstWildcard(RelationshipType::FOLLOWS_T, DesignEntity::PRINT) == followsTFirstWildcardExpectedResult);
	REQUIRE(relManager.getRelationshipWithFirstWildcard(RelationshipType::NEXT, DesignEntity::WHILE) == nextFirstWildcardExpectedResult);
	REQUIRE(relManager.getRelationshipWithFirstWildcard(RelationshipType::CALLS, DesignEntity::PROCEDURE) == callsFirstWildcardExpectedResult);
	REQUIRE(relManager.getRelationshipWithFirstWildcard(RelationshipType::CALLS_T, DesignEntity::PROCEDURE) == callsTFirstWildcardExpectedResult);

	std::unordered_set<std::string> usesSecondWildcardExpectedResult({ assign_value_one });
	std::unordered_set<std::string> modifiesSecondWildcardExpectedResult({ assign_value_one });
	std::unordered_set<std::string> parentSecondWildcardExpectedResult({ while_value_one });
	std::unordered_set<std::string> parentTSecondWildcardExpectedResult({ while_value_one });
	std::unordered_set<std::string> followsSecondWildcardExpectedResult({ read_value_one });
	std::unordered_set<std::string> followsTSecondWildcardExpectedResult({ read_value_one });
	std::unordered_set<std::string> nextSecondWildcardExpectedResult({ if_value_one });
	std::unordered_set<std::string> callsSecondWildcardExpectedResult{ procedure_value_one, procedure_value_two };
	std::unordered_set<std::string> callsTSecondWildcardExpectedResult{ procedure_value_one, procedure_value_two };

	REQUIRE(relManager.getRelationshipWithSecondWildcard(RelationshipType::USES, DesignEntity::ASSIGN) == usesSecondWildcardExpectedResult);
	REQUIRE(relManager.getRelationshipWithSecondWildcard(RelationshipType::MODIFIES, DesignEntity::ASSIGN) == modifiesSecondWildcardExpectedResult);
	REQUIRE(relManager.getRelationshipWithSecondWildcard(RelationshipType::PARENT, DesignEntity::WHILE) == parentSecondWildcardExpectedResult);
	REQUIRE(relManager.getRelationshipWithSecondWildcard(RelationshipType::PARENT_T, DesignEntity::WHILE) == parentTSecondWildcardExpectedResult);
	REQUIRE(relManager.getRelationshipWithSecondWildcard(RelationshipType::FOLLOWS, DesignEntity::READ) == followsSecondWildcardExpectedResult);
	REQUIRE(relManager.getRelationshipWithSecondWildcard(RelationshipType::FOLLOWS_T, DesignEntity::READ) == followsTSecondWildcardExpectedResult);
	REQUIRE(relManager.getRelationshipWithSecondWildcard(RelationshipType::NEXT, DesignEntity::IF) == nextSecondWildcardExpectedResult);
	REQUIRE(relManager.getRelationshipWithSecondWildcard(RelationshipType::CALLS, DesignEntity::PROCEDURE) == callsSecondWildcardExpectedResult);
	REQUIRE(relManager.getRelationshipWithSecondWildcard(RelationshipType::CALLS_T, DesignEntity::PROCEDURE) == callsTSecondWildcardExpectedResult);

	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultUsesAll{ { assign_value_one, std::unordered_set<std::string>({variable_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultModifiesAll{ { assign_value_one, std::unordered_set<std::string>({variable_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultParentAll{ { while_value_one, std::unordered_set<std::string>({read_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultParentTAll{ { while_value_one, std::unordered_set<std::string>({read_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultFollowsAll{ { read_value_one, std::unordered_set<std::string>({print_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultFollowsTAll{ { read_value_one, std::unordered_set<std::string>({print_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultNextAll{ { print_value_one, std::unordered_set<std::string>({read_value_one}) } };
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
	REQUIRE(relManager.getAllRelationship(RelationshipType::NEXT, DesignEntity::PRINT, DesignEntity::READ) == expectedResultNextAll);
	REQUIRE(relManager.getAllRelationship(RelationshipType::CALLS, DesignEntity::PROCEDURE, DesignEntity::PROCEDURE) == expectedResultCallsAll);
	REQUIRE(relManager.getAllRelationship(RelationshipType::CALLS_T, DesignEntity::PROCEDURE, DesignEntity::PROCEDURE) == expectedResultCallsTAll);

	// For runtime evaluation relationship
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultNextTAll{ { print_value_one, std::unordered_set<std::string>({read_value_one}) } };

	REQUIRE(relManager.getAllRuntimeRelationship(RelationshipType::NEXT_T, p_filter, r_filter) == expectedResultNextTAll);
	
}

TEST_CASE("Runtime Evaluator Manager test") {
	RelationshipManager relManager = RelationshipManager();

	// Populate PKB for Next
	REQUIRE(relManager.storeRelationship(nextRelationshipAffectsOne));
	REQUIRE(relManager.storeRelationship(nextRelationshipAffectsTwo));
	REQUIRE(relManager.storeRelationship(nextRelationshipAffectsThree));
	REQUIRE(relManager.storeRelationship(nextRelationshipAffectsFour));
	REQUIRE(relManager.storeRelationship(nextRelationshipAffectsFive));
	REQUIRE(relManager.storeRelationship(nextRelationshipAffectsSix));
	REQUIRE(relManager.storeRelationship(nextRelationshipAffectsSeven));

	// Populate PKB for Modifies
	REQUIRE(relManager.storeRelationship(modifyRelationshipAffectsOne));
	REQUIRE(relManager.storeRelationship(modifyRelationshipAffectsTwo));
	REQUIRE(relManager.storeRelationship(modifyRelationshipAffectsThree));
	REQUIRE(relManager.storeRelationship(modifyRelationshipAffectsFour));
	REQUIRE(relManager.storeRelationship(modifyRelationshipAffectsFive));
	REQUIRE(relManager.storeRelationship(modifyRelationshipAffectsSix));

	// Populate PKB for Uses
	REQUIRE(relManager.storeRelationship(usesRelationshipAffectsOne));
	REQUIRE(relManager.storeRelationship(usesRelationshipAffectsTwo));
	REQUIRE(relManager.storeRelationship(usesRelationshipAffectsThree));
	REQUIRE(relManager.storeRelationship(usesRelationshipAffectsFour));

	// Test for affects(1, 2)
	REQUIRE(relManager.getRuntimeRelationship(RelationshipType::AFFECTS, stmtTokenObject1, stmtTokenObject5));
	REQUIRE(relManager.getRuntimeRelationship(RelationshipType::AFFECTS, stmtTokenObject3, stmtTokenObject5));
	REQUIRE(!relManager.getRuntimeRelationship(RelationshipType::AFFECTS, stmtTokenObject1, stmtTokenObject7));
	REQUIRE(!relManager.getRuntimeRelationship(RelationshipType::AFFECTS, stmtTokenObject1, stmtTokenObject4));

	REQUIRE(relManager.getRuntimeRelationship(RelationshipType::AFFECTS, wildcardTokenObject, stmtTokenObject5));
	REQUIRE(relManager.getRuntimeRelationship(RelationshipType::AFFECTS, stmtTokenObject3, wildcardTokenObject));
	REQUIRE(relManager.getRuntimeRelationship(RelationshipType::AFFECTS, wildcardTokenObject, wildcardTokenObject));

	std::unordered_set<std::string> a_filter = { stmt1, stmt3, stmt4, stmt5, stmt7 };
	std::unordered_set<std::string> empty = {};

	// Test for Affects(1, a)
	std::unordered_set<std::string> expectedResultByFirst = { stmt5 };
	std::unordered_set<std::string> expectedResultByFirst2 = { stmt7 };
	std::unordered_set<std::string> expectedResultByFirst3 = { stmt5, stmt7 };


	REQUIRE(relManager.getRuntimeRelationshipByFirst(RelationshipType::AFFECTS, stmtTokenObject1, a_filter) == expectedResultByFirst);
	REQUIRE(relManager.getRuntimeRelationshipByFirst(RelationshipType::AFFECTS, stmtTokenObject2, a_filter) == empty);
	REQUIRE(relManager.getRuntimeRelationshipByFirst(RelationshipType::AFFECTS, stmtTokenObject3, a_filter) == expectedResultByFirst);
	REQUIRE(relManager.getRuntimeRelationshipByFirst(RelationshipType::AFFECTS, stmtTokenObject4, a_filter) == empty);
	REQUIRE(relManager.getRuntimeRelationshipByFirst(RelationshipType::AFFECTS, stmtTokenObject5, a_filter) == expectedResultByFirst2);
	REQUIRE(relManager.getRuntimeRelationshipByFirst(RelationshipType::AFFECTS, stmtTokenObject6, a_filter) == empty);
	REQUIRE(relManager.getRuntimeRelationshipByFirst(RelationshipType::AFFECTS, stmtTokenObject7, a_filter) == empty);

	REQUIRE(relManager.getRuntimeRelationshipWithFirstWildcard(RelationshipType::AFFECTS, a_filter, a_filter) == expectedResultByFirst3);

	// Test for Affects(a, 2)
	std::unordered_set<std::string> expectedResultBySecond = { stmt1, stmt3 };
	std::unordered_set<std::string> expectedResultBySecond2 = { stmt5 };
	std::unordered_set<std::string> expectedResultBySecond3 = { stmt1, stmt3, stmt5 };

	REQUIRE(relManager.getRuntimeRelationshipBySecond(RelationshipType::AFFECTS, stmtTokenObject1, a_filter) == empty);
	REQUIRE(relManager.getRuntimeRelationshipBySecond(RelationshipType::AFFECTS, stmtTokenObject2, a_filter) == empty);
	REQUIRE(relManager.getRuntimeRelationshipBySecond(RelationshipType::AFFECTS, stmtTokenObject3, a_filter) == empty);
	REQUIRE(relManager.getRuntimeRelationshipBySecond(RelationshipType::AFFECTS, stmtTokenObject4, a_filter) == empty);
	REQUIRE(relManager.getRuntimeRelationshipBySecond(RelationshipType::AFFECTS, stmtTokenObject5, a_filter) == expectedResultBySecond);
	REQUIRE(relManager.getRuntimeRelationshipBySecond(RelationshipType::AFFECTS, stmtTokenObject6, a_filter) == empty);
	REQUIRE(relManager.getRuntimeRelationshipBySecond(RelationshipType::AFFECTS, stmtTokenObject7, a_filter) == expectedResultBySecond2);

	REQUIRE(relManager.getRuntimeRelationshipWithSecondWildcard(RelationshipType::AFFECTS, a_filter, a_filter) == expectedResultBySecond3);

	std::unordered_map<std::string, std::unordered_set<std::string>> emptyMap = {};
	// Test for Affects(a1, a2)
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAll{
									{ stmt1, std::unordered_set<std::string>({stmt5})},
									{ stmt3, std::unordered_set<std::string>({stmt5})},
									{ stmt5, std::unordered_set<std::string>({ stmt7 })} };

	std::unordered_set<std::string> if_filter = { stmt2 };

	REQUIRE(relManager.getAllRuntimeRelationship(RelationshipType::AFFECTS, a_filter, a_filter) == expectedResultAll);
	REQUIRE(relManager.getAllRuntimeRelationship(RelationshipType::AFFECTS, if_filter, a_filter) == emptyMap);

	///// Test For Affects* Relationship

	// Test for affectsT(1, 2)
	REQUIRE(relManager.getRuntimeRelationship(RelationshipType::AFFECTS_T, stmtTokenObject1, stmtTokenObject5));
	REQUIRE(relManager.getRuntimeRelationship(RelationshipType::AFFECTS_T, stmtTokenObject3, stmtTokenObject5));
	REQUIRE(relManager.getRuntimeRelationship(RelationshipType::AFFECTS_T, stmtTokenObject1, stmtTokenObject7));

	REQUIRE(!relManager.getRuntimeRelationship(RelationshipType::AFFECTS_T, stmtTokenObject1, stmtTokenObject4));

	REQUIRE(relManager.getRuntimeRelationship(RelationshipType::AFFECTS_T, wildcardTokenObject, stmtTokenObject7));
	REQUIRE(relManager.getRuntimeRelationship(RelationshipType::AFFECTS_T, stmtTokenObject1, wildcardTokenObject));
	REQUIRE(relManager.getRuntimeRelationship(RelationshipType::AFFECTS_T, wildcardTokenObject, wildcardTokenObject));

	std::unordered_set<std::string> a_filterT = { stmt1, stmt3, stmt4, stmt5, stmt7 };
	std::unordered_set<std::string> emptyT = {};

	// Test for AffectsT(1, a)
	std::unordered_set<std::string> expectedResultByFirstT = { stmt5, stmt7 };
	std::unordered_set<std::string> expectedResultByFirstT2 = { stmt7 };

	REQUIRE(relManager.getRuntimeRelationshipByFirst(RelationshipType::AFFECTS_T, stmtTokenObject1, a_filter) == expectedResultByFirstT);
	REQUIRE(relManager.getRuntimeRelationshipByFirst(RelationshipType::AFFECTS_T, stmtTokenObject2, a_filter) == emptyT);
	REQUIRE(relManager.getRuntimeRelationshipByFirst(RelationshipType::AFFECTS_T, stmtTokenObject3, a_filter) == expectedResultByFirstT);
	REQUIRE(relManager.getRuntimeRelationshipByFirst(RelationshipType::AFFECTS_T, stmtTokenObject4, a_filter) == emptyT);
	REQUIRE(relManager.getRuntimeRelationshipByFirst(RelationshipType::AFFECTS_T, stmtTokenObject5, a_filter) == expectedResultByFirstT2);
	REQUIRE(relManager.getRuntimeRelationshipByFirst(RelationshipType::AFFECTS_T, stmtTokenObject6, a_filter) == emptyT);
	REQUIRE(relManager.getRuntimeRelationshipByFirst(RelationshipType::AFFECTS_T, stmtTokenObject7, a_filter) == emptyT);

	REQUIRE(relManager.getRuntimeRelationshipWithFirstWildcard(RelationshipType::AFFECTS_T, a_filter, a_filter) == expectedResultByFirstT);

	// Test for Affects(a, 2)
	std::unordered_set<std::string> expectedResultBySecondT = { stmt1, stmt3 };
	std::unordered_set<std::string> expectedResultBySecondT2 = { stmt1,stmt3, stmt5 };

	REQUIRE(relManager.getRuntimeRelationshipBySecond(RelationshipType::AFFECTS_T, stmtTokenObject1, a_filter) == emptyT);
	REQUIRE(relManager.getRuntimeRelationshipBySecond(RelationshipType::AFFECTS_T, stmtTokenObject2, a_filter) == emptyT);
	REQUIRE(relManager.getRuntimeRelationshipBySecond(RelationshipType::AFFECTS_T, stmtTokenObject3, a_filter) == emptyT);
	REQUIRE(relManager.getRuntimeRelationshipBySecond(RelationshipType::AFFECTS_T, stmtTokenObject4, a_filter) == emptyT);
	REQUIRE(relManager.getRuntimeRelationshipBySecond(RelationshipType::AFFECTS_T, stmtTokenObject5, a_filter) == expectedResultBySecondT);
	REQUIRE(relManager.getRuntimeRelationshipBySecond(RelationshipType::AFFECTS_T, stmtTokenObject6, a_filter) == emptyT);
	REQUIRE(relManager.getRuntimeRelationshipBySecond(RelationshipType::AFFECTS_T, stmtTokenObject7, a_filter) == expectedResultBySecondT2);

	REQUIRE(relManager.getRuntimeRelationshipWithSecondWildcard(RelationshipType::AFFECTS_T, a_filter, a_filter) == expectedResultBySecondT2);

	std::unordered_map<std::string, std::unordered_set<std::string>> emptyMapT = {};
	// Test for AffectsT(a1, a2)
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAllT{
									{ stmt1, std::unordered_set<std::string>({stmt5, stmt7})},
									{ stmt3, std::unordered_set<std::string>({stmt5, stmt7})},
									{ stmt5, std::unordered_set<std::string>({ stmt7 })} };

	std::unordered_set<std::string> if_filterT = { stmt2 };

	REQUIRE(relManager.getAllRuntimeRelationship(RelationshipType::AFFECTS_T, a_filterT, a_filterT) == expectedResultAllT);
	REQUIRE(relManager.getAllRuntimeRelationship(RelationshipType::AFFECTS_T, if_filterT, a_filterT) == emptyMapT);
}
