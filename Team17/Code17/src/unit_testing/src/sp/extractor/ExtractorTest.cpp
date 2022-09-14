#include "components/sp/extractor/Extractor.h"

#include <catch.hpp>

Extractor generateExtractor() {
	PKB* pkb = new PKB();
	SPClient* client = new SPClient(pkb);
	Extractor testExtractor = Extractor(client);
}

TEST_CASE("Unit test - extractReadStmt for valid tokentype variable a") {
	Extractor testExtractor = generateExtractor();
}
TEST_CASE("Unit test - extractReadStmt for invalid tokentype constant 1") {}
TEST_CASE("Unit test - extractReadStmt for invalid tokentype procedure proc") {}

TEST_CASE("Unit test - extractPrintStmt for valid tokentype variable a") {}
TEST_CASE("Unit test - extractPrintStmt for invalid tokentype constant 1 ") {}
TEST_CASE("Unit test - extractPrintStmt for invalid tokentype procedure proc") {}

TEST_CASE("Unit test - extractAssignStmt") {}

TEST_CASE("Integration test - extractProcedure") {}
TEST_CASE("Integration test - extractParentRelationships") {}
TEST_CASE("Integration test - extractFollowsRelationships") {}
TEST_CASE("Integration test - extractSeriesOfStmts") {}
TEST_CASE("Integration test - extractWhileStmt") {}
TEST_CASE("Integration test - extractIfStmt") {}
TEST_CASE("Integration test - extractStmtLst") {}

// TO BE IMPLEMENTED
TEST_CASE("extractCondExpr") {}
TEST_CASE("extractCall") {}
