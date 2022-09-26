#include "ParentTRelationshipStorage.h"
#include "models/Relationship/ParentTRelationship.h"
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

#include "typeinfo"
#include <iostream>


ParentTRelationshipStorage::ParentTRelationshipStorage() : RelationshipStorage(),
															ifToReadForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															ifToPrintForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															ifToAssignForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															ifToCallForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															ifToWhileForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															ifToIfForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															ifToStmtForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															ifToStmtBackwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															whileToReadForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															whileToPrintForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															whileToAssignForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															whileToCallForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															whileToWhileForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															whileToIfForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															whileToStmtForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															whileToStmtBackwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															stmtToReadForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															stmtToPrintForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															stmtToAssignForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															stmtToCallForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															stmtToWhileForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															stmtToIfForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															stmtToStmtForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
															stmtToStmtBackwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()) {}


std::unordered_map<std::string, std::unordered_set<std::string>>* ParentTRelationshipStorage::getStorage(DesignEntity left, DesignEntity right, bool isForward) {
	if (left == DesignEntity::WHILE) {
		//Store Stmt -> stmt forward and backward

		if (right == DesignEntity::READ) {
			return &(this->whileToReadForwardMap);
		}

		else if (right == DesignEntity::PRINT) {
			return &(this->whileToPrintForwardMap);
		}
		else if (right == DesignEntity::ASSIGN) {
			return &(this->whileToAssignForwardMap);
		}
		else if (right == DesignEntity::CALL) {
			return &(this->whileToCallForwardMap);
		}
		else if (right == DesignEntity::WHILE) {
			return &(this->whileToWhileForwardMap);
		}
		else if (right == DesignEntity::IF) {
			return &(this->whileToIfForwardMap);
		}
		else if (right == DesignEntity::STMT) {
			return isForward ? &(this->whileToStmtForwardMap) : &(this->whileToStmtBackwardMap);
		}
	}
	else if (left == DesignEntity::IF) {
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
			return isForward ? &(this->ifToStmtForwardMap) : &(this->ifToStmtBackwardMap);
		}
	}
	else if (left == DesignEntity::STMT) {
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
			return isForward ? &(this->stmtToStmtForwardMap) : &(this->stmtToStmtBackwardMap);
		}
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
		std::unordered_map<std::string, std::unordered_set<std::string>>* stmtToStmtForwardStorage = getStorage(DesignEntity::STMT, DesignEntity::STMT, true);
		std::unordered_map<std::string, std::unordered_set<std::string>>* stmtToStmtBackwardStorage = getStorage(DesignEntity::STMT, DesignEntity::STMT);
		std::unordered_map<std::string, std::unordered_set<std::string>>* stmtToRightForwardStorage = getStorage(DesignEntity::STMT, right);
		std::unordered_map<std::string, std::unordered_set<std::string>>* leftToRightForwardStorage = getStorage(left, right);
		std::unordered_map<std::string, std::unordered_set<std::string>>* leftToStmtForwardStorage = getStorage(left, DesignEntity::STMT, true);
		std::unordered_map<std::string, std::unordered_set<std::string>>* leftToStmtBackwardStorage = getStorage(left, DesignEntity::STMT);

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

		storage = getStorage(DesignEntity::STMT, DesignEntity::STMT, true);

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

// Answer ParentT(s,2), ParentT(w,2), or ParentT(if, 2)
std::unordered_set<std::string> ParentTRelationshipStorage::getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument) {
	if (relType == RelationshipType::PARENT_T) {
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

//Answer ParentT(s,w),...., ParentT(w,a),..., ParentT(if, a)
std::unordered_map<std::string, std::unordered_set<std::string>> ParentTRelationshipStorage::getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returnType2) {
	if (relType == RelationshipType::PARENT_T) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};

		storage = getStorage(returnType1, returnType2, true);

		if (storage == nullptr) {
			return std::unordered_map<std::string, std::unordered_set<std::string>>();
		}

		return *storage;

	}
	return std::unordered_map<std::string, std::unordered_set<std::string>>();
}
