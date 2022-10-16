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

#include <iostream>
#include <catch.hpp>

PKB* pkb = new PKB();


TEST_CASE("SP Client test") {
	SPClient spClient = SPClient(pkb);

	REQUIRE(spClient.storeConstant(constantEntity));

	//Pattern
	//ASSIGN
	REQUIRE(spClient.storePattern(assignPatternOne));
	REQUIRE(spClient.storePattern(assignPatternTwo));
	REQUIRE(spClient.storePattern(assignPatternThree));
	REQUIRE(spClient.storePattern(assignPatternFour));
	REQUIRE(spClient.storePattern(assignPatternFive));
	REQUIRE(spClient.storePattern(assignPatternSix));
	REQUIRE(spClient.storePattern(assignPatternSeven));
	REQUIRE(spClient.storePattern(assignPatternEight));

	//IF
	REQUIRE(spClient.storePattern(ifPatternOne));
	REQUIRE(spClient.storePattern(ifPatternOneDup));
	REQUIRE(spClient.storePattern(ifPatternTwo));

	//WHILE
	REQUIRE(spClient.storePattern(whilePatternOne));
	REQUIRE(spClient.storePattern(whilePatternOneDup));
	REQUIRE(spClient.storePattern(whilePatternTwo));

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

	REQUIRE(spClient.storeRelationship(nextRelationshipAssignCallOne));
	REQUIRE(spClient.storeRelationship(nextRelationshipCallIfOne));
	REQUIRE(spClient.storeRelationship(nextRelationshipIfPrintOne));
	REQUIRE(spClient.storeRelationship(nextRelationshipPrintReadOne));
	REQUIRE(spClient.storeRelationship(nextRelationshipReadWhileOne));

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

	std::string callMappingResult = procedure_value_one;
	std::string printMappingResult = variable_value_one;
	std::string readMappingResult = variable_value_one;

	std::string callMappingTest = qpsClient.getStatementMapping(call_value_one, DesignEntity::CALL);
	std::string printMappingTest = qpsClient.getStatementMapping(print_value_one, DesignEntity::PRINT);
	std::string readMappingTest = qpsClient.getStatementMapping(read_value_one, DesignEntity::READ);

	REQUIRE(callMappingTest == callMappingResult);
	REQUIRE(printMappingTest == printMappingResult);
	REQUIRE(readMappingTest == readMappingResult);

	std::unordered_set<std::string> callGetStmtByNameTest = qpsClient.getStatementByName(procedure_value_one, DesignEntity::CALL);
	std::unordered_set<std::string> printGetStmtByNameTest = qpsClient.getStatementByName(variable_value_one, DesignEntity::PRINT);
	std::unordered_set<std::string> readGetStmtByNameTest = qpsClient.getStatementByName(variable_value_one, DesignEntity::READ);

	std::unordered_set<std::string> callGetStmtByNameExpectedResult({ call_value_one });
	std::unordered_set<std::string> printGetStmtByNameExpectedResult({ print_value_one });
	std::unordered_set<std::string> readGetStmtByNameExpectedResult({ read_value_one });

	REQUIRE(callGetStmtByNameTest == callGetStmtByNameExpectedResult);
	REQUIRE(printGetStmtByNameTest == printGetStmtByNameExpectedResult);
	REQUIRE(readGetStmtByNameTest == readGetStmtByNameExpectedResult);

	std::unordered_set<std::string> callGetAllNameTest = qpsClient.getAllName(DesignEntity::CALL);
	std::unordered_set<std::string> printGetAllNameTest = qpsClient.getAllName(DesignEntity::PRINT);
	std::unordered_set<std::string> readGetAllNameTest = qpsClient.getAllName(DesignEntity::READ);

	std::unordered_set<std::string> callGetAllNameExpectedResult({ procedure_value_one });
	std::unordered_set<std::string> printGetAllNameExpectedResult({ variable_value_one });
	std::unordered_set<std::string> readGetAllNameExpectedResult({ variable_value_one });

	REQUIRE(callGetAllNameTest == callGetAllNameExpectedResult);
	REQUIRE(printGetAllNameTest == printGetAllNameExpectedResult);
	REQUIRE(readGetAllNameTest == readGetAllNameExpectedResult);

	//Pattern
	//ASSIGN
	std::unordered_set<std::string> assignGetPatternNameNameOne = qpsClient.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSecondOne);
	std::unordered_set<std::string> assignGetPatternNameNameTwo = qpsClient.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, assignPatternTokenObjectSecondTwo);
	std::unordered_set<std::string> assignGetPatternNameSubexprOne = qpsClient.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSubexprOne);
	std::unordered_set<std::string> assignGetPatternNameSubexprTwo = qpsClient.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, assignPatternTokenObjectSubexprTwo);
	std::unordered_set<std::string> assignGetPatternNameSubexprThree = qpsClient.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSubexprThree);
	std::unordered_set<std::string> assignGetPatternNameWildcardOne = qpsClient.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, wildCardTokenObject);
	std::unordered_set<std::string> assignGetPatternNameWildcardTwo = qpsClient.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, wildCardTokenObject);

	//IF
	std::unordered_set<std::string> ifGetPatternNameNameOne = qpsClient.getContainerPattern(DesignEntity::IF, ifPatternTokenObjectFirstOne);
	std::unordered_set<std::string> ifGetPatternNameNameTwo = qpsClient.getContainerPattern(DesignEntity::IF, ifPatternTokenObjectFirstTwo);

	//WHILE
	std::unordered_set<std::string> whileGetPatternNameNameOne = qpsClient.getContainerPattern(DesignEntity::WHILE, whilePatternTokenObjectFirstOne);
	std::unordered_set<std::string> whileGetPatternNameNameTwo = qpsClient.getContainerPattern(DesignEntity::WHILE, whilePatternTokenObjectFirstTwo);

	//ASSIGN
	std::unordered_set<std::string> expectedGetPatternNameNameOne({ assignLineNumOne, assignLineNumEight });
	std::unordered_set<std::string> expectedGetPatternNameNameTwo({ assignLineNumSix });
	std::unordered_set<std::string> expectedGetPatternNameSubexprOne({ assignLineNumFive });
	std::unordered_set<std::string> expectedGetPatternNameSubexprTwo({ assignLineNumTwo, assignLineNumSix });
	std::unordered_set<std::string> expectedGetPatternNameSubexprThree({ assignLineNumOne, assignLineNumFive, assignLineNumEight });
	std::unordered_set<std::string> expectedGetPatternNameWildcardOne({ assignLineNumOne, assignLineNumFive, assignLineNumEight });
	std::unordered_set<std::string> expectedGetPatternNameWilcardTwo({ assignLineNumTwo, assignLineNumSix });

	//IF
	std::unordered_set<std::string> expectedResultIfGetPatternOne({ ifLineNumOne });
	std::unordered_set<std::string> expectedResultIfGetPatternTwo({ ifLineNumOne, ifLineNumTwo });

	//WHILE
	std::unordered_set<std::string> expectedResultWhileGetPatternOne({ whileLineNumOne });
	std::unordered_set<std::string> expectedResultWhileGetPatternTwo({ whileLineNumOne, whileLineNumTwo });

	REQUIRE(assignGetPatternNameNameOne == expectedGetPatternNameNameOne);
	REQUIRE(assignGetPatternNameNameOne == expectedGetPatternNameNameOne);
	REQUIRE(assignGetPatternNameNameTwo == expectedGetPatternNameNameTwo);
	REQUIRE(assignGetPatternNameSubexprOne == expectedGetPatternNameSubexprOne);
	REQUIRE(assignGetPatternNameSubexprTwo == expectedGetPatternNameSubexprTwo);
	REQUIRE(assignGetPatternNameSubexprThree == expectedGetPatternNameSubexprThree);
	REQUIRE(assignGetPatternNameWildcardOne == expectedGetPatternNameWildcardOne);
	REQUIRE(assignGetPatternNameWildcardTwo == expectedGetPatternNameWilcardTwo);

	//IF
	REQUIRE(ifGetPatternNameNameOne == expectedResultIfGetPatternOne);
	REQUIRE(ifGetPatternNameNameTwo == expectedResultIfGetPatternTwo);

	//WHILE
	REQUIRE(whileGetPatternNameNameOne == expectedResultWhileGetPatternOne);
	REQUIRE(whileGetPatternNameNameTwo == expectedResultWhileGetPatternTwo);

	//ASSIGN
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameNameOne = qpsClient.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSecondOne);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameNameTwo = qpsClient.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSecondTwo);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprOne = qpsClient.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprOne);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprTwo = qpsClient.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprTwo);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprThree = qpsClient.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprThree);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameWildcard = qpsClient.getPatternPair(DesignEntity::ASSIGN, wildCardTokenObject);

	//IF
	std::vector<std::pair<std::string, std::string>> ifGetPatternPairNameNameOne = qpsClient.getContainerPatternPair(DesignEntity::IF);
	std::vector<std::pair<std::string, std::string>> ifGetPatternPairNameNameTwo = qpsClient.getContainerPatternPair(DesignEntity::IF);

	//WHILE
	std::vector<std::pair<std::string, std::string>> whileGetPatternPairNameNameOne = qpsClient.getContainerPatternPair(DesignEntity::WHILE);
	std::vector<std::pair<std::string, std::string>> whileGetPatternPairNameNameTwo = qpsClient.getContainerPatternPair(DesignEntity::WHILE);

	//ASSIGN
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
	//IF
	std::vector<std::pair<std::string, std::string>> ifExpectedGetPatternPairNameNameOne{ { ifLineNumOne, ifFirstValueOne },
																							{ ifLineNumTwo, ifFirstValueTwo},
																							{ ifLineNumOne, ifFirstValueTwo} };

	std::vector<std::pair<std::string, std::string>> ifExpectedGetPatternPairNameNameTwo{ { ifLineNumOne, ifFirstValueOne },
																							{ ifLineNumTwo, ifFirstValueTwo},
																							{ ifLineNumOne, ifFirstValueTwo} };

	//WHILE
	std::vector<std::pair<std::string, std::string>> whileExpectedGetPatternPairNameNameOne{ { whileLineNumOne, whileFirstValueOne },
																							{ whileLineNumTwo, whileFirstValueTwo},
																							{ whileLineNumOne, whileFirstValueTwo} };

	std::vector<std::pair<std::string, std::string>> whileExpectedGetPatternPairNameNameTwo{ { whileLineNumOne, whileFirstValueOne },
																							{ whileLineNumTwo, whileFirstValueTwo},
																							{ whileLineNumOne, whileFirstValueTwo} };

	sort(assignGetPatternPairNameNameOne.begin(), assignGetPatternPairNameNameOne.end());
	sort(assignGetPatternPairNameNameTwo.begin(), assignGetPatternPairNameNameTwo.end());
	sort(assignGetPatternPairNameSubexprOne.begin(), assignGetPatternPairNameSubexprOne.end());
	sort(assignGetPatternPairNameSubexprTwo.begin(), assignGetPatternPairNameSubexprTwo.end());
	sort(assignGetPatternPairNameSubexprThree.begin(), assignGetPatternPairNameSubexprThree.end());
	sort(assignGetPatternPairNameWildcard.begin(), assignGetPatternPairNameWildcard.end());

	sort(ifGetPatternPairNameNameOne.begin(), ifGetPatternPairNameNameOne.end());
	sort(ifGetPatternPairNameNameTwo.begin(), ifGetPatternPairNameNameTwo.end());
	sort(ifExpectedGetPatternPairNameNameOne.begin(), ifExpectedGetPatternPairNameNameOne.end());
	sort(ifExpectedGetPatternPairNameNameTwo.begin(), ifExpectedGetPatternPairNameNameTwo.end());

	sort(whileGetPatternPairNameNameOne.begin(), whileGetPatternPairNameNameOne.end());
	sort(whileGetPatternPairNameNameTwo.begin(), whileGetPatternPairNameNameTwo.end());
	sort(whileExpectedGetPatternPairNameNameOne.begin(), whileExpectedGetPatternPairNameNameOne.end());
	sort(whileExpectedGetPatternPairNameNameTwo.begin(), whileExpectedGetPatternPairNameNameTwo.end());

	//ASSIGN
	REQUIRE(assignGetPatternPairNameNameOne == expectedGetPatternPairNameNameOne);
	REQUIRE(assignGetPatternPairNameNameTwo == expectedGetPatternPairNameNameTwo);
	REQUIRE(assignGetPatternPairNameSubexprOne == expectedGetPatternPairNameSubexprOne);
	REQUIRE(assignGetPatternPairNameSubexprTwo == expectedGetPatternPairNameSubexprTwo);
	REQUIRE(assignGetPatternPairNameSubexprThree == expectedGetPatternPairNameSubexprThree);
	REQUIRE(assignGetPatternPairNameWildcard == expectedGetPatternPairNameWilcard);

	REQUIRE(ifGetPatternPairNameNameOne == ifExpectedGetPatternPairNameNameOne);
	REQUIRE(ifGetPatternPairNameNameTwo == ifExpectedGetPatternPairNameNameTwo);

	//WHILE
	REQUIRE(whileGetPatternPairNameNameOne == whileExpectedGetPatternPairNameNameOne);
	REQUIRE(whileGetPatternPairNameNameTwo == whileExpectedGetPatternPairNameNameTwo);

	//Relationship
	REQUIRE(qpsClient.getRelationship(RelationshipType::USES, stmtTokenObject1, variableTokenObject));
	REQUIRE(qpsClient.getRelationship(RelationshipType::MODIFIES, stmtTokenObject1, variableTokenObject));
	REQUIRE(qpsClient.getRelationship(RelationshipType::PARENT, stmtTokenObject6, stmtTokenObject5));
	REQUIRE(qpsClient.getRelationship(RelationshipType::PARENT_T, stmtTokenObject6, stmtTokenObject5));
	REQUIRE(qpsClient.getRelationship(RelationshipType::FOLLOWS, stmtTokenObject5, stmtTokenObject4));
	REQUIRE(qpsClient.getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject5, stmtTokenObject4));
	REQUIRE(qpsClient.getRelationship(RelationshipType::NEXT, stmtTokenObject1, stmtTokenObject2));
	REQUIRE(qpsClient.getRelationship(RelationshipType::NEXT_T, stmtTokenObject1, stmtTokenObject2));
	REQUIRE(qpsClient.getRelationship(RelationshipType::CALLS, procedureTokenObject, procedureTokenObjectTwo));
	REQUIRE(qpsClient.getRelationship(RelationshipType::CALLS_T, procedureTokenObject, procedureTokenObjectTwo));

	std::unordered_set<std::string> usesExpectedResult({ variable_value_one });
	std::unordered_set<std::string> modifiesExpectedResult({ variable_value_one });
	std::unordered_set<std::string> parentExpectedResult({ read_value_one });
	std::unordered_set<std::string> parentTExpectedResult({ read_value_one });
	std::unordered_set<std::string> followsExpectedResult({ print_value_one });
	std::unordered_set<std::string> followsTExpectedResult({ print_value_one });
	std::unordered_set<std::string> nextExpectedResult({ while_value_one });
	std::unordered_set<std::string> nextTExpectedResult({ while_value_one });
	std::unordered_set<std::string> callsExpectedResult{ procedure_value_two, procedure_value_three };
	std::unordered_set<std::string> callsTExpectedResult{ procedure_value_two, procedure_value_three };

	REQUIRE(qpsClient.getRelationshipByFirst(RelationshipType::USES, stmtTokenObject1, DesignEntity::VARIABLE) == usesExpectedResult);
	REQUIRE(qpsClient.getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject1, DesignEntity::VARIABLE) == modifiesExpectedResult);
	REQUIRE(qpsClient.getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject6, DesignEntity::READ) == parentExpectedResult);
	REQUIRE(qpsClient.getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject6, DesignEntity::READ) == parentTExpectedResult);
	REQUIRE(qpsClient.getRelationshipByFirst(RelationshipType::FOLLOWS, stmtTokenObject5, DesignEntity::PRINT) == followsExpectedResult);
	REQUIRE(qpsClient.getRelationshipByFirst(RelationshipType::FOLLOWS_T, stmtTokenObject5, DesignEntity::PRINT) == followsTExpectedResult);
	REQUIRE(qpsClient.getRelationshipByFirst(RelationshipType::NEXT, stmtTokenObject5, DesignEntity::WHILE) == nextExpectedResult);
	REQUIRE(qpsClient.getRelationshipByFirst(RelationshipType::NEXT_T, stmtTokenObject5, DesignEntity::WHILE) == nextTExpectedResult);
	REQUIRE(qpsClient.getRelationshipByFirst(RelationshipType::CALLS, procedureTokenObject, DesignEntity::PROCEDURE) == callsExpectedResult);
	REQUIRE(qpsClient.getRelationshipByFirst(RelationshipType::CALLS_T, procedureTokenObject, DesignEntity::PROCEDURE) == callsTExpectedResult);


	std::unordered_set<std::string> usesExpectedResultTwo({ assign_value_one });
	std::unordered_set<std::string> modifiesExpectedResultTwo({ assign_value_one });
	std::unordered_set<std::string> parentExpectedResultTwo({ while_value_one });
	std::unordered_set<std::string> parentTExpectedResultTwo({ while_value_one });
	std::unordered_set<std::string> followsExpectedResultTwo({ read_value_one });
	std::unordered_set<std::string> followsTExpectedResultTwo({ read_value_one });
	std::unordered_set<std::string> nextExpectedResultTwo({ if_value_one });
	std::unordered_set<std::string> nextTExpectedResultTwo({ call_value_one });
	std::unordered_set<std::string> callsExpectedResultTwo{ procedure_value_one, procedure_value_two };
	std::unordered_set<std::string> callsTExpectedResultTwo{ procedure_value_one, procedure_value_two };

	REQUIRE(qpsClient.getRelationshipBySecond(RelationshipType::USES, DesignEntity::ASSIGN, variableTokenObject) == usesExpectedResultTwo);
	REQUIRE(qpsClient.getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::ASSIGN, variableTokenObject) == modifiesExpectedResultTwo);
	REQUIRE(qpsClient.getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::WHILE, stmtTokenObject5) == parentExpectedResultTwo);
	REQUIRE(qpsClient.getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::WHILE, stmtTokenObject5) == parentTExpectedResultTwo);
	REQUIRE(qpsClient.getRelationshipBySecond(RelationshipType::FOLLOWS, DesignEntity::READ, stmtTokenObject4) == followsExpectedResultTwo);
	REQUIRE(qpsClient.getRelationshipBySecond(RelationshipType::FOLLOWS_T, DesignEntity::READ, stmtTokenObject4) == followsTExpectedResultTwo);
	REQUIRE(qpsClient.getRelationshipBySecond(RelationshipType::NEXT, DesignEntity::IF, stmtTokenObject4) == nextExpectedResultTwo);
	REQUIRE(qpsClient.getRelationshipBySecond(RelationshipType::NEXT_T, DesignEntity::CALL, stmtTokenObject4) == nextTExpectedResultTwo);
	REQUIRE(qpsClient.getRelationshipBySecond(RelationshipType::CALLS, DesignEntity::PROCEDURE, procedureTokenObjectThree) == callsExpectedResultTwo);
	REQUIRE(qpsClient.getRelationshipBySecond(RelationshipType::CALLS_T, DesignEntity::PROCEDURE, procedureTokenObjectThree) == callsTExpectedResultTwo);


	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultUsesAll{ { assign_value_one, std::unordered_set<std::string>({variable_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultModifiesAll{ { assign_value_one, std::unordered_set<std::string>({variable_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultParentAll{ { while_value_one, std::unordered_set<std::string>({read_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultParentTAll{ { while_value_one, std::unordered_set<std::string>({read_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultFollowsAll{ { read_value_one, std::unordered_set<std::string>({print_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultFollowsTAll{ { read_value_one, std::unordered_set<std::string>({print_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultNextAll{ { print_value_one, std::unordered_set<std::string>({read_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultNextTAll{ { print_value_one, std::unordered_set<std::string>({read_value_one}) } };
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
	REQUIRE(qpsClient.getAllRelationship(RelationshipType::NEXT, DesignEntity::PRINT, DesignEntity::READ) == expectedResultNextAll);
	REQUIRE(qpsClient.getAllRelationship(RelationshipType::NEXT_T, DesignEntity::PRINT, DesignEntity::READ) == expectedResultNextTAll);
	REQUIRE(qpsClient.getAllRelationship(RelationshipType::CALLS, DesignEntity::PROCEDURE, DesignEntity::PROCEDURE) == expectedResultCallsAll);
	REQUIRE(qpsClient.getAllRelationship(RelationshipType::CALLS_T, DesignEntity::PROCEDURE, DesignEntity::PROCEDURE) == expectedResultCallsTAll);
}
