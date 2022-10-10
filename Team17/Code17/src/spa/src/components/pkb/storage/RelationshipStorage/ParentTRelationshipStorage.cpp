#include "ParentTRelationshipStorage.h"
#include "models/Relationship/ParentTRelationship.h"
#include "utils.h"

ParentTRelationshipStorage::ParentTRelationshipStorage() : RelationshipStorage() {}


std::unordered_map<std::string, std::unordered_set<std::string>>* ParentTRelationshipStorage::getWhileToSpecificStorage(DesignEntity right) {
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
		return &(this->whileToStmtForwardMap);
	}

	return nullptr;
}

std::unordered_map<std::string, std::unordered_set<std::string>>* ParentTRelationshipStorage::getIfToSpecificStorage(DesignEntity right) {
	if (right == DesignEntity::READ) {
		return &(this->ifToReadForwardMap);
	}

	else if (right == DesignEntity::PRINT) {
		return &(this->ifToPrintForwardMap);
	}
	else if (right == DesignEntity::ASSIGN) {
		return &(this->ifToAssignForwardMap);
	}
	else if (right == DesignEntity::CALL) {
		return &(this->ifToCallForwardMap);
	}
	else if (right == DesignEntity::WHILE) {
		return &(this->ifToWhileForwardMap);
	}
	else if (right == DesignEntity::IF) {
		return &(this->ifToIfForwardMap);
	}
	else if (right == DesignEntity::STMT) {
		return &(this->ifToStmtForwardMap);
	}

	return nullptr;
}

std::unordered_map<std::string, std::unordered_set<std::string>>* ParentTRelationshipStorage::getStmtToSpecificStorage(DesignEntity right) {
	if (right == DesignEntity::READ) {
		return &(this->stmtToReadForwardMap);
	}

	else if (right == DesignEntity::PRINT) {
		return &(this->stmtToPrintForwardMap);
	}
	else if (right == DesignEntity::ASSIGN) {
		return &(this->stmtToAssignForwardMap);
	}
	else if (right == DesignEntity::CALL) {
		return &(this->stmtToCallForwardMap);
	}
	else if (right == DesignEntity::WHILE) {
		return &(this->stmtToWhileForwardMap);
	}
	else if (right == DesignEntity::IF) {
		return &(this->stmtToIfForwardMap);
	}
	else if (right == DesignEntity::STMT) {
		return &(this->stmtToStmtForwardMap);
	}

	return nullptr;
}

std::unordered_map<std::string, std::unordered_set<std::string>>* ParentTRelationshipStorage::getStorageForward(DesignEntity left, DesignEntity right) {
	if (left == DesignEntity::WHILE) {
		//Store Stmt -> stmt forward and backward
		return getWhileToSpecificStorage(right);

	}
	else if (left == DesignEntity::IF) {
		return getIfToSpecificStorage(right);
	}
	else if (left == DesignEntity::STMT) {
		return getStmtToSpecificStorage(right);
	}
	return nullptr;
}

std::unordered_map<std::string, std::unordered_set<std::string>>* ParentTRelationshipStorage::getStorageBackward(DesignEntity left) {
	if (left == DesignEntity::WHILE) {
		//Store Stmt -> stmt forward and backward
		return &(this->whileToStmtBackwardMap);

	}
	else if (left == DesignEntity::IF) {
		return &(this->ifToStmtBackwardMap);
	}
	else if (left == DesignEntity::STMT) {
		return &(this->stmtToStmtBackwardMap);
	}
	return nullptr;
}


bool ParentTRelationshipStorage::storeRelationship(Relationship* rel) {
	ParentTRelationship* parentTRelationship = dynamic_cast<ParentTRelationship*>(rel);

	if (parentTRelationship) {
		Entity* leftEntity = parentTRelationship->getLeftEntity();
		Entity* rightEntity = parentTRelationship->getRightEntity();

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

// Answer ParentT(1,2)
bool ParentTRelationshipStorage::getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::PARENT_T) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};

		storage = getStorageForward(DesignEntity::STMT, DesignEntity::STMT);

		if (storage->find(firstArgument.getValue()) == storage->end()) {
			return false;
		}

		std::unordered_set<std::string>* set = &storage->find(firstArgument.getValue())->second;

		return set->find(secondArgument.getValue()) != set->end();
	}
	return false;
}

// Answer ParentT(1,a)
std::unordered_set<std::string> ParentTRelationshipStorage::getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType) {
	if (relType == RelationshipType::PARENT_T) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};

		storage = getStorageForward(DesignEntity::STMT, returnType);

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

// Answer ParentT(s,2), ParentT(w,2), or ParentT(if, 2)
std::unordered_set<std::string> ParentTRelationshipStorage::getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument) {
	if (relType == RelationshipType::PARENT_T) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};

		storage = getStorageBackward(returnType);

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

//Answer ParentT(s,w),...., ParentT(w,a),..., ParentT(if, a)
std::unordered_map<std::string, std::unordered_set<std::string>> ParentTRelationshipStorage::getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returnType2) {
	if (relType == RelationshipType::PARENT_T) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};

		storage = getStorageForward(returnType1, returnType2);

		if (storage == nullptr) {
			return std::unordered_map<std::string, std::unordered_set<std::string>>();
		}

		return *storage;

	}
	return std::unordered_map<std::string, std::unordered_set<std::string>>();
}
