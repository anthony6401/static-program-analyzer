#include "models/Entity/AssignEntity.h"
#include "models/Entity/DesignEntity.h"
#include "models/Entity/VariableEntity.h"
#include "models/Relationship/Relationship.h"
#include "models/Relationship/UsesRelationship.h"


#include "components/pkb/pkb.h"
#include "components/pkb/manager/EntityManager.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"

#include "./EntityObject.h"
#include "./PatternObject.h"
#include "./ReuseableTokenObject.h"
#include "./RelationshipObject.h"

#include <catch.hpp>


static Relationship* usesRel = new UsesRelationship(assignEntity, variableEntity);

TEST_CASE("PKB Entity Managertest") {
	PKB pkb = PKB();

	//Currenty one test is sufficient
	REQUIRE(pkb.storeRelationship(usesRel));
	REQUIRE(pkb.storeRelationship(followsRelationshipReadCallOne));
	REQUIRE(pkb.storeConstant(constantEntity));

	std::unordered_set<std::string> ass_set = {assign_value_one};
	std::unordered_set<std::string> var_set = {variable_value_one};
	std::unordered_set<std::string> const_set = {constant_value_one};
	std::unordered_set<std::string> read_set = { read_value_one };
	std::unordered_set<std::string> call_set = { call_value_one };

	REQUIRE(pkb.getAllEntity(DesignEntity::ASSIGN) == ass_set);
	REQUIRE(pkb.getAllEntity(DesignEntity::VARIABLE) == var_set);
	REQUIRE(pkb.getAllEntity(DesignEntity::CONSTANT) == const_set);
	REQUIRE(pkb.getAllEntity(DesignEntity::READ) == read_set);
	REQUIRE(pkb.getAllEntity(DesignEntity::CALL) == call_set);

	std::string callMappingResult = procedure_value_one;
	std::string readMappingResult = variable_value_one;

	std::string callMappingTest = pkb.getStatementMapping(call_value_one, DesignEntity::CALL);
	std::string readMappingTest = pkb.getStatementMapping(read_value_one, DesignEntity::READ);

	REQUIRE(callMappingTest == callMappingResult);
	REQUIRE(readMappingTest == readMappingResult);

	std::unordered_set<std::string> callGetStmtByNameTest = pkb.getStatementByName(procedure_value_one, DesignEntity::CALL);
	std::unordered_set<std::string> readGetStmtByNameTest = pkb.getStatementByName(variable_value_one, DesignEntity::READ);

	std::unordered_set<std::string> callGetStmtByNameExpectedResult({ call_value_one });
	std::unordered_set<std::string> readGetStmtByNameExpectedResult({ read_value_one });

	REQUIRE(callGetStmtByNameTest == callGetStmtByNameExpectedResult);
	REQUIRE(readGetStmtByNameTest == readGetStmtByNameExpectedResult);

	std::unordered_set<std::string> callGetAllNameTest = pkb.getAllName(DesignEntity::CALL);
	std::unordered_set<std::string> readGetAllNameTest = pkb.getAllName(DesignEntity::READ);

	std::unordered_set<std::string> callGetAllNameExpectedResult({ procedure_value_one });
	std::unordered_set<std::string> readGetAllNameExpectedResult({ variable_value_one });

	REQUIRE(callGetAllNameTest == callGetAllNameExpectedResult);
	REQUIRE(readGetAllNameTest == readGetAllNameExpectedResult);
}

TEST_CASE("PKB Pattern Manager test") {
	PKB pkb = PKB();

	//ASSIGN
	REQUIRE(pkb.storePattern(assignPatternOne));
	REQUIRE(pkb.storePattern(assignPatternTwo));
	REQUIRE(pkb.storePattern(assignPatternThree));
	REQUIRE(pkb.storePattern(assignPatternFour));
	REQUIRE(pkb.storePattern(assignPatternFive));
	REQUIRE(pkb.storePattern(assignPatternSix));
	REQUIRE(pkb.storePattern(assignPatternSeven));
	REQUIRE(pkb.storePattern(assignPatternEight));

	//IF
	REQUIRE(pkb.storePattern(ifPatternOne));
	REQUIRE(pkb.storePattern(ifPatternOneDup));
	REQUIRE(pkb.storePattern(ifPatternTwo));

	//WHILE
	REQUIRE(pkb.storePattern(whilePatternOne));
	REQUIRE(pkb.storePattern(whilePatternOneDup));
	REQUIRE(pkb.storePattern(whilePatternTwo));

	//ASSIGN
	std::unordered_set<std::string> assignGetPatternNameNameOne = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSecondOne);
	std::unordered_set<std::string> assignGetPatternNameNameTwo = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, assignPatternTokenObjectSecondTwo);
	std::unordered_set<std::string> assignGetPatternNameSubexprOne = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSubexprOne);
	std::unordered_set<std::string> assignGetPatternNameSubexprTwo = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, assignPatternTokenObjectSubexprTwo);
	std::unordered_set<std::string> assignGetPatternNameSubexprThree = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSubexprThree);
	std::unordered_set<std::string> assignGetPatternNameWildcardOne = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, wildCardTokenObject);
	std::unordered_set<std::string> assignGetPatternNameWildcardTwo = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, wildCardTokenObject);

	//IF
	std::unordered_set<std::string> ifGetPatternNameNameOne = pkb.getPattern(DesignEntity::IF, ifPatternTokenObjectFirstOne, TokenObject());
	std::unordered_set<std::string> ifGetPatternNameNameTwo = pkb.getPattern(DesignEntity::IF, ifPatternTokenObjectFirstTwo, TokenObject());

	//WHILE
	std::unordered_set<std::string> whileGetPatternNameNameOne = pkb.getPattern(DesignEntity::WHILE, whilePatternTokenObjectFirstOne, TokenObject());
	std::unordered_set<std::string> whileGetPatternNameNameTwo = pkb.getPattern(DesignEntity::WHILE, whilePatternTokenObjectFirstTwo, TokenObject());

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
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameNameOne = pkb.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSecondOne);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameNameTwo = pkb.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSecondTwo);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprOne = pkb.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprOne);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprTwo = pkb.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprTwo);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprThree = pkb.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprThree);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameWildcard = pkb.getPatternPair(DesignEntity::ASSIGN, wildCardTokenObject);

	//IF
	std::vector<std::pair<std::string, std::string>> ifGetPatternPairNameNameOne = pkb.getPatternPair(DesignEntity::IF, ifPatternTokenObjectFirstOne);
	std::vector<std::pair<std::string, std::string>> ifGetPatternPairNameNameTwo = pkb.getPatternPair(DesignEntity::IF, ifPatternTokenObjectFirstTwo);

	//WHILE
	std::vector<std::pair<std::string, std::string>> whileGetPatternPairNameNameOne = pkb.getPatternPair(DesignEntity::WHILE, whilePatternTokenObjectFirstOne);
	std::vector<std::pair<std::string, std::string>> whileGetPatternPairNameNameTwo = pkb.getPatternPair(DesignEntity::WHILE, whilePatternTokenObjectFirstTwo);

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

	//IF
	REQUIRE(ifGetPatternPairNameNameOne == ifExpectedGetPatternPairNameNameOne);
	REQUIRE(ifGetPatternPairNameNameTwo == ifExpectedGetPatternPairNameNameTwo);

	//WHILE
	REQUIRE(whileGetPatternPairNameNameOne == whileExpectedGetPatternPairNameNameOne);
	REQUIRE(whileGetPatternPairNameNameTwo == whileExpectedGetPatternPairNameNameTwo);
}

TEST_CASE("PKB Relationship Manager test") {
	PKB pkb = PKB();

	REQUIRE(pkb.storeRelationship(usesRelationshipAssignOne));
	REQUIRE(pkb.storeRelationship(usesRelationshipProcOne));
	REQUIRE(pkb.storeRelationship(usesRelationshipPrintOne));
	REQUIRE(pkb.storeRelationship(usesRelationshipWhileOne));
	REQUIRE(pkb.storeRelationship(usesRelationshipIfOne));


	REQUIRE(pkb.storeRelationship(modifyRelationshipAssignOne));
	REQUIRE(pkb.storeRelationship(modifyRelationshipProcOne));
	REQUIRE(pkb.storeRelationship(modifyRelationshipReadOne));
	REQUIRE(pkb.storeRelationship(modifyRelationshipWhileOne));


	REQUIRE(pkb.storeRelationship(parentRelationshipWhileReadOne));
	REQUIRE(pkb.storeRelationship(parentRelationshipWhilePrintOne));
	REQUIRE(pkb.storeRelationship(parentRelationshipIfAssignOne));
	REQUIRE(pkb.storeRelationship(parentRelationshipIfCallOne));

	REQUIRE(pkb.storeRelationship(parentTRelationshipWhileReadOne));
	REQUIRE(pkb.storeRelationship(parentTRelationshipWhilePrintOne));
	REQUIRE(pkb.storeRelationship(parentTRelationshipIfAssignOne));
	REQUIRE(pkb.storeRelationship(parentTRelationshipIfCallOne));

	REQUIRE(pkb.storeRelationship(followsRelationshipReadPrintOne));
	REQUIRE(pkb.storeRelationship(followsRelationshipPrintAssignOne));
	REQUIRE(pkb.storeRelationship(followsRelationshipAssignCallOne));
	REQUIRE(pkb.storeRelationship(followsRelationshipCallWhileOne));
	REQUIRE(pkb.storeRelationship(followsRelationshipWhileIfOne));
	REQUIRE(pkb.storeRelationship(followsRelationshipIfReadOne));

	REQUIRE(pkb.storeRelationship(followsTRelationshipReadPrintOne));
	REQUIRE(pkb.storeRelationship(followsTRelationshipPrintAssignOne));
	REQUIRE(pkb.storeRelationship(followsTRelationshipAssignCallOne));
	REQUIRE(pkb.storeRelationship(followsTRelationshipCallWhileOne));
	REQUIRE(pkb.storeRelationship(followsTRelationshipWhileIfOne));
	REQUIRE(pkb.storeRelationship(followsTRelationshipIfReadOne));

	REQUIRE(pkb.storeRelationship(nextRelationshipAssignCallOne));
	REQUIRE(pkb.storeRelationship(nextRelationshipCallIfOne));
	REQUIRE(pkb.storeRelationship(nextRelationshipIfPrintOne));
	REQUIRE(pkb.storeRelationship(nextRelationshipPrintReadOne));
	REQUIRE(pkb.storeRelationship(nextRelationshipReadWhileOne));

	REQUIRE(pkb.storeRelationship(callsRelationshipOne));
	REQUIRE(pkb.storeRelationship(callsRelationshipTwo));
	REQUIRE(pkb.storeRelationship(callsRelationshipThree));

	REQUIRE(pkb.storeRelationship(callsTRelationshipOne));
	REQUIRE(pkb.storeRelationship(callsTRelationshipTwo));
	REQUIRE(pkb.storeRelationship(callsTRelationshipThree));

	REQUIRE(pkb.getRelationship(RelationshipType::USES, stmtTokenObject1, variableTokenObject));
	REQUIRE(pkb.getRelationship(RelationshipType::MODIFIES, stmtTokenObject1, variableTokenObject));
	REQUIRE(pkb.getRelationship(RelationshipType::PARENT, stmtTokenObject6, stmtTokenObject5));
	REQUIRE(pkb.getRelationship(RelationshipType::PARENT_T, stmtTokenObject6, stmtTokenObject5));
	REQUIRE(pkb.getRelationship(RelationshipType::FOLLOWS, stmtTokenObject5, stmtTokenObject4));
	REQUIRE(pkb.getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject5, stmtTokenObject4));
	REQUIRE(pkb.getRelationship(RelationshipType::NEXT, stmtTokenObject1, stmtTokenObject2));
	REQUIRE(pkb.getRelationship(RelationshipType::NEXT_T, stmtTokenObject1, stmtTokenObject2));
	REQUIRE(pkb.getRelationship(RelationshipType::CALLS, procedureTokenObject, procedureTokenObjectTwo));
	REQUIRE(pkb.getRelationship(RelationshipType::CALLS_T, procedureTokenObject, procedureTokenObjectTwo));


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


	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::USES, stmtTokenObject1, DesignEntity::VARIABLE) == usesExpectedResult);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject1, DesignEntity::VARIABLE) == modifiesExpectedResult);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject6, DesignEntity::READ) == parentExpectedResult);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject6, DesignEntity::READ) == parentTExpectedResult);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::FOLLOWS, stmtTokenObject5, DesignEntity::PRINT) == followsExpectedResult);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::FOLLOWS_T, stmtTokenObject5, DesignEntity::PRINT) == followsTExpectedResult);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::NEXT, stmtTokenObject5, DesignEntity::WHILE) == nextExpectedResult);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::NEXT_T, stmtTokenObject5, DesignEntity::WHILE) == nextTExpectedResult);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::CALLS, procedureTokenObject, DesignEntity::PROCEDURE) == callsExpectedResult);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::CALLS_T, procedureTokenObject, DesignEntity::PROCEDURE) == callsTExpectedResult);



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

	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::USES, DesignEntity::ASSIGN, variableTokenObject) == usesExpectedResultTwo);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::ASSIGN, variableTokenObject) == modifiesExpectedResultTwo);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::WHILE, stmtTokenObject5) == parentExpectedResultTwo);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::WHILE, stmtTokenObject5) == parentTExpectedResultTwo);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::FOLLOWS, DesignEntity::READ, stmtTokenObject4) == followsExpectedResultTwo);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::FOLLOWS_T, DesignEntity::READ, stmtTokenObject4) == followsTExpectedResultTwo);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::NEXT, DesignEntity::IF, stmtTokenObject4) == nextExpectedResultTwo);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::NEXT_T, DesignEntity::CALL, stmtTokenObject4) == nextTExpectedResultTwo);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::CALLS, DesignEntity::PROCEDURE, procedureTokenObjectThree) == callsExpectedResultTwo);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::CALLS_T, DesignEntity::PROCEDURE, procedureTokenObjectThree) == callsTExpectedResultTwo);


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

	REQUIRE(pkb.getAllRelationship(RelationshipType::USES, DesignEntity::ASSIGN, DesignEntity::VARIABLE) == expectedResultUsesAll);
	REQUIRE(pkb.getAllRelationship(RelationshipType::MODIFIES, DesignEntity::ASSIGN, DesignEntity::VARIABLE) == expectedResultModifiesAll);
	REQUIRE(pkb.getAllRelationship(RelationshipType::PARENT, DesignEntity::WHILE, DesignEntity::READ) == expectedResultParentAll);
	REQUIRE(pkb.getAllRelationship(RelationshipType::PARENT_T, DesignEntity::WHILE, DesignEntity::READ) == expectedResultParentTAll);
	REQUIRE(pkb.getAllRelationship(RelationshipType::FOLLOWS, DesignEntity::READ, DesignEntity::PRINT) == expectedResultFollowsAll);
	REQUIRE(pkb.getAllRelationship(RelationshipType::FOLLOWS_T, DesignEntity::READ, DesignEntity::PRINT) == expectedResultFollowsTAll);
	REQUIRE(pkb.getAllRelationship(RelationshipType::NEXT, DesignEntity::PRINT, DesignEntity::READ) == expectedResultNextAll);
	REQUIRE(pkb.getAllRelationship(RelationshipType::NEXT_T, DesignEntity::PRINT, DesignEntity::READ) == expectedResultNextTAll);
	REQUIRE(pkb.getAllRelationship(RelationshipType::CALLS, DesignEntity::PROCEDURE, DesignEntity::PROCEDURE) == expectedResultCallsAll);
	REQUIRE(pkb.getAllRelationship(RelationshipType::CALLS_T, DesignEntity::PROCEDURE, DesignEntity::PROCEDURE) == expectedResultCallsTAll);
	

}

//Test for Runtime Evaluator Relationship
TEST_CASE("Runtime Evaluator Relationship Manager Test") {
	PKB pkb = PKB();
	
	// Populate PKB for Next
	REQUIRE(pkb.storeRelationship(nextRelationshipAffectsOne));
	REQUIRE(pkb.storeRelationship(nextRelationshipAffectsTwo));
	REQUIRE(pkb.storeRelationship(nextRelationshipAffectsThree));
	REQUIRE(pkb.storeRelationship(nextRelationshipAffectsFour));
	REQUIRE(pkb.storeRelationship(nextRelationshipAffectsFive));
	REQUIRE(pkb.storeRelationship(nextRelationshipAffectsSix));
	REQUIRE(pkb.storeRelationship(nextRelationshipAffectsSeven));

	// Populate PKB for Modifies
	REQUIRE(pkb.storeRelationship(modifyRelationshipAffectsOne));
	REQUIRE(pkb.storeRelationship(modifyRelationshipAffectsTwo));
	REQUIRE(pkb.storeRelationship(modifyRelationshipAffectsThree));
	REQUIRE(pkb.storeRelationship(modifyRelationshipAffectsFour));
	REQUIRE(pkb.storeRelationship(modifyRelationshipAffectsFive));
	REQUIRE(pkb.storeRelationship(modifyRelationshipAffectsSix));

	// Populate PKB for Uses
	REQUIRE(pkb.storeRelationship(usesRelationshipAffectsOne));
	REQUIRE(pkb.storeRelationship(usesRelationshipAffectsTwo));
	REQUIRE(pkb.storeRelationship(usesRelationshipAffectsThree));
	REQUIRE(pkb.storeRelationship(usesRelationshipAffectsFour));

	// Test for affects(1, 2)
	REQUIRE(pkb.getRelationship(RelationshipType::AFFECTS, stmtTokenObject1, stmtTokenObject5));
	REQUIRE(pkb.getRelationship(RelationshipType::AFFECTS, stmtTokenObject3, stmtTokenObject5));
	REQUIRE(!pkb.getRelationship(RelationshipType::AFFECTS, stmtTokenObject1, stmtTokenObject7));
	REQUIRE(!pkb.getRelationship(RelationshipType::AFFECTS, stmtTokenObject1, stmtTokenObject4));

	std::unordered_set<std::string> a_filter = { stmt1, stmt3, stmt4, stmt5, stmt7 };
	std::unordered_set<std::string> empty = {};

	// Test for Affects(1, a)
	std::unordered_set<std::string> expectedResultByFirst = { stmt5 };
	std::unordered_set<std::string> expectedResultByFirst2 = { stmt7 };


	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::AFFECTS, stmtTokenObject1, DesignEntity::ASSIGN) == expectedResultByFirst);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::AFFECTS, stmtTokenObject2, DesignEntity::ASSIGN) == empty);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::AFFECTS, stmtTokenObject3, DesignEntity::ASSIGN) == expectedResultByFirst);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::AFFECTS, stmtTokenObject4, DesignEntity::ASSIGN) == empty);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::AFFECTS, stmtTokenObject5, DesignEntity::ASSIGN) == expectedResultByFirst2);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::AFFECTS, stmtTokenObject6, DesignEntity::ASSIGN) == empty);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::AFFECTS, stmtTokenObject7, DesignEntity::ASSIGN) == empty);

	// Test for Affects(a, 2)
	std::unordered_set<std::string> expectedResultBySecond = { stmt1, stmt3 };
	std::unordered_set<std::string> expectedResultBySecond2 = { stmt5 };

	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::AFFECTS, DesignEntity::ASSIGN, stmtTokenObject1) == empty);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::AFFECTS, DesignEntity::ASSIGN, stmtTokenObject2) == empty);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::AFFECTS, DesignEntity::ASSIGN, stmtTokenObject3) == empty);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::AFFECTS, DesignEntity::ASSIGN, stmtTokenObject4) == empty);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::AFFECTS, DesignEntity::ASSIGN, stmtTokenObject5) == expectedResultBySecond);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::AFFECTS, DesignEntity::ASSIGN, stmtTokenObject6) == empty);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::AFFECTS, DesignEntity::ASSIGN, stmtTokenObject7) == expectedResultBySecond2);

	// Test for Affects(a1, a2)
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAll{
									{ stmt1, std::unordered_set<std::string>({stmt5})},
									{ stmt3, std::unordered_set<std::string>({stmt5})},
									{ stmt5, std::unordered_set<std::string>({ stmt7 })} };

	std::unordered_set<std::string> if_filter = { stmt2 };

	REQUIRE(pkb.getAllRelationship(RelationshipType::AFFECTS, DesignEntity::ASSIGN, DesignEntity::ASSIGN) == expectedResultAll);

	///// Test For Affects* Relationship

	// Test for affectsT(1, 2)
	REQUIRE(pkb.getRelationship(RelationshipType::AFFECTS_T, stmtTokenObject1, stmtTokenObject5));
	REQUIRE(pkb.getRelationship(RelationshipType::AFFECTS_T, stmtTokenObject3, stmtTokenObject5));
	REQUIRE(pkb.getRelationship(RelationshipType::AFFECTS_T, stmtTokenObject1, stmtTokenObject7));

	REQUIRE(!pkb.getRelationship(RelationshipType::AFFECTS_T, stmtTokenObject1, stmtTokenObject4));

	std::unordered_set<std::string> a_filterT = { stmt1, stmt3, stmt4, stmt5, stmt7 };
	std::unordered_set<std::string> emptyT = {};

	// Test for AffectsT(1, a)
	std::unordered_set<std::string> expectedResultByFirstT = { stmt5, stmt7 };
	std::unordered_set<std::string> expectedResultByFirstT2 = { stmt7 };

	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::AFFECTS_T, stmtTokenObject1, DesignEntity::ASSIGN) == expectedResultByFirstT);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::AFFECTS_T, stmtTokenObject2, DesignEntity::ASSIGN) == emptyT);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::AFFECTS_T, stmtTokenObject3, DesignEntity::ASSIGN) == expectedResultByFirstT);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::AFFECTS_T, stmtTokenObject4, DesignEntity::ASSIGN) == emptyT);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::AFFECTS_T, stmtTokenObject5, DesignEntity::ASSIGN) == expectedResultByFirstT2);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::AFFECTS_T, stmtTokenObject6, DesignEntity::ASSIGN) == emptyT);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::AFFECTS_T, stmtTokenObject7, DesignEntity::ASSIGN) == emptyT);

	// Test for Affects(a, 2)
	std::unordered_set<std::string> expectedResultBySecondT = { stmt1, stmt3 };
	std::unordered_set<std::string> expectedResultBySecondT2 = { stmt1,stmt3, stmt5 };

	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::AFFECTS_T, DesignEntity::ASSIGN, stmtTokenObject1) == emptyT);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::AFFECTS_T, DesignEntity::ASSIGN, stmtTokenObject2) == emptyT);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::AFFECTS_T, DesignEntity::ASSIGN, stmtTokenObject3) == emptyT);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::AFFECTS_T, DesignEntity::ASSIGN, stmtTokenObject4) == emptyT);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::AFFECTS_T, DesignEntity::ASSIGN, stmtTokenObject5) == expectedResultBySecondT);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::AFFECTS_T, DesignEntity::ASSIGN, stmtTokenObject6) == emptyT);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::AFFECTS_T, DesignEntity::ASSIGN, stmtTokenObject7) == expectedResultBySecondT2);

	// Test for AffectsT(a1, a2)
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAllT{
									{ stmt1, std::unordered_set<std::string>({stmt5, stmt7})},
									{ stmt3, std::unordered_set<std::string>({stmt5, stmt7})},
									{ stmt5, std::unordered_set<std::string>({ stmt7 })} };

	std::unordered_set<std::string> if_filterT = { stmt2 };

	REQUIRE(pkb.getAllRelationship(RelationshipType::AFFECTS_T, DesignEntity::ASSIGN, DesignEntity::ASSIGN) == expectedResultAllT);
}

//Integration testing between managers.
TEST_CASE("All Manager Test") {
	PKB pkb = PKB();

	//Pattern
	//ASSIGN
	REQUIRE(pkb.storePattern(assignPatternOne));
	REQUIRE(pkb.storePattern(assignPatternTwo));
	REQUIRE(pkb.storePattern(assignPatternThree));
	REQUIRE(pkb.storePattern(assignPatternFour));
	REQUIRE(pkb.storePattern(assignPatternFive));
	REQUIRE(pkb.storePattern(assignPatternSix));
	REQUIRE(pkb.storePattern(assignPatternSeven));
	REQUIRE(pkb.storePattern(assignPatternEight));
	REQUIRE(pkb.storeConstant(constantEntity));

	//IF
	REQUIRE(pkb.storePattern(ifPatternOne));
	REQUIRE(pkb.storePattern(ifPatternOneDup));
	REQUIRE(pkb.storePattern(ifPatternTwo));

	//WHILE
	REQUIRE(pkb.storePattern(whilePatternOne));
	REQUIRE(pkb.storePattern(whilePatternOneDup));
	REQUIRE(pkb.storePattern(whilePatternTwo));


	//Relationship + Entity
	REQUIRE(pkb.storeRelationship(usesRelationshipAssignOne));
	REQUIRE(pkb.storeRelationship(usesRelationshipProcOne));
	REQUIRE(pkb.storeRelationship(usesRelationshipPrintOne));
	REQUIRE(pkb.storeRelationship(usesRelationshipWhileOne));
	REQUIRE(pkb.storeRelationship(usesRelationshipIfOne));


	REQUIRE(pkb.storeRelationship(modifyRelationshipAssignOne));
	REQUIRE(pkb.storeRelationship(modifyRelationshipProcOne));
	REQUIRE(pkb.storeRelationship(modifyRelationshipReadOne));
	REQUIRE(pkb.storeRelationship(modifyRelationshipWhileOne));


	REQUIRE(pkb.storeRelationship(parentRelationshipWhileReadOne));
	REQUIRE(pkb.storeRelationship(parentRelationshipWhilePrintOne));
	REQUIRE(pkb.storeRelationship(parentRelationshipIfAssignOne));
	REQUIRE(pkb.storeRelationship(parentRelationshipIfCallOne));

	REQUIRE(pkb.storeRelationship(parentTRelationshipWhileReadOne));
	REQUIRE(pkb.storeRelationship(parentTRelationshipWhilePrintOne));
	REQUIRE(pkb.storeRelationship(parentTRelationshipIfAssignOne));
	REQUIRE(pkb.storeRelationship(parentTRelationshipIfCallOne));

	REQUIRE(pkb.storeRelationship(followsRelationshipReadPrintOne));
	REQUIRE(pkb.storeRelationship(followsRelationshipPrintAssignOne));
	REQUIRE(pkb.storeRelationship(followsRelationshipAssignCallOne));
	REQUIRE(pkb.storeRelationship(followsRelationshipCallWhileOne));
	REQUIRE(pkb.storeRelationship(followsRelationshipWhileIfOne));
	REQUIRE(pkb.storeRelationship(followsRelationshipIfReadOne));

	REQUIRE(pkb.storeRelationship(followsTRelationshipReadPrintOne));
	REQUIRE(pkb.storeRelationship(followsTRelationshipPrintAssignOne));
	REQUIRE(pkb.storeRelationship(followsTRelationshipAssignCallOne));
	REQUIRE(pkb.storeRelationship(followsTRelationshipCallWhileOne));
	REQUIRE(pkb.storeRelationship(followsTRelationshipWhileIfOne));
	REQUIRE(pkb.storeRelationship(followsTRelationshipIfReadOne));

	//Entity
	std::unordered_set<std::string> ass_set;
	ass_set.insert(assign_value_one);

	std::unordered_set<std::string> var_set;
	var_set.insert(variable_value_one);

	std::unordered_set<std::string> const_set;
	const_set.insert(constant_value_one);

	REQUIRE(pkb.getAllEntity(DesignEntity::ASSIGN) == ass_set);
	REQUIRE(pkb.getAllEntity(DesignEntity::VARIABLE) == var_set);
	REQUIRE(pkb.getAllEntity(DesignEntity::CONSTANT) == const_set);

	std::string callMappingResult = procedure_value_one;
	std::string printMappingResult = variable_value_one;
	std::string readMappingResult = variable_value_one;

	std::string callMappingTest = pkb.getStatementMapping(call_value_one, DesignEntity::CALL);
	std::string printMappingTest = pkb.getStatementMapping(print_value_one, DesignEntity::PRINT);
	std::string readMappingTest = pkb.getStatementMapping(read_value_one, DesignEntity::READ);

	REQUIRE(callMappingTest == callMappingResult);
	REQUIRE(printMappingTest == printMappingResult);
	REQUIRE(readMappingTest == readMappingResult);

	std::unordered_set<std::string> callGetStmtByNameTest = pkb.getStatementByName(procedure_value_one, DesignEntity::CALL);
	std::unordered_set<std::string> readGetStmtByNameTest = pkb.getStatementByName(variable_value_one, DesignEntity::READ);

	std::unordered_set<std::string> callGetStmtByNameExpectedResult({ call_value_one });
	std::unordered_set<std::string> readGetStmtByNameExpectedResult({ read_value_one });

	REQUIRE(callGetStmtByNameTest == callGetStmtByNameExpectedResult);
	REQUIRE(readGetStmtByNameTest == readGetStmtByNameExpectedResult);

	std::unordered_set<std::string> callGetAllNameTest = pkb.getAllName(DesignEntity::CALL);
	std::unordered_set<std::string> readGetAllNameTest = pkb.getAllName(DesignEntity::READ);

	std::unordered_set<std::string> callGetAllNameExpectedResult({ procedure_value_one });
	std::unordered_set<std::string> readGetAllNameExpectedResult({ variable_value_one });

	REQUIRE(callGetAllNameTest == callGetAllNameExpectedResult);
	REQUIRE(readGetAllNameTest == readGetAllNameExpectedResult);

	//Relationship
	REQUIRE(pkb.getRelationship(RelationshipType::USES, stmtTokenObject1, variableTokenObject));
	REQUIRE(pkb.getRelationship(RelationshipType::MODIFIES, stmtTokenObject1, variableTokenObject));
	REQUIRE(pkb.getRelationship(RelationshipType::PARENT, stmtTokenObject6, stmtTokenObject5));
	REQUIRE(pkb.getRelationship(RelationshipType::PARENT_T, stmtTokenObject6, stmtTokenObject5));
	REQUIRE(pkb.getRelationship(RelationshipType::FOLLOWS, stmtTokenObject5, stmtTokenObject4));
	REQUIRE(pkb.getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject5, stmtTokenObject4));


	std::unordered_set<std::string> usesExpectedResult({ variable_value_one });
	std::unordered_set<std::string> modifiesExpectedResult({ variable_value_one });
	std::unordered_set<std::string> parentExpectedResult({ read_value_one });
	std::unordered_set<std::string> parentTExpectedResult({ read_value_one });
	std::unordered_set<std::string> followsExpectedResult({ print_value_one });
	std::unordered_set<std::string> followsTExpectedResult({ print_value_one });

	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::USES, stmtTokenObject1, DesignEntity::VARIABLE) == usesExpectedResult);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject1, DesignEntity::VARIABLE) == modifiesExpectedResult);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject6, DesignEntity::READ) == parentExpectedResult);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject6, DesignEntity::READ) == parentTExpectedResult);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::FOLLOWS, stmtTokenObject5, DesignEntity::PRINT) == followsExpectedResult);
	REQUIRE(pkb.getRelationshipByFirst(RelationshipType::FOLLOWS_T, stmtTokenObject5, DesignEntity::PRINT) == followsTExpectedResult);


	std::unordered_set<std::string> usesExpectedResultTwo({ assign_value_one });
	std::unordered_set<std::string> modifiesExpectedResultTwo({ assign_value_one });
	std::unordered_set<std::string> parentExpectedResultTwo({ while_value_one });
	std::unordered_set<std::string> parentTExpectedResultTwo({ while_value_one });
	std::unordered_set<std::string> followsExpectedResultTwo({ read_value_one });
	std::unordered_set<std::string> followsTExpectedResultTwo({ read_value_one });

	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::USES, DesignEntity::ASSIGN, variableTokenObject) == usesExpectedResultTwo);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::ASSIGN, variableTokenObject) == modifiesExpectedResultTwo);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::WHILE, stmtTokenObject5) == parentExpectedResultTwo);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::WHILE, stmtTokenObject5) == parentTExpectedResultTwo);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::FOLLOWS, DesignEntity::READ, stmtTokenObject4) == followsExpectedResultTwo);
	REQUIRE(pkb.getRelationshipBySecond(RelationshipType::FOLLOWS_T, DesignEntity::READ, stmtTokenObject4) == followsTExpectedResultTwo);


	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultUsesAll{ { assign_value_one, std::unordered_set<std::string>({variable_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultModifiesAll{ { assign_value_one, std::unordered_set<std::string>({variable_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultParentAll{ { while_value_one, std::unordered_set<std::string>({read_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultParentTAll{ { while_value_one, std::unordered_set<std::string>({read_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultFollowsAll{ { read_value_one, std::unordered_set<std::string>({print_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultFollowsTAll{ { read_value_one, std::unordered_set<std::string>({print_value_one}) } };

	REQUIRE(pkb.getAllRelationship(RelationshipType::USES, DesignEntity::ASSIGN, DesignEntity::VARIABLE) == expectedResultUsesAll);
	REQUIRE(pkb.getAllRelationship(RelationshipType::MODIFIES, DesignEntity::ASSIGN, DesignEntity::VARIABLE) == expectedResultModifiesAll);
	REQUIRE(pkb.getAllRelationship(RelationshipType::PARENT, DesignEntity::WHILE, DesignEntity::READ) == expectedResultParentAll);
	REQUIRE(pkb.getAllRelationship(RelationshipType::PARENT_T, DesignEntity::WHILE, DesignEntity::READ) == expectedResultParentTAll);
	REQUIRE(pkb.getAllRelationship(RelationshipType::FOLLOWS, DesignEntity::READ, DesignEntity::PRINT) == expectedResultFollowsAll);
	REQUIRE(pkb.getAllRelationship(RelationshipType::FOLLOWS_T, DesignEntity::READ, DesignEntity::PRINT) == expectedResultFollowsTAll);

	//Pattern
	//ASSIGN
	std::unordered_set<std::string> assignGetPatternNameNameOne = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSecondOne);
	std::unordered_set<std::string> assignGetPatternNameNameTwo = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, assignPatternTokenObjectSecondTwo);
	std::unordered_set<std::string> assignGetPatternNameSubexprOne = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSubexprOne);
	std::unordered_set<std::string> assignGetPatternNameSubexprTwo = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, assignPatternTokenObjectSubexprTwo);
	std::unordered_set<std::string> assignGetPatternNameSubexprThree = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSubexprThree);
	std::unordered_set<std::string> assignGetPatternNameWildcardOne = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, wildCardTokenObject);
	std::unordered_set<std::string> assignGetPatternNameWildcardTwo = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, wildCardTokenObject);

	//IF
	std::unordered_set<std::string> ifGetPatternNameNameOne = pkb.getPattern(DesignEntity::IF, ifPatternTokenObjectFirstOne, TokenObject());
	std::unordered_set<std::string> ifGetPatternNameNameTwo = pkb.getPattern(DesignEntity::IF, ifPatternTokenObjectFirstTwo, TokenObject());

	//WHILE
	std::unordered_set<std::string> whileGetPatternNameNameOne = pkb.getPattern(DesignEntity::WHILE, whilePatternTokenObjectFirstOne, TokenObject());
	std::unordered_set<std::string> whileGetPatternNameNameTwo = pkb.getPattern(DesignEntity::WHILE, whilePatternTokenObjectFirstTwo, TokenObject());

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

	//ASSIGN
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
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameNameOne = pkb.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSecondOne);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameNameTwo = pkb.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSecondTwo);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprOne = pkb.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprOne);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprTwo = pkb.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprTwo);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprThree = pkb.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprThree);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameWildcard = pkb.getPatternPair(DesignEntity::ASSIGN, wildCardTokenObject);

	//IF
	std::vector<std::pair<std::string, std::string>> ifGetPatternPairNameNameOne = pkb.getPatternPair(DesignEntity::IF, ifPatternTokenObjectFirstOne);
	std::vector<std::pair<std::string, std::string>> ifGetPatternPairNameNameTwo = pkb.getPatternPair(DesignEntity::IF, ifPatternTokenObjectFirstTwo);

	//WHILE
	std::vector<std::pair<std::string, std::string>> whileGetPatternPairNameNameOne = pkb.getPatternPair(DesignEntity::WHILE, whilePatternTokenObjectFirstOne);
	std::vector<std::pair<std::string, std::string>> whileGetPatternPairNameNameTwo = pkb.getPatternPair(DesignEntity::WHILE, whilePatternTokenObjectFirstTwo);

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

	//IF
	REQUIRE(ifGetPatternPairNameNameOne == ifExpectedGetPatternPairNameNameOne);
	REQUIRE(ifGetPatternPairNameNameTwo == ifExpectedGetPatternPairNameNameTwo);

	//WHILE
	REQUIRE(whileGetPatternPairNameNameOne == whileExpectedGetPatternPairNameNameOne);
	REQUIRE(whileGetPatternPairNameNameTwo == whileExpectedGetPatternPairNameNameTwo);
}
