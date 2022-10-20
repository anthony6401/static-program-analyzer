#include "ParentRelationshipStorageInterface.h"
#include "ParentRelationshipStorage.h"
#include "models/Relationship/ParentRelationship.h"
#include "components/pkb/storage/RelationshipStorage/utils.h"


ParentRelationshipStorage::ParentRelationshipStorage() : ParentRelationshipStorageInterface(RelationshipType::PARENT) {}

bool ParentRelationshipStorage::storeRelationship(Relationship* rel) {
	ParentRelationship* parentRelationship = dynamic_cast<ParentRelationship*>(rel);

	if (parentRelationship) {
		Entity* leftEntity = parentRelationship->getLeftEntity();
		Entity* rightEntity = parentRelationship->getRightEntity();

		DesignEntity left = RelationshipUtils::entityToDesignEntity(leftEntity);
		DesignEntity right = RelationshipUtils::entityToDesignEntity(rightEntity);

		std::string leftValue = leftEntity->getValue();
		std::string rightValue = rightEntity->getValue();

		//Get all the neccessary storage
		std::unordered_map<std::string, std::unordered_set<std::string>>* stmtToStmtForwardStorage = getStorageForward(DesignEntity::STMT, DesignEntity::STMT);
		std::unordered_map<std::string, std::unordered_set<std::string>>* stmtToStmtBackwardStorage = getStorageBackward(DesignEntity::STMT);
		std::unordered_map<std::string, std::unordered_set<std::string>>* stmtToRightForwardStorage = getStorageForward(DesignEntity::STMT, right);
		std::unordered_map<std::string, std::unordered_set<std::string>>* leftToRightForwardStorage = getStorageForward(left, right);
		std::unordered_map<std::string, std::unordered_set<std::string>>* leftToStmtForwardStorage = getStorageForward(left, DesignEntity::STMT);
		std::unordered_map<std::string, std::unordered_set<std::string>>* leftToStmtBackwardStorage = getStorageBackward(left);

		bool result = false;
		bool resultOne = RelationshipUtils::insertEntity(stmtToStmtForwardStorage, leftValue, rightValue);
		bool resultTwo = RelationshipUtils::insertEntity(stmtToStmtBackwardStorage, rightValue, leftValue);
		bool resultThree = RelationshipUtils::insertEntity(stmtToRightForwardStorage, leftValue, rightValue);
		bool resultFour = RelationshipUtils::insertEntity(leftToRightForwardStorage, leftValue, rightValue);
		bool resultFive = RelationshipUtils::insertEntity(leftToStmtForwardStorage, leftValue, rightValue);
		bool resultSix = RelationshipUtils::insertEntity(leftToStmtBackwardStorage, rightValue, leftValue);

		result = result || resultOne || resultTwo || resultThree || resultFour || resultFive || resultSix;

		return result;
	}
	return false;
}