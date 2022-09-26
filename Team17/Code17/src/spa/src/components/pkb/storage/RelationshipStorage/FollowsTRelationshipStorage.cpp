#include "FollowsTRelationshipStorage.h"
#include "models/Relationship/FollowsTRelationship.h"
#include "models/Relationship/RelationshipType.h"
#include "models/Entity/ProcedureEntity.h"
#include "models/Entity/AssignEntity.h"
#include "models/Entity/ReadEntity.h"
#include "models/Entity/CallEntity.h"
#include "models/Entity/IfEntity.h"
#include "models/Entity/WhileEntity.h"
#include "models/Entity/PrintEntity.h"
#include "models/Entity/Entity.h"
#include "models/Entity/DesignEntity.h"

#include "utils.h"

#include "utils.h"
#include "typeinfo"
#include <iostream>

FollowsTRelationshipStorage::FollowsTRelationshipStorage() : RelationshipStorage(),
readToReadForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
readToPrintForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
readToAssignForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
readToCallForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
readToWhileForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
readToIfForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
readToStmtForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
readToStmtBackwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),

printToReadForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
printToPrintForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
printToAssignForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
printToCallForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
printToWhileForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
printToIfForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
printToStmtForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
printToStmtBackwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),

assignToReadForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
assignToPrintForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
assignToAssignForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
assignToCallForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
assignToWhileForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
assignToIfForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
assignToStmtForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
assignToStmtBackwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),

callToReadForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
callToPrintForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
callToAssignForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
callToCallForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
callToWhileForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
callToIfForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
callToStmtForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
callToStmtBackwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),

whileToReadForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
whileToPrintForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
whileToAssignForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
whileToCallForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
whileToWhileForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
whileToIfForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
whileToStmtForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
whileToStmtBackwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),

ifToReadForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
ifToPrintForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
ifToAssignForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
ifToCallForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
ifToWhileForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
ifToIfForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
ifToStmtForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
ifToStmtBackwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),

stmtToReadForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
stmtToPrintForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
stmtToAssignForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
stmtToCallForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
stmtToWhileForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
stmtToIfForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
stmtToStmtForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
stmtToStmtBackwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()) {}

std::unordered_map<std::string, std::unordered_set<std::string>>* FollowsTRelationshipStorage::getStorage(DesignEntity left, DesignEntity right, bool isForward = false) {
	if (left == DesignEntity::READ) {
		if (right == DesignEntity::READ) {
			return &(this->readToReadForwardMap);
		}
		if (right == DesignEntity::PRINT) {
			return &(this->readToPrintForwardMap);
		}
		if (right == DesignEntity::ASSIGN) {
			return &(this->readToAssignForwardMap);
		}
		if (right == DesignEntity::CALL) {
			return &(this->readToCallForwardMap);
		}

		if (right == DesignEntity::WHILE) {
			return &(this->readToWhileForwardMap);
		}
		if (right == DesignEntity::IF) {
			return &(this->readToIfForwardMap);
		}
		if (right == DesignEntity::STMT) {
			return isForward ? &(this->readToStmtForwardMap) : &(this->readToStmtBackwardMap);
		}
	}
	if (left == DesignEntity::PRINT) {
		if (right == DesignEntity::READ) {
			return &(this->printToReadForwardMap);
		}
		if (right == DesignEntity::PRINT) {
			return &(this->printToPrintForwardMap);
		}
		if (right == DesignEntity::ASSIGN) {
			return &(this->printToAssignForwardMap);
		}
		if (right == DesignEntity::CALL) {
			return &(this->printToCallForwardMap);
		}
		if (right == DesignEntity::WHILE) {
			return &(this->printToWhileForwardMap);
		}
		if (right == DesignEntity::IF) {
			return &(this->printToIfForwardMap);
		}
		if (right == DesignEntity::STMT) {
			return isForward ? &(this->printToStmtForwardMap) : &(this->printToStmtBackwardMap);
		}
	}
	if (left == DesignEntity::ASSIGN) {
		if (right == DesignEntity::READ) {
			return &(this->assignToReadForwardMap);
		}
		if (right == DesignEntity::PRINT) {
			return &(this->assignToPrintForwardMap);
		}
		if (right == DesignEntity::ASSIGN) {
			return &(this->assignToAssignForwardMap);
		}
		if (right == DesignEntity::CALL) {
			return &(this->assignToCallForwardMap);
		}

		if (right == DesignEntity::WHILE) {
			return &(this->assignToPrintForwardMap);
		}
		if (right == DesignEntity::IF) {
			return &(this->assignToIfForwardMap);
		}
		if (right == DesignEntity::STMT) {
			return isForward ? &(this->assignToStmtForwardMap) : &(this->assignToStmtBackwardMap);
		}
	}
	if (left == DesignEntity::CALL) {
		if (right == DesignEntity::READ) {
			return &(this->callToReadForwardMap);
		}
		if (right == DesignEntity::PRINT) {
			return &(this->callToPrintForwardMap);
		}
		if (right == DesignEntity::ASSIGN) {
			return &(this->callToAssignForwardMap);
		}
		if (right == DesignEntity::CALL) {
			return &(this->callToCallForwardMap);
		}
		if (right == DesignEntity::WHILE) {
			return &(this->callToWhileForwardMap);
		}
		if (right == DesignEntity::IF) {
			return &(this->callToIfForwardMap);
		}
		if (right == DesignEntity::STMT) {
			return isForward ? &(this->callToStmtForwardMap) : &(this->callToStmtBackwardMap);
		}
	}

	if (left == DesignEntity::WHILE) {
		if (right == DesignEntity::READ) {
			return &(this->whileToReadForwardMap);
		}
		if (right == DesignEntity::PRINT) {
			return &(this->whileToPrintForwardMap);
		}
		if (right == DesignEntity::ASSIGN) {
			return &(this->whileToAssignForwardMap);
		}
		if (right == DesignEntity::CALL) {
			return &(this->whileToCallForwardMap);
		}

		if (right == DesignEntity::WHILE) {
			return &(this->whileToWhileForwardMap);
		}
		if (right == DesignEntity::IF) {
			return &(this->whileToIfForwardMap);
		}
		if (right == DesignEntity::STMT) {
			return isForward ? &(this->whileToStmtForwardMap) : &(this->whileToStmtBackwardMap);
		}
	}
	if (left == DesignEntity::IF) {
		if (right == DesignEntity::READ) {
			return &(this->ifToReadForwardMap);
		}
		if (right == DesignEntity::PRINT) {
			return &(this->ifToPrintForwardMap);
		}
		if (right == DesignEntity::ASSIGN) {
			return &(this->ifToAssignForwardMap);
		}
		if (right == DesignEntity::CALL) {
			return &(this->ifToCallForwardMap);
		}

		if (right == DesignEntity::WHILE) {
			return &(this->ifToWhileForwardMap);
		}
		if (right == DesignEntity::IF) {
			return &(this->ifToIfForwardMap);
		}
		if (right == DesignEntity::STMT) {
			return isForward ? &(this->ifToStmtForwardMap) : &(this->ifToStmtBackwardMap);
		}
	}
	if (left == DesignEntity::STMT) {
		if (right == DesignEntity::READ) {
			return &(this->stmtToReadForwardMap);
		}
		if (right == DesignEntity::PRINT) {
			return &(this->stmtToPrintForwardMap);
		}
		if (right == DesignEntity::ASSIGN) {
			return &(this->stmtToAssignForwardMap);
		}
		if (right == DesignEntity::CALL) {
			return &(this->stmtToCallForwardMap);
		}

		if (right == DesignEntity::WHILE) {
			return &(this->stmtToWhileForwardMap);
		}
		if (right == DesignEntity::IF) {
			return &(this->stmtToIfForwardMap);
		}
		if (right == DesignEntity::STMT) {
			return isForward ? &(this->stmtToStmtForwardMap) : &(this->stmtToStmtBackwardMap);
		}
	}
	return nullptr;
}

bool FollowsTRelationshipStorage::storeRelationship(Relationship* rel) {
	FollowsTRelationship* followsTRelationship = dynamic_cast<FollowsTRelationship*>(rel);

	if (followsTRelationship) {
		Entity* leftEntity = followsTRelationship->getLeftEntity();
		Entity* rightEntity = followsTRelationship->getRightEntity();

		std::string leftValue = leftEntity->getValue();
		std::string rightValue = rightEntity->getValue();

		bool result = false;
		DesignEntity left = RelationshipUtils::entityToDesignEntity(leftEntity);
		DesignEntity right = RelationshipUtils::entityToDesignEntity(rightEntity);

		//Get all the neccessary storage
		std::unordered_map<std::string, std::unordered_set<std::string>>* stmtToStmtForwardStorage = getStorage(DesignEntity::STMT, DesignEntity::STMT, true);
		std::unordered_map<std::string, std::unordered_set<std::string>>* stmtToStmtBackwardStorage = getStorage(DesignEntity::STMT, DesignEntity::STMT);
		std::unordered_map<std::string, std::unordered_set<std::string>>* stmtToRightForwardStorage = getStorage(DesignEntity::STMT, right);
		std::unordered_map<std::string, std::unordered_set<std::string>>* leftToRightForwardStorage = getStorage(left, right);
		std::unordered_map<std::string, std::unordered_set<std::string>>* leftToStmtForwardStorage = getStorage(left, DesignEntity::STMT, true);
		std::unordered_map<std::string, std::unordered_set<std::string>>* leftToStmtBackwardStorage = getStorage(left, DesignEntity::STMT);


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

bool FollowsTRelationshipStorage::getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::FOLLOWS_T) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};

		storage = getStorage(DesignEntity::STMT, DesignEntity::STMT, true);

		if (storage->find(firstArgument.getValue()) == storage->end()) {
			return false;
		}

		std::unordered_set<std::string>* set = &storage->find(firstArgument.getValue())->second;

		return set->find(secondArgument.getValue()) != set->end();
	}
	return false;
}

// Answer Follows(1,a)
std::unordered_set<std::string> FollowsTRelationshipStorage::getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType) {
	if (relType == RelationshipType::FOLLOWS_T) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};

		storage = getStorage(DesignEntity::STMT, returnType, true);

		if (storage == nullptr) {
			return std::unordered_set<std::string>();
		}

		std::string findValue = firstArgument.getValue();

		if (storage->find(findValue) == storage->end()) {
			return std::unordered_set<std::string>();
		}

		return storage->find(findValue)->second;
	}
	return std::unordered_set<std::string>();
}

// Answer Follows(s,2), Follows(w,2), or Follows(if, 2)
std::unordered_set<std::string> FollowsTRelationshipStorage::getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument) {
	if (relType == RelationshipType::FOLLOWS_T) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};

		storage = getStorage(returnType, DesignEntity::STMT, false);

		if (storage == nullptr) {
			return std::unordered_set<std::string>();
		}

		std::string findValue = secondArgument.getValue();

		if (storage->find(findValue) == storage->end()) {
			return std::unordered_set<std::string>();
		}

		return storage->find(findValue)->second;
	}
	return std::unordered_set<std::string>();
}

std::unordered_map<std::string, std::unordered_set<std::string>> FollowsTRelationshipStorage::getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returnType2) {
	if (relType == RelationshipType::FOLLOWS_T) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};

		storage = getStorage(returnType1, returnType2, true);

		if (storage == nullptr) {
			return std::unordered_map<std::string, std::unordered_set<std::string>>();
		}

		return *storage;

	}
	return std::unordered_map<std::string, std::unordered_set<std::string>>();
}
