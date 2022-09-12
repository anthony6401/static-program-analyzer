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

	std::unordered_set<std::string> ass_set;
	ass_set.insert(assign_value_one);

	std::unordered_set<std::string> var_set;
	var_set.insert(variable_value_one);

	REQUIRE(pkb.getAllEntity(DesignEntity::ASSIGN) == ass_set);
	REQUIRE(pkb.getAllEntity(DesignEntity::VARIABLE) == var_set);

	
}

TEST_CASE("PKB Pattern Manager test") {
	PKB pkb = PKB();

	REQUIRE(pkb.storePattern(assignPatternOne));
	REQUIRE(pkb.storePattern(assignPatternTwo));
	REQUIRE(pkb.storePattern(assignPatternThree));
	REQUIRE(pkb.storePattern(assignPatternFour));
	REQUIRE(pkb.storePattern(assignPatternFive));
	REQUIRE(pkb.storePattern(assignPatternSix));
	REQUIRE(pkb.storePattern(assignPatternSeven));
	REQUIRE(pkb.storePattern(assignPatternEight));

	std::unordered_set<std::string> assignGetPatternNameNameOne = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSecondOne);
	std::unordered_set<std::string> assignGetPatternNameNameTwo = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, assignPatternTokenObjectSecondTwo);
	std::unordered_set<std::string> assignGetPatternNameSubexprOne = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSubexprOne);
	std::unordered_set<std::string> assignGetPatternNameSubexprTwo = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, assignPatternTokenObjectSubexprTwo);
	std::unordered_set<std::string> assignGetPatternNameSubexprThree = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSubexprThree);
	std::unordered_set<std::string> assignGetPatternNameWildcardOne = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, wildCardTokenObject);
	std::unordered_set<std::string> assignGetPatternNameWildcardTwo = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, wildCardTokenObject);

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

	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameNameOne = pkb.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSecondOne);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameNameTwo = pkb.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSecondTwo);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprOne = pkb.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprOne);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprTwo = pkb.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprTwo);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprThree = pkb.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprThree);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameWildcard = pkb.getPatternPair(DesignEntity::ASSIGN, wildCardTokenObject);

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

}

TEST_CASE("All Manager Test") {
	PKB pkb = PKB();

	//Pattern
	REQUIRE(pkb.storePattern(assignPatternOne));
	REQUIRE(pkb.storePattern(assignPatternTwo));
	REQUIRE(pkb.storePattern(assignPatternThree));
	REQUIRE(pkb.storePattern(assignPatternFour));
	REQUIRE(pkb.storePattern(assignPatternFive));
	REQUIRE(pkb.storePattern(assignPatternSix));
	REQUIRE(pkb.storePattern(assignPatternSeven));
	REQUIRE(pkb.storePattern(assignPatternEight));

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

	REQUIRE(pkb.getAllEntity(DesignEntity::ASSIGN) == ass_set);
	REQUIRE(pkb.getAllEntity(DesignEntity::VARIABLE) == var_set);

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
	std::unordered_set<std::string> assignGetPatternNameNameOne = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSecondOne);
	std::unordered_set<std::string> assignGetPatternNameNameTwo = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, assignPatternTokenObjectSecondTwo);
	std::unordered_set<std::string> assignGetPatternNameSubexprOne = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSubexprOne);
	std::unordered_set<std::string> assignGetPatternNameSubexprTwo = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, assignPatternTokenObjectSubexprTwo);
	std::unordered_set<std::string> assignGetPatternNameSubexprThree = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, assignPatternTokenObjectSubexprThree);
	std::unordered_set<std::string> assignGetPatternNameWildcardOne = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstOne, wildCardTokenObject);
	std::unordered_set<std::string> assignGetPatternNameWildcardTwo = pkb.getPattern(DesignEntity::ASSIGN, assignPatternTokenObjectFirstTwo, wildCardTokenObject);

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

	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameNameOne = pkb.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSecondOne);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameNameTwo = pkb.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSecondTwo);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprOne = pkb.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprOne);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprTwo = pkb.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprTwo);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameSubexprThree = pkb.getPatternPair(DesignEntity::ASSIGN, assignPatternTokenObjectSubexprThree);
	std::vector<std::pair<std::string, std::string>> assignGetPatternPairNameWildcard = pkb.getPatternPair(DesignEntity::ASSIGN, wildCardTokenObject);

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
}
