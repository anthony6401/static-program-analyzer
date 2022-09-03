#include "models/Relationship/Relationship.h"
#include "models/Relationship/UsesRelationship.h"
#include "models/Entity/AssignEntity.h"
#include "models/Entity/VariableEntity.h"

#include "components/pkb/pkb.h"
#include "components/pkb/manager/EntityManager.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"

#include "./EntityObject.h"

#include <catch.hpp>


Relationship* usesRel = new UsesRelationship(assignEntity, variableEntity);

TEST_CASE("PKB storeEntity method test") {
	PKB pkb = PKB();

	//Currenty one test is sufficient
	REQUIRE(pkb.storeRelationship(usesRel));
}

TEST_CASE("PKB getAllEntity method test") {
	PKB pkb = PKB();

	pkb.storeRelationship(usesRel);

	std::unordered_set<std::string> ass_set;
	ass_set.insert(value_one);

	std::unordered_set<std::string> var_set;
	var_set.insert(value_one);
	
	REQUIRE(pkb.getAllEntity(qps::TokenType::ASSIGN) == ass_set);
	REQUIRE(pkb.getAllEntity(qps::TokenType::VARIABLE) == var_set);

}