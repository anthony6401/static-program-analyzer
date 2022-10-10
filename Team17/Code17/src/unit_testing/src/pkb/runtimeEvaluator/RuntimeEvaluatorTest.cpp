#include <catch.hpp>

#include "components/pkb/storage/RelationshipStorage/NextRelationshipStorage.h"
#include "components/pkb/runtimeEvaluator/NextTRelationshipEvaluator.h"

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
