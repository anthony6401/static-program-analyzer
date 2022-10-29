#include <catch.hpp>

#include "components/pkb/storage/RelationshipStorage/NextRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/ModifyRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/UsesRelationshipStorage.h"
#include "components/pkb/runtimeEvaluator/NextTRelationshipEvaluator.h"
#include "components/pkb/runtimeEvaluator/AffectsRelationshipEvaluator.h"
#include "components/pkb/runtimeEvaluator/AffectsTRelationshipEvaluator.h"

#include "../RelationshipObject.h"
#include "../ReuseableTokenObject.h"

#include <catch.hpp>

TEST_CASE("NextT Relationship Evaluator Test") {
	NextRelationshipStorage* nextRelationshipStorage = new NextRelationshipStorage();
	NextTRelationshipEvaluator* nextTRelationshipEvaluator = new NextTRelationshipEvaluator(nextRelationshipStorage);

	// Populate PKB
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipAssignCallOne));
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipCallIfOne));
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipIfPrintOne));
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipPrintReadOne));
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipReadWhileOne));

	// Test for Next*(1, 2)
	REQUIRE(nextTRelationshipEvaluator->getRuntimeRelationship(RelationshipType::NEXT_T, stmtTokenObject1, stmtTokenObject6));
	REQUIRE(nextTRelationshipEvaluator->getRuntimeRelationship(RelationshipType::NEXT_T, stmtTokenObject2, stmtTokenObject6));
	REQUIRE(nextTRelationshipEvaluator->getRuntimeRelationship(RelationshipType::NEXT_T, stmtTokenObject3, stmtTokenObject6));
	REQUIRE(nextTRelationshipEvaluator->getRuntimeRelationship(RelationshipType::NEXT_T, stmtTokenObject2, stmtTokenObject5));
	REQUIRE(nextTRelationshipEvaluator->getRuntimeRelationship(RelationshipType::NEXT_T, stmtTokenObject3, stmtTokenObject4));
	REQUIRE(!nextTRelationshipEvaluator->getRuntimeRelationship(RelationshipType::NEXT_T, stmtTokenObject2, stmtTokenObject7));
	REQUIRE(!nextTRelationshipEvaluator->getRuntimeRelationship(RelationshipType::NEXT_T, stmtTokenObject3, stmtTokenObject1));
	REQUIRE(nextTRelationshipEvaluator->getRuntimeRelationship(RelationshipType::NEXT_T, wildcardTokenObject, stmtTokenObject6));
	REQUIRE(nextTRelationshipEvaluator->getRuntimeRelationship(RelationshipType::NEXT_T, stmtTokenObject3, wildcardTokenObject));
	REQUIRE(nextTRelationshipEvaluator->getRuntimeRelationship(RelationshipType::NEXT_T, wildcardTokenObject, wildcardTokenObject));

	std::unordered_set<std::string> stmt_filter = { assign_value_one, call_value_one, if_value_one, print_value_one, read_value_one, while_value_one };
	std::unordered_set<std::string> a_filter = { assign_value_one };
	std::unordered_set<std::string> c_filter = { call_value_one };
	std::unordered_set<std::string> if_filter = { if_value_one };
	std::unordered_set<std::string> pr_filter = { print_value_one };
	std::unordered_set<std::string> r_filter = { read_value_one };
	std::unordered_set<std::string> w_filter = { while_value_one };

	std::unordered_set<std::string> empty = {};

	// Test for Next*(1, s)
	std::unordered_set<std::string> expectedResultByFirstStmt = { call_value_one, if_value_one, print_value_one, read_value_one, while_value_one };
	std::unordered_set<std::string> expectedResultByFirstPrint = { print_value_one };
	std::unordered_set<std::string> expectedResultByFirstRead = { read_value_one };
	std::unordered_set<std::string> expectedResultByFirstWhile = { while_value_one };

	REQUIRE(nextTRelationshipEvaluator->getRuntimeRelationshipByFirst(RelationshipType::NEXT_T, stmtTokenObject1, stmt_filter) == expectedResultByFirstStmt);
	REQUIRE(nextTRelationshipEvaluator->getRuntimeRelationshipByFirst(RelationshipType::NEXT_T, stmtTokenObject2, pr_filter) == expectedResultByFirstPrint);
	REQUIRE(nextTRelationshipEvaluator->getRuntimeRelationshipByFirst(RelationshipType::NEXT_T, stmtTokenObject3, r_filter) == expectedResultByFirstRead);
	REQUIRE(nextTRelationshipEvaluator->getRuntimeRelationshipByFirst(RelationshipType::NEXT_T, stmtTokenObject4, w_filter) == expectedResultByFirstWhile);
	REQUIRE(nextTRelationshipEvaluator->getRuntimeRelationshipByFirst(RelationshipType::NEXT_T, stmtTokenObject1, a_filter) == empty);

	REQUIRE(nextTRelationshipEvaluator->getRuntimeRelationshipWithFirstWildcard(RelationshipType::NEXT_T, stmt_filter, stmt_filter) == expectedResultByFirstStmt);

	// Test for Next*(s, 2)
	std::unordered_set<std::string> expectedResultBySecondStmt = { assign_value_one, call_value_one, if_value_one, print_value_one, read_value_one };
	std::unordered_set<std::string> expectedResultBySecondAssign = { assign_value_one };
	std::unordered_set<std::string> expectedResultBySecondCall = { call_value_one };
	std::unordered_set<std::string> expectedResultBySecondIf = { if_value_one };

	REQUIRE(nextTRelationshipEvaluator->getRuntimeRelationshipBySecond(RelationshipType::NEXT_T, stmtTokenObject6, stmt_filter) == expectedResultBySecondStmt);
	REQUIRE(nextTRelationshipEvaluator->getRuntimeRelationshipBySecond(RelationshipType::NEXT_T, stmtTokenObject5, if_filter) == expectedResultBySecondIf);
	REQUIRE(nextTRelationshipEvaluator->getRuntimeRelationshipBySecond(RelationshipType::NEXT_T, stmtTokenObject4, c_filter) == expectedResultBySecondCall);
	REQUIRE(nextTRelationshipEvaluator->getRuntimeRelationshipBySecond(RelationshipType::NEXT_T, stmtTokenObject3, a_filter) == expectedResultBySecondAssign);
	REQUIRE(nextTRelationshipEvaluator->getRuntimeRelationshipBySecond(RelationshipType::NEXT_T, stmtTokenObject6, w_filter) == empty);

	REQUIRE(nextTRelationshipEvaluator->getRuntimeRelationshipWithSecondWildcard(RelationshipType::NEXT_T, stmt_filter, stmt_filter) == expectedResultBySecondStmt);

	std::unordered_map<std::string, std::unordered_set<std::string>> emptyMap = {};
	// Test for Next*(s1, s2)
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedStmtStmtAll{
									{ assign_value_one, std::unordered_set<std::string>({call_value_one, if_value_one, print_value_one, read_value_one, while_value_one})},
									{ call_value_one, std::unordered_set<std::string>({if_value_one, print_value_one, read_value_one, while_value_one})},
									{ if_value_one, std::unordered_set<std::string>({print_value_one, read_value_one, while_value_one})},
									{ print_value_one, std::unordered_set<std::string>({read_value_one, while_value_one})},
									{ read_value_one, std::unordered_set<std::string>({while_value_one})} };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedStmtWhileAll{
									{ assign_value_one, std::unordered_set<std::string>({while_value_one})},
									{ call_value_one, std::unordered_set<std::string>({while_value_one})},
									{ if_value_one, std::unordered_set<std::string>({while_value_one})},
									{ print_value_one, std::unordered_set<std::string>({while_value_one})},
									{ read_value_one, std::unordered_set<std::string>({while_value_one})} };


	REQUIRE(nextTRelationshipEvaluator->getAllRuntimeRelationship(RelationshipType::NEXT_T, stmt_filter, stmt_filter) == expectedStmtStmtAll);
	REQUIRE(nextTRelationshipEvaluator->getAllRuntimeRelationship(RelationshipType::NEXT_T, stmt_filter, w_filter) == expectedStmtWhileAll);
	REQUIRE(nextTRelationshipEvaluator->getAllRuntimeRelationship(RelationshipType::NEXT_T, w_filter, stmt_filter) == emptyMap);
}

TEST_CASE("Affects Relationship Evaluator Test") {
	NextRelationshipStorage* nextRelationshipStorage = new NextRelationshipStorage();
	ModifyRelationshipStorage* modifyRelationshipStorage = new ModifyRelationshipStorage();
	UsesRelationshipStorage* usesRelationshipStorage = new UsesRelationshipStorage();
	AffectsRelationshipEvaluator* affectsRelationshipEvaluator = new AffectsRelationshipEvaluator(nextRelationshipStorage, modifyRelationshipStorage, usesRelationshipStorage);

	// Populate PKB for Next
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipAffectsOne));
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipAffectsTwo));
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipAffectsThree));
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipAffectsFour));
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipAffectsFive));
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipAffectsSix));
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipAffectsSeven));

	// Populate PKB for Modifies
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipAffectsOne));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipAffectsTwo));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipAffectsThree));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipAffectsFour));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipAffectsFive));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipAffectsSix));

	// Populate PKB for Uses
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipAffectsOne));
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipAffectsTwo));
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipAffectsThree));
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipAffectsFour));

	// Test for affects(1, 2)
	REQUIRE(affectsRelationshipEvaluator->getRuntimeRelationship(RelationshipType::AFFECTS, stmtTokenObject1, stmtTokenObject5));
	REQUIRE(affectsRelationshipEvaluator->getRuntimeRelationship(RelationshipType::AFFECTS, stmtTokenObject3, stmtTokenObject5));
	REQUIRE(!affectsRelationshipEvaluator->getRuntimeRelationship(RelationshipType::AFFECTS, stmtTokenObject1, stmtTokenObject7));
	REQUIRE(!affectsRelationshipEvaluator->getRuntimeRelationship(RelationshipType::AFFECTS, stmtTokenObject1, stmtTokenObject4));

	REQUIRE(affectsRelationshipEvaluator->getRuntimeRelationship(RelationshipType::AFFECTS, stmtTokenObject3, wildcardTokenObject));
	REQUIRE(affectsRelationshipEvaluator->getRuntimeRelationship(RelationshipType::AFFECTS, wildcardTokenObject, stmtTokenObject5));
	REQUIRE(affectsRelationshipEvaluator->getRuntimeRelationship(RelationshipType::AFFECTS, wildcardTokenObject, wildcardTokenObject));

	std::unordered_set<std::string> a_filter = { stmt1, stmt3, stmt4, stmt5, stmt7 };
	std::unordered_set<std::string> empty = {};

	// Test for Affects(1, a)
	std::unordered_set<std::string> expectedResultByFirst = { stmt5 };
	std::unordered_set<std::string> expectedResultByFirst2 = { stmt7 };
	std::unordered_set<std::string> expectedResultByFirst3 = { stmt5, stmt7 };

	REQUIRE(affectsRelationshipEvaluator->getRuntimeRelationshipByFirst(RelationshipType::AFFECTS, stmtTokenObject1, a_filter) == expectedResultByFirst);
	REQUIRE(affectsRelationshipEvaluator->getRuntimeRelationshipByFirst(RelationshipType::AFFECTS, stmtTokenObject2, a_filter) == empty);
	REQUIRE(affectsRelationshipEvaluator->getRuntimeRelationshipByFirst(RelationshipType::AFFECTS, stmtTokenObject3, a_filter) == expectedResultByFirst);
	REQUIRE(affectsRelationshipEvaluator->getRuntimeRelationshipByFirst(RelationshipType::AFFECTS, stmtTokenObject4, a_filter) == empty);
	REQUIRE(affectsRelationshipEvaluator->getRuntimeRelationshipByFirst(RelationshipType::AFFECTS, stmtTokenObject5, a_filter) == expectedResultByFirst2);
	REQUIRE(affectsRelationshipEvaluator->getRuntimeRelationshipByFirst(RelationshipType::AFFECTS, stmtTokenObject6, a_filter) == empty);
	REQUIRE(affectsRelationshipEvaluator->getRuntimeRelationshipByFirst(RelationshipType::AFFECTS, stmtTokenObject7, a_filter) == empty);

	REQUIRE(affectsRelationshipEvaluator->getRuntimeRelationshipWithFirstWildcard(RelationshipType::AFFECTS, a_filter, a_filter) == expectedResultByFirst3);
	
	// Test for Affects(a, 2)
	std::unordered_set<std::string> expectedResultBySecond = { stmt1, stmt3 };
	std::unordered_set<std::string> expectedResultBySecond2 = { stmt5 };
	std::unordered_set<std::string> expectedResultBySecond3 = { stmt1, stmt3, stmt5 };

	REQUIRE(affectsRelationshipEvaluator->getRuntimeRelationshipBySecond(RelationshipType::AFFECTS, stmtTokenObject1, a_filter) == empty);
	REQUIRE(affectsRelationshipEvaluator->getRuntimeRelationshipBySecond(RelationshipType::AFFECTS, stmtTokenObject2, a_filter) == empty);
	REQUIRE(affectsRelationshipEvaluator->getRuntimeRelationshipBySecond(RelationshipType::AFFECTS, stmtTokenObject3, a_filter) == empty);
	REQUIRE(affectsRelationshipEvaluator->getRuntimeRelationshipBySecond(RelationshipType::AFFECTS, stmtTokenObject4, a_filter) == empty);
	REQUIRE(affectsRelationshipEvaluator->getRuntimeRelationshipBySecond(RelationshipType::AFFECTS, stmtTokenObject5, a_filter) == expectedResultBySecond);
	REQUIRE(affectsRelationshipEvaluator->getRuntimeRelationshipBySecond(RelationshipType::AFFECTS, stmtTokenObject6, a_filter) == empty);
	REQUIRE(affectsRelationshipEvaluator->getRuntimeRelationshipBySecond(RelationshipType::AFFECTS, stmtTokenObject7, a_filter) == expectedResultBySecond2);

	REQUIRE(affectsRelationshipEvaluator->getRuntimeRelationshipWithSecondWildcard(RelationshipType::AFFECTS, a_filter, a_filter) == expectedResultBySecond3);

	std::unordered_map<std::string, std::unordered_set<std::string>> emptyMap = {};
	// Test for Affects(a1, a2)
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAll{
									{ stmt1, std::unordered_set<std::string>({ stmt5 })},
									{ stmt3, std::unordered_set<std::string>({ stmt5 })},
									{ stmt5, std::unordered_set<std::string>({ stmt7 })} };

	std::unordered_set<std::string> if_filter = { stmt2 };

	REQUIRE(affectsRelationshipEvaluator->getAllRuntimeRelationship(RelationshipType::AFFECTS, a_filter, a_filter) == expectedResultAll);
	REQUIRE(affectsRelationshipEvaluator->getAllRuntimeRelationship(RelationshipType::AFFECTS, if_filter, a_filter) == emptyMap);
}

TEST_CASE("AffectsT Relationship Evaluator Test") {
	NextRelationshipStorage* nextRelationshipStorage = new NextRelationshipStorage();
	ModifyRelationshipStorage* modifyRelationshipStorage = new ModifyRelationshipStorage();
	UsesRelationshipStorage* usesRelationshipStorage = new UsesRelationshipStorage();
	AffectsTRelationshipEvaluator* affectsTRelationshipEvaluator = new AffectsTRelationshipEvaluator(nextRelationshipStorage, modifyRelationshipStorage, usesRelationshipStorage);

	// Populate PKB for Next
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipAffectsOne));
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipAffectsTwo));
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipAffectsThree));
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipAffectsFour));
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipAffectsFive));
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipAffectsSix));
	REQUIRE(nextRelationshipStorage->storeRelationship(nextRelationshipAffectsSeven));

	// Populate PKB for Modifies
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipAffectsOne));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipAffectsTwo));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipAffectsThree));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipAffectsFour));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipAffectsFive));
	REQUIRE(modifyRelationshipStorage->storeRelationship(modifyRelationshipAffectsSix));

	// Populate PKB for Uses
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipAffectsOne));
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipAffectsTwo));
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipAffectsThree));
	REQUIRE(usesRelationshipStorage->storeRelationship(usesRelationshipAffectsFour));

	// Test for affectsT(1, 2)
	REQUIRE(affectsTRelationshipEvaluator->getRuntimeRelationship(RelationshipType::AFFECTS_T, stmtTokenObject1, stmtTokenObject5));
	REQUIRE(affectsTRelationshipEvaluator->getRuntimeRelationship(RelationshipType::AFFECTS_T, stmtTokenObject3, stmtTokenObject5));
	REQUIRE(affectsTRelationshipEvaluator->getRuntimeRelationship(RelationshipType::AFFECTS_T, stmtTokenObject1, stmtTokenObject7));

	REQUIRE(!affectsTRelationshipEvaluator->getRuntimeRelationship(RelationshipType::AFFECTS_T, stmtTokenObject1, stmtTokenObject4));

	REQUIRE(affectsTRelationshipEvaluator->getRuntimeRelationship(RelationshipType::AFFECTS_T, stmtTokenObject1, wildcardTokenObject));
	REQUIRE(affectsTRelationshipEvaluator->getRuntimeRelationship(RelationshipType::AFFECTS_T, wildcardTokenObject, stmtTokenObject7));
	REQUIRE(affectsTRelationshipEvaluator->getRuntimeRelationship(RelationshipType::AFFECTS_T, wildcardTokenObject, wildcardTokenObject));

	std::unordered_set<std::string> a_filter = { stmt1, stmt3, stmt4, stmt5, stmt7 };
	std::unordered_set<std::string> empty = {};

	 //Test for AffectsT(1, a)
	std::unordered_set<std::string> expectedResultByFirst = { stmt5, stmt7 };
	std::unordered_set<std::string> expectedResultByFirst2 = { stmt7 };

	REQUIRE(affectsTRelationshipEvaluator->getRuntimeRelationshipByFirst(RelationshipType::AFFECTS_T, stmtTokenObject1, a_filter) == expectedResultByFirst);
	REQUIRE(affectsTRelationshipEvaluator->getRuntimeRelationshipByFirst(RelationshipType::AFFECTS_T, stmtTokenObject2, a_filter) == empty);
	REQUIRE(affectsTRelationshipEvaluator->getRuntimeRelationshipByFirst(RelationshipType::AFFECTS_T, stmtTokenObject3, a_filter) == expectedResultByFirst);
	REQUIRE(affectsTRelationshipEvaluator->getRuntimeRelationshipByFirst(RelationshipType::AFFECTS_T, stmtTokenObject4, a_filter) == empty);
	REQUIRE(affectsTRelationshipEvaluator->getRuntimeRelationshipByFirst(RelationshipType::AFFECTS_T, stmtTokenObject5, a_filter) == expectedResultByFirst2);
	REQUIRE(affectsTRelationshipEvaluator->getRuntimeRelationshipByFirst(RelationshipType::AFFECTS_T, stmtTokenObject6, a_filter) == empty);
	REQUIRE(affectsTRelationshipEvaluator->getRuntimeRelationshipByFirst(RelationshipType::AFFECTS_T, stmtTokenObject7, a_filter) == empty);

	REQUIRE(affectsTRelationshipEvaluator->getRuntimeRelationshipWithFirstWildcard(RelationshipType::AFFECTS_T, a_filter, a_filter) == expectedResultByFirst);

	// Test for Affects(a, 2)
	std::unordered_set<std::string> expectedResultBySecond = { stmt1, stmt3 };
	std::unordered_set<std::string> expectedResultBySecond2 = { stmt1,stmt3, stmt5 };

	REQUIRE(affectsTRelationshipEvaluator->getRuntimeRelationshipBySecond(RelationshipType::AFFECTS_T, stmtTokenObject1, a_filter) == empty);
	REQUIRE(affectsTRelationshipEvaluator->getRuntimeRelationshipBySecond(RelationshipType::AFFECTS_T, stmtTokenObject2, a_filter) == empty);
	REQUIRE(affectsTRelationshipEvaluator->getRuntimeRelationshipBySecond(RelationshipType::AFFECTS_T, stmtTokenObject3, a_filter) == empty);
	REQUIRE(affectsTRelationshipEvaluator->getRuntimeRelationshipBySecond(RelationshipType::AFFECTS_T, stmtTokenObject4, a_filter) == empty);
	REQUIRE(affectsTRelationshipEvaluator->getRuntimeRelationshipBySecond(RelationshipType::AFFECTS_T, stmtTokenObject5, a_filter) == expectedResultBySecond);
	REQUIRE(affectsTRelationshipEvaluator->getRuntimeRelationshipBySecond(RelationshipType::AFFECTS_T, stmtTokenObject6, a_filter) == empty);
	REQUIRE(affectsTRelationshipEvaluator->getRuntimeRelationshipBySecond(RelationshipType::AFFECTS_T, stmtTokenObject7, a_filter) == expectedResultBySecond2);

	REQUIRE(affectsTRelationshipEvaluator->getRuntimeRelationshipWithSecondWildcard(RelationshipType::AFFECTS_T, a_filter, a_filter) == expectedResultBySecond2);



	std::unordered_map<std::string, std::unordered_set<std::string>> emptyMap = {};
	// Test for AffectsT(a1, a2)
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultAll{
									{ stmt1, std::unordered_set<std::string>({stmt5, stmt7})},
									{ stmt3, std::unordered_set<std::string>({stmt5, stmt7})},
									{ stmt5, std::unordered_set<std::string>({ stmt7 })} };

	std::unordered_set<std::string> if_filter = { stmt2 };

	REQUIRE(affectsTRelationshipEvaluator->getAllRuntimeRelationship(RelationshipType::AFFECTS_T, a_filter, a_filter) == expectedResultAll);
	REQUIRE(affectsTRelationshipEvaluator->getAllRuntimeRelationship(RelationshipType::AFFECTS_T, if_filter, a_filter) == emptyMap);
}
