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

	REQUIRE(relManager.getRelationship(RelationshipType::USES, stmtTokenObject1, variableTokenObject));
	REQUIRE(relManager.getRelationship(RelationshipType::MODIFIES, stmtTokenObject1, variableTokenObject));
	REQUIRE(relManager.getRelationship(RelationshipType::PARENT, stmtTokenObject6, stmtTokenObject5));
	REQUIRE(relManager.getRelationship(RelationshipType::PARENT_T, stmtTokenObject6, stmtTokenObject5));
	REQUIRE(relManager.getRelationship(RelationshipType::FOLLOWS, stmtTokenObject5, stmtTokenObject4));
	REQUIRE(relManager.getRelationship(RelationshipType::FOLLOWS_T, stmtTokenObject5, stmtTokenObject4));


	std::unordered_set<std::string> usesExpectedResult({ variable_value_one });
	std::unordered_set<std::string> modifiesExpectedResult({ variable_value_one });
	std::unordered_set<std::string> parentExpectedResult({ read_value_one });
	std::unordered_set<std::string> parentTExpectedResult({ read_value_one });
	std::unordered_set<std::string> followsExpectedResult({ print_value_one });
	std::unordered_set<std::string> followsTExpectedResult({ print_value_one });

	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::USES, stmtTokenObject1, DesignEntity::VARIABLE) == usesExpectedResult);
	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::MODIFIES, stmtTokenObject1, DesignEntity::VARIABLE) == modifiesExpectedResult);
	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::PARENT, stmtTokenObject6, DesignEntity::READ) == parentExpectedResult);
	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::PARENT_T, stmtTokenObject6, DesignEntity::READ) == parentTExpectedResult);
	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::FOLLOWS, stmtTokenObject5, DesignEntity::PRINT) == followsExpectedResult);
	REQUIRE(relManager.getRelationshipByFirst(RelationshipType::FOLLOWS_T, stmtTokenObject5, DesignEntity::PRINT) == followsTExpectedResult);

	
	std::unordered_set<std::string> usesExpectedResultTwo({ assign_value_one });
	std::unordered_set<std::string> modifiesExpectedResultTwo({ assign_value_one });
	std::unordered_set<std::string> parentExpectedResultTwo({ while_value_one });
	std::unordered_set<std::string> parentTExpectedResultTwo({ while_value_one });
	std::unordered_set<std::string> followsExpectedResultTwo({ read_value_one });
	std::unordered_set<std::string> followsTExpectedResultTwo({ read_value_one });

	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::USES, DesignEntity::ASSIGN, variableTokenObject) == usesExpectedResultTwo);
	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::MODIFIES, DesignEntity::ASSIGN, variableTokenObject) == modifiesExpectedResultTwo);
	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::PARENT, DesignEntity::WHILE, stmtTokenObject5) == parentExpectedResultTwo);
	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::PARENT_T, DesignEntity::WHILE, stmtTokenObject5) == parentTExpectedResultTwo);
	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::FOLLOWS, DesignEntity::READ, stmtTokenObject4) == followsExpectedResultTwo);
	REQUIRE(relManager.getRelationshipBySecond(RelationshipType::FOLLOWS_T, DesignEntity::READ, stmtTokenObject4) == followsTExpectedResultTwo);


	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultUsesAll{ { assign_value_one, std::unordered_set<std::string>({variable_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultModifiesAll{ { assign_value_one, std::unordered_set<std::string>({variable_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultParentAll{ { while_value_one, std::unordered_set<std::string>({read_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultParentTAll{ { while_value_one, std::unordered_set<std::string>({read_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultFollowsAll{ { read_value_one, std::unordered_set<std::string>({print_value_one}) } };
	std::unordered_map<std::string, std::unordered_set<std::string>> expectedResultFollowsTAll{ { read_value_one, std::unordered_set<std::string>({print_value_one}) } };

	REQUIRE(relManager.getAllRelationship(RelationshipType::USES, DesignEntity::ASSIGN, DesignEntity::VARIABLE) == expectedResultUsesAll);
	REQUIRE(relManager.getAllRelationship(RelationshipType::MODIFIES, DesignEntity::ASSIGN, DesignEntity::VARIABLE) == expectedResultModifiesAll);
	REQUIRE(relManager.getAllRelationship(RelationshipType::PARENT, DesignEntity::WHILE, DesignEntity::READ) == expectedResultParentAll);
	REQUIRE(relManager.getAllRelationship(RelationshipType::PARENT_T, DesignEntity::WHILE, DesignEntity::READ) == expectedResultParentTAll);
	REQUIRE(relManager.getAllRelationship(RelationshipType::FOLLOWS, DesignEntity::READ, DesignEntity::PRINT) == expectedResultFollowsAll);
	REQUIRE(relManager.getAllRelationship(RelationshipType::FOLLOWS_T, DesignEntity::READ, DesignEntity::PRINT) == expectedResultFollowsTAll);
}