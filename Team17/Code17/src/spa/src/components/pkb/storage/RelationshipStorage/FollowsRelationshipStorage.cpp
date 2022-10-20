#include "FollowsRelationshipStorageInterface.h"
#include "FollowsRelationshipStorage.h"
#include "models/Relationship/FollowsRelationship.h"
#include "models/Relationship/RelationshipType.h"
#include "utils.h"

FollowsRelationshipStorage::FollowsRelationshipStorage() : FollowsRelationshipStorageInterface(RelationshipType::FOLLOWS) {}


bool FollowsRelationshipStorage::storeRelationship(Relationship* rel) {
	FollowsRelationship* followsRelationship = dynamic_cast<FollowsRelationship*>(rel);

	if (followsRelationship) {
		Entity* leftEntity = followsRelationship->getLeftEntity();
		Entity* rightEntity = followsRelationship->getRightEntity();

		std::string leftValue = leftEntity->getValue();
		std::string rightValue = rightEntity->getValue();

		bool result = false;
		DesignEntity left = RelationshipUtils::entityToDesignEntity(leftEntity);
		DesignEntity right = RelationshipUtils::entityToDesignEntity(rightEntity);

		//Get all the neccessary storage
		std::unordered_map<std::string, std::unordered_set<std::string>>* stmtToStmtForwardStorage = getStorageForward(DesignEntity::STMT, DesignEntity::STMT);
		std::unordered_map<std::string, std::unordered_set<std::string>>* stmtToStmtBackwardStorage = getStorageBackward(DesignEntity::STMT);
		std::unordered_map<std::string, std::unordered_set<std::string>>* stmtToRightForwardStorage = getStorageForward(DesignEntity::STMT, right);
		std::unordered_map<std::string, std::unordered_set<std::string>>* leftToRightForwardStorage = getStorageForward(left, right);
		std::unordered_map<std::string, std::unordered_set<std::string>>* leftToStmtForwardStorage = getStorageForward(left, DesignEntity::STMT);
		std::unordered_map<std::string, std::unordered_set<std::string>>* leftToStmtBackwardStorage = getStorageBackward(left);


		bool resultOne = RelationshipUtils::insertEntity(stmtToStmtForwardStorage, leftValue, rightValue);
		bool resultTwo = RelationshipUtils::insertEntity(stmtToStmtBackwardStorage, rightValue, leftValue);
		bool resultThree = RelationshipUtils::insertEntity(stmtToRightForwardStorage, leftValue, rightValue);
		bool resultFour = RelationshipUtils::insertEntity(leftToRightForwardStorage, leftValue, rightValue);
		bool resultFive= RelationshipUtils::insertEntity(leftToStmtForwardStorage, leftValue, rightValue);
		bool resultSix = RelationshipUtils::insertEntity(leftToStmtBackwardStorage, rightValue, leftValue);
		
		result = result || resultOne || resultTwo || resultThree || resultFour || resultFive || resultSix ;
		
		return result;
	}
	return false;
}