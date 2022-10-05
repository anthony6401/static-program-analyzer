#include "models/Entity/DesignEntity.h"
#include "models/Relationship/Relationship.h"
#include "models/Relationship/UsesRelationship.h"
#include "models/Relationship/RelationshipType.h"

#include "components/pkb/clients/QPSClient.h"
#include "components/pkb/clients/SPClient.h"

#include "components/pkb/pkb.h"

#include "../EntityObject.h"
#include "../ReuseableTokenObject.h"
#include "../RelationshipObject.h"


#include <catch.hpp>

static Relationship* usesRel = new UsesRelationship(assignEntity, variableEntity); 

PKB* pkb = new PKB();


TEST_CASE("SP Client test") {
	SPClient spClient = SPClient(pkb);

	REQUIRE(spClient.storeRelationship(usesRel));
	REQUIRE(spClient.storeConstant(constantEntity));

	//Pattern
	REQUIRE(spClient.storePattern(assignPatternOne));
	REQUIRE(spClient.storePattern(assignPatternTwo));
	REQUIRE(spClient.storePattern(assignPatternThree));
	REQUIRE(spClient.storePattern(assignPatternFour));
	REQUIRE(spClient.storePattern(assignPatternFive));
	REQUIRE(spClient.storePattern(assignPatternSix));
	REQUIRE(spClient.storePattern(assignPatternSeven));
	REQUIRE(spClient.storePattern(assignPatternEight));

	//Relationship
	REQUIRE(spClient.storeRelationship(usesRelationshipAssignOne));
	REQUIRE(spClient.storeRelationship(usesRelationshipProcOne));
	REQUIRE(spClient.storeRelationship(usesRelationshipPrintOne));
	REQUIRE(spClient.storeRelationship(usesRelationshipWhileOne));
	REQUIRE(spClient.storeRelationship(usesRelationshipIfOne));


	REQUIRE(spClient.storeRelationship(modifyRelationshipAssignOne));
	REQUIRE(spClient.storeRelationship(modifyRelationshipProcOne));
	REQUIRE(spClient.storeRelationship(modifyRelationshipReadOne));
	REQUIRE(spClient.storeRelationship(modifyRelationshipWhileOne));


	REQUIRE(spClient.storeRelationship(parentRelationshipWhileReadOne));
	REQUIRE(spClient.storeRelationship(parentRelationshipWhilePrintOne));
	REQUIRE(spClient.storeRelationship(parentRelationshipIfAssignOne));
	REQUIRE(spClient.storeRelationship(parentRelationshipIfCallOne));

	REQUIRE(spClient.storeRelationship(parentTRelationshipWhileReadOne));
	REQUIRE(spClient.storeRelationship(parentTRelationshipWhilePrintOne));
	REQUIRE(spClient.storeRelationship(parentTRelationshipIfAssignOne));
	REQUIRE(spClient.storeRelationship(parentTRelationshipIfCallOne));

	REQUIRE(spClient.storeRelationship(followsRelationshipReadPrintOne));
	REQUIRE(spClient.storeRelationship(followsRelationshipPrintAssignOne));
	REQUIRE(spClient.storeRelationship(followsRelationshipAssignCallOne));
	REQUIRE(spClient.storeRelationship(followsRelationshipCallWhileOne));
	REQUIRE(spClient.storeRelationship(followsRelationshipWhileIfOne));
	REQUIRE(spClient.storeRelationship(followsRelationshipIfReadOne));

	REQUIRE(spClient.storeRelationship(followsTRelationshipReadPrintOne));
	REQUIRE(spClient.storeRelationship(followsTRelationshipPrintAssignOne));
	REQUIRE(spClient.storeRelationship(followsTRelationshipAssignCallOne));
	REQUIRE(spClient.storeRelationship(followsTRelationshipCallWhileOne));
	REQUIRE(spClient.storeRelationship(followsTRelationshipWhileIfOne));
	REQUIRE(spClient.storeRelationship(followsTRelationshipIfReadOne));

	REQUIRE(spClient.storeRelationship(nextRelationshipReadPrintOne));
	REQUIRE(spClient.storeRelationship(nextRelationshipPrintAssignOne));
	REQUIRE(spClient.storeRelationship(nextRelationshipAssignCallOne));
	REQUIRE(spClient.storeRelationship(nextRelationshipCallWhileOne));
	REQUIRE(spClient.storeRelationship(nextRelationshipWhileIfOne));
	REQUIRE(spClient.storeRelationship(nextRelationshipIfReadOne));

	//REQUIRE(spClient.storeRelationship(nextTRelationshipReadPrintOne));
	//REQUIRE(spClient.storeRelationship(nextTRelationshipPrintAssignOne));
	//REQUIRE(spClient.storeRelationship(nextTRelationshipAssignCallOne));
	//REQUIRE(spClient.storeRelationship(nextTRelationshipCallWhileOne));
	//REQUIRE(spClient.storeRelationship(nextTRelationshipWhileIfOne));
	//REQUIRE(spClient.storeRelationship(nextTRelationshipIfReadOne));

	REQUIRE(spClient.storeRelationship(callsRelationshipOne));
	REQUIRE(spClient.storeRelationship(callsRelationshipTwo));
	REQUIRE(spClient.storeRelationship(callsRelationshipThree));

	REQUIRE(spClient.storeRelationship(callsTRelationshipOne));
	REQUIRE(spClient.storeRelationship(callsTRelationshipTwo));
	REQUIRE(spClient.storeRelationship(callsTRelationshipThree));

}

TEST_CASE("QPS Client test") {
	QPSClient qpsClient = QPSClient(pkb);

	std::unordered_set<std::string> ass_set;
	ass_set.insert(assign_value_one);

	std::unordered_set<std::string> var_set;
	var_set.insert(variable_value_one);

	std::unordered_set<std::string> const_set;
	const_set.insert(constant_value_one);

	REQUIRE(qpsClient.getAllEntity(DesignEntity::ASSIGN) == ass_set);
	REQUIRE(qpsClient.getAllEntity(DesignEntity::VARIABLE) == var_set);
	REQUIRE(qpsClient.getAllEntity(DesignEntity::CONSTANT) == const_set);

	//Pattern
	std::unordered_set<std::string> assignGetPatternNameNameOne = qpsClient.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSecondOne);
	std::unordered_set<std::string> assignGetPatternNameNameTwo = qpsClient.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, assignPatternTokenObjectSecondTwo);
	std::unordered_set<std::string> assignGetPatternNameSubexprOne = qpsClient.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSubexprOne);
	std::unordered_set<std::string> assignGetPatternNameSubexprTwo = qpsClient.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, assignPatternTokenObjectSubexprTwo);
	std::unordered_set<std::string> assignGetPatternNameSubexprThree = qpsClient.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSubexprThree);
	std::unordered_set<std::string> assignGetPatternNameWildcardOne = qpsClient.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, wildCardTokenObject);
	std::unordered_set<std::string> assignGetPatternNameWildcardTwo = qpsClient.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, wildCardTokenObject);

	std::unordered_set<std::string> expectedGetPatternNameNameOne({ assignLineNumOne, assignLineNumEight });
	std::unordered_set<std::string> expectedGetPatternNameNameTwo({ assignLineNumSix });
	std::unordered_set<std::string> expectedGetPatternNameSubexprOne({ assignLineNumFive });
	std::unordered_set<std::string> expectedGetPatternNameSubexprTwo({ assignLineNumTwo, assignLineNumSix });
	std::unordered_set<std::string> expectedGetPatternNameSubexprThree({ assignLineNumOne, assignLineNumFive, assignLineNumEight });
	std::unordered_set<std::string> expectedGetPatternNameWildcardOne({ assignLineNumOne, assignLineNumFive, assignLineNumEight });
	std::unordered_set<std::string> expectedGetPatternNameWilcardTwo({ assignLineNumTwo, assignLineNumSix });

	REQUIRE(assignGetPatternNameNameOne == expectedGetPatternNameNameOne);
	REQUIRE(assignGetPatternNameNameOne == expectedGetPatternNameNameOne);
	REQUIRE(assignGetPatternNameNameTwo == expectedGetPatternNameNameTwo);
	REQUIRE(assignGetPatternNameSubexprOne == expectedGetPatternNameSubexprOne);
	REQUIRE(assignGetPatternNameSubexprTwo == expectedGetPatternNameSubexprTwo);
	REQUIRE(assignGetPatternNameSubexprThree == expectedGetPatternNameSubexprThree);
	REQUIRE(assignGetPatternNameWildcardOne == expectedGetPatternNameWildcardOne);
	REQUIRE(assignGetPatternNameWildcardTwo == expectedGetPatternNameWilcardTwo);

	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameNameOne = qpsClient.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSecondOne);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameNameTwo = qpsClient.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSecondTwo);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprOne = qpsClient.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprOne);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprTwo = qpsClient.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprTwo);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprThree = qpsClient.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprThree);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameWildcard = qpsClient.getPatternPair(DesignEntity::ASSIGN, wildCardTokenObject);

	std::vector<std::pair<std::string, std::string>> expectedGetPatternPairNameNameOne{ {assignLineNumOne, assignFirstValueOne},
																						{assignLineNumEight, assignFirstValueEight} };
	std::vector<std::pair<std::string, std::string>> expectedGetPatternPairNameNameTwo{ {assignLineNumSix, assignFirstValueSix},
																					{assignLineNumSeven, assignFirstValueSeven} };
	std::vector<std::pair<std::string, std::string>> expectedGetPatternPairNameSubexprOne{ {assignLineNumTwo, assignFirstValueTwo},
																						{assignLineNumThree, assignFirstValueThree},
																						{assignLineNumFive, assignFirstValueFive} };
	std::vector<std::pair<std::string, std::string>> expectedGetPatternPairNameSubexprTwo{ {assignLineNumOne, assignFirstValueOne},
																						{assignLineNumTwo, assignFirstValueTwo},
																						{assignLineNumThree, assignFirstValueThree},
																						{assignLineNumSix, assignFirstValueSix},
																						{assignLineNumSeven, assignFirstValueSeven},
																						{assignLineNumEight, assignFirstValueEight} };
	std::vector<std::pair<std::string, std::string>> expectedGetPatternPairNameSubexprThree{ {assignLineNumOne, assignFirstValueOne},
																						 {assignLineNumFour, assignFirstValueFour},
																						 {assignLineNumFive, assignFirstValueFive},
																						 {assignLineNumEight, assignFirstValueEight} };
	std::vector<std::pair<std::string, std::string>> expectedGetPatternPairNameWilcard{ {assignLineNumOne, assignFirstValueOne},
																						{assignLineNumTwo, assignFirstValueTwo},
																						{assignLineNumThree, assignFirstValueThree},
																						{assignLineNumFour, assignFirstValueFour},
																						{assignLineNumFive, assignFirstValueFive},
																						{assignLineNumSix, assignFirstValueSix},
																						{assignLineNumSeven, assignFirstValueSeven},
																						{assignLineNumEight, assignFirstValueEight} };

	sort(assignGetPatternPairNameNameOne.begin(), assignGetPatternPairNameNameOne.end());
	sort(assignGetPatternPairNameNameTwo.begin(), assignGetPatternPairNameNameTwo.end());
	sort(assignGetPatternPairNameSubexprOne.begin(), assignGetPatternPairNameSubexprOne.end());
	sort(assignGetPatternPairNameSubexprTwo.begin(), assignGetPatternPairNameSubexprTwo.end());
	sort(assignGetPatternPairNameSubexprThree.begin(), assignGetPatternPairNameSubexprThree.end());
	sort(assignGetPatternPairNameWildcard.begin(), assignGetPatternPairNameWildcard.end());

	REQUIRE(assignGetPatternPairNameNameOne == expectedGetPatternPairNameNameOne);
	REQUIRE(assignGetPatternPairNameNameTwo == expectedGetPatternPairNameNameTwo);
	REQUIRE(assignGetPatternPairNameSubexprOne == expectedGetPatternPairNameSubexprOne);
	REQUIRE(assignGetPatternPairNameSubexprTwo == expectedGetPatternPairNameSubexprTwo);
	REQUIRE(assignGetPatternPairNameSubexprThree == expectedGetPatternPairNameSubexprThree);
	REQUIRE(assignGetPatternPairNameWildcard == expectedGetPatternPairNameWilcard);

	//Relationship
	REQUIRE(qpsClient.getRelationship(RelationshipType::USES, stmtTokenObject1, variableTokenObject));
	REQUIRE(qpsClient.getRelationship(RelationshipType::MODIFIES, stmtTokenObject1, variableTokenObject));
	REQUIRE(qpsClient.getRelationship(RelationshipType::PARENT, stmtTokenObject6, stmtTokenObject5));
	REQUIRE(qpsClient.getRelationship(RelationshipType::PARENT_T, stmtTokenObject6, stmtTokenObject5));
	REQUIRE(qpsClient.getRelationship(RelationshipType::FOLLOWS, stmtTokenObject5, stmtTokenObject4));
	REQUIRE(qpsClient.getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject5, stmtTokenObject4));
	REQUIRE(qpsClient.getRelationship(RelationshipType::NEXT, stmtTokenObject1, stmtTokenObject2));
	//REQUIRE(qpsClient.getRelationship(RelationshipType::NEXT_T, stmtTokenObject1, stmtTokenObject2));
	REQUIRE(qpsClient.getRelationship(RelationshipType::CALLS, procedureTokenObject, procedureTokenObjectTwo));
	REQUIRE(qpsClient.getRelationship(RelationshipType::CALLS_T, procedureTokenObject, procedureTokenObjectTwo));

	std::unordered_set<std::string> usesExpectedResult({ variable_value_one });
	std::unordered_set<std::string> modifiesExpectedResult({ variable_value_one });
	std::unordered_set<std::string> parentExpectedResult({ read_value_one });
	std::unordered_set<std::string> parentTExpectedResult({ read_value_one });
	std::unordered_set<std::string> followsExpectedResult({ print_value_one });
	std::unordered_set<std::string> followsTExpectedResult({ print_value_one });
	std::unordered_set<std::string> nextExpectedResult({ print_value_one });
	//std::unordered_set<std::string> nextTExpectedResult({ print_value_one });
	std::unordered_set<std::string> callsExpectedResult{ procedure_value_two, procedure_value_three };
	std::unordered_set<std::string> callsTExpectedResult{ procedure_value_two, procedure_value_three };

	REQUIRE(qpsClient.getRelationshipByFirst(RelationshipType::USES, stmtTokenObject1, DesignEntity::VARIABLE) == usesExpectedResult);
	REQUIRE(qpsClient.getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject1, DesignEntity::VARIABLE) == modifiesExpectedResult);
	REQUIRE(qpsClient.getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject6, DesignEntity::READ) == parentExpectedResult);
	REQUIRE(qpsClient.getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject6, DesignEntity::READ) == parentTExpectedResult);
	REQUIRE(qpsClient.getRelationshipByFirst(RelationshipType::FOLLOWS, stmtTokenObject5, DesignEntity::PRINT) == followsExpectedResult);
	REQUIRE(qpsClient.getRelationshipByFirst(RelationshipType::FOLLOWS_T, stmtTokenObject5, DesignEntity::PRINT) == followsTExpectedResult);
	REQUIRE(qpsClient.getRelationshipByFirst(RelationshipType::NEXT, stmtTokenObject5, DesignEntity::PRINT) == nextExpectedResult);
	//REQUIRE(qpsClient.getRelationshipByFirst(RelationshipType::NEXT_T, stmtTokenObject5, DesignEntity::PRINT) == nextTExpectedResult);
	REQUIRE(qpsClient.getRelationshipByFirst(RelationshipType::CALLS, procedureTokenObject, DesignEntity::PROCEDURE) == callsExpectedResult);
	REQUIRE(qpsClient.getRelationshipByFirst(RelationshipType::CALLS_T, procedureTokenObject, DesignEntity::PROCEDURE) == callsTExpectedResult);


	std::unordered_set<std::string> usesExpectedResultTwo({ assign_value_one });
	std::unordered_set<std::string> modifiesExpectedResultTwo({ assign_value_one });
	std::unordered_set<std::string> parentExpectedResultTwo({ while_value_one });
	std::unordered_set<std::string> parentTExpectedResultTwo({ while_value_one });
	std::unordered_set<std::string> followsExpectedResultTwo({ read_value_one });
	std::unordered_set<std::string> followsTExpectedResultTwo({ read_value_one });
	std::unordered_set<std::string> nextExpectedResultTwo({ read_value_one });
	//std::unordered_set<std::string> nextTExpectedResultTwo({ read_value_one });
	std::unordered_set<std::string> callsExpectedResultTwo{ procedure_value_one, procedure_value_two };
	std::unordered_set<std::string> callsTExpectedResultTwo{ procedure_value_one, procedure_value_two };

	REQUIRE(qpsClient.getRelationshipBySecond(RelationshipType::USES, DesignEntity::ASSIGN, variableTokenObject) == usesExpectedResultTwo);
	REQUIRE(qpsClient.getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::ASSIGN, variableTokenObject) == modifiesExpectedResultTwo);
	REQUIRE(qpsClient.getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::WHILE, stmtTokenObject5) == parentExpectedResultTwo);
	REQUIRE(qpsClient.getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::WHILE, stmtTokenObject5) == parentTExpectedResultTwo);
	REQUIRE(qpsClient.getRelationshipBySecond(RelationshipType::FOLLOWS, DesignEntity::READ, stmtTokenObject4) == followsExpectedResultTwo);
	REQUIRE(qpsClient.getRelationshipBySecond(RelationshipType::FOLLOWS_T, DesignEntity::READ, stmtTokenObject4) == followsTExpectedResultTwo);
	REQUIRE(qpsClient.getRelationshipBySecond(RelationshipType::NEXT, DesignEntity::READ, stmtTokenObject4) == nextExpectedResultTwo);
	//REQUIRE(qpsClient.getRelationshipBySecond(RelationshipType::NEXT_T, DesignEntity::READ, stmtTokenObject4) == nextTExpectedResultTwo);
	REQUIRE(qpsClient.getRelationshipBySecond(RelationshipType::CALLS, DesignEntity::PROCEDURE, procedureTokenObjectThree) == callsExpectedResultTwo);
	REQUIRE(qpsClient.getRelationshipBySecond(RelationshipType::CALLS_T, DesignEntity::PROCEDURE, procedureTokenObjectThree) == callsTExpectedResultTwo);


	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultUsesAll{ { assign_value_one, std::unordered_set<std::string>({variable_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultModifiesAll{ { assign_value_one, std::unordered_set<std::string>({variable_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultParentAll{ { while_value_one, std::unordered_set<std::string>({read_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultParentTAll{ { while_value_one, std::unordered_set<std::string>({read_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultFollowsAll{ { read_value_one, std::unordered_set<std::string>({print_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultFollowsTAll{ { read_value_one, std::unordered_set<std::string>({print_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultNextAll{ { read_value_one, std::unordered_set<std::string>({print_value_one}) } };
	//std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultNextTAll{ { read_value_one, std::unordered_set<std::string>({print_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultCallsAll{
										{ procedure_value_one, std::unordered_set<std::string>({procedure_value_two, procedure_value_three})},
										{ procedure_value_two, std::unordered_set<std::string>({procedure_value_three})}, };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultCallsTAll{
									{ procedure_value_one, std::unordered_set<std::string>({procedure_value_two, procedure_value_three})},
									{ procedure_value_two, std::unordered_set<std::string>({procedure_value_three})}, };

	REQUIRE(qpsClient.getAllRelationship(RelationshipType::USES, DesignEntity::ASSIGN, DesignEntity::VARIABLE) == expectedResultUsesAll);
	REQUIRE(qpsClient.getAllRelationship(RelationshipType::MODIFIES, DesignEntity::ASSIGN, DesignEntity::VARIABLE) == expectedResultModifiesAll);
	REQUIRE(qpsClient.getAllRelationship(RelationshipType::PARENT, DesignEntity::WHILE, DesignEntity::READ) == expectedResultParentAll);
	REQUIRE(qpsClient.getAllRelationship(RelationshipType::PARENT_T, DesignEntity::WHILE, DesignEntity::READ) == expectedResultParentTAll);
	REQUIRE(qpsClient.getAllRelationship(RelationshipType::FOLLOWS, DesignEntity::READ, DesignEntity::PRINT) == expectedResultFollowsAll);
	REQUIRE(qpsClient.getAllRelationship(RelationshipType::FOLLOWS_T, DesignEntity::READ, DesignEntity::PRINT) == expectedResultFollowsTAll);
	REQUIRE(qpsClient.getAllRelationship(RelationshipType::NEXT, DesignEntity::READ, DesignEntity::PRINT) == expectedResultNextAll);
	//REQUIRE(qpsClient.getAllRelationship(RelationshipType::NEXT_T, DesignEntity::READ, DesignEntity::PRINT) == expectedResultNextTAll);
	REQUIRE(qpsClient.getAllRelationship(RelationshipType::CALLS, DesignEntity::PROCEDURE, DesignEntity::PROCEDURE) == expectedResultCallsAll);
	REQUIRE(qpsClient.getAllRelationship(RelationshipType::CALLS_T, DesignEntity::PROCEDURE, DesignEntity::PROCEDURE) == expectedResultCallsTAll);
}
