#include "NextRelationshipStorage.h"
#include "models/Relationship/NextRelationship.h"
#include "models/Relationship/RelationshipType.h"
#include "models/Entity/Entity.h"
#include "models/Entity/DesignEntity.h"

#include "utils.h"

#include "utils.h"
#include "typeinfo"
#include <iostream>

NextRelationshipStorage::NextRelationshipStorage() : RelationshipStorage() {}

std::unordered_map<std::string, std::unordered_set<std::string>>* NextRelationshipStorage::getStorage(DesignEntity left, DesignEntity right,
																									bool isForward = false) {
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

std::unordered_set<std::string> NextRelationshipStorage::getNextForward(std::string c) {
	if (this->stmtToStmtForwardMap.find(c) != this->stmtToStmtForwardMap.end()) {
		return this->stmtToStmtForwardMap.find(c)->second;
	}

	return std::unordered_set<std::string>();
}

std::unordered_set<std::string> NextRelationshipStorage::getNextBackward(std::string c) {
	if (this->stmtToStmtBackwardMap.find(c) != this->stmtToStmtBackwardMap.end()) {
		return this->stmtToStmtBackwardMap.find(c)->second;
	}

	return std::unordered_set<std::string>();
}

bool NextRelationshipStorage::storeRelationship(Relationship* rel) {
	NextRelationship* nextRelationship = dynamic_cast<NextRelationship*>(rel);

	if (nextRelationship) {
		Entity* leftEntity = nextRelationship->getLeftEntity();
		Entity* rightEntity = nextRelationship->getRightEntity();

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

// Answer Next(1, 2)
bool NextRelationshipStorage::getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::NEXT) {
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

// Answer Next(1,a)
std::unordered_set<std::string> NextRelationshipStorage::getRelationshipByFirst(RelationshipType relType, 
																			TokenObject firstArgument, 
																			DesignEntity returnType) {
	if (relType == RelationshipType::NEXT) {
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

// Answer Next(s, 2)
std::unordered_set<std::string> NextRelationshipStorage::getRelationshipBySecond(RelationshipType relType, 
																				DesignEntity returnType, 
																				TokenObject secondArgument) {
	if (relType == RelationshipType::NEXT) {
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

std::unordered_map<std::string, std::unordered_set<std::string>> NextRelationshipStorage::getAllRelationship(RelationshipType relType, 
																											DesignEntity returnType1, 
																											DesignEntity returnType2) {
	if (relType == RelationshipType::NEXT) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};

		storage = getStorage(returnType1, returnType2, true);

		if (storage == nullptr) {
			return std::unordered_map<std::string, std::unordered_set<std::string>>();
		}

		return *storage;

	}
	return std::unordered_map<std::string, std::unordered_set<std::string>>();
}
