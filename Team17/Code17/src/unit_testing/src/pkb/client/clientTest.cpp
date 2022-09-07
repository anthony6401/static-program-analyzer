#include "models/Relationship/Relationship.h"
#include "models/Relationship/UsesRelationship.h"

#include "components/pkb/clients/QPSClient.h"
#include "components/pkb/clients/SPClient.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"

#include "components/pkb/pkb.h"

#include "../EntityObject.h"

#include <catch.hpp>

static Relationship* usesRel = new UsesRelationship(assignEntity, variableEntity); 

PKB* pkb = new PKB();


TEST_CASE("SP Client test") {
	SPClient spClient = SPClient(pkb);

	REQUIRE(spClient.storeRelationship(usesRel));
}

TEST_CASE("QPS Client test") {
	QPSClient qpsClient = QPSClient(pkb);

	std::unordered_set<std::string> ass_set;
	ass_set.insert(assign_value_one);

	std::unordered_set<std::string> var_set;
	var_set.insert(variable_value_one);

	REQUIRE(qpsClient.getAllEntity(qps::TokenType::ASSIGN) == ass_set);
	REQUIRE(qpsClient.getAllEntity(qps::TokenType::VARIABLE) == var_set);


}