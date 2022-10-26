#include "NextRelationshipStorage.h"
#include "models/Relationship/NextRelationship.h"
#include "utils.h"

NextRelationshipStorage::NextRelationshipStorage() : RelationshipStorage() {}

std::unordered_map<std::string, std::unordered_set<std::string>>* NextRelationshipStorage::getReadSpecificEntityStorage(DesignEntity right) {
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
		return &(this->readToStmtForwardMap);
	}

	return nullptr;
}

std::unordered_map<std::string, std::unordered_set<std::string>>* NextRelationshipStorage::getPrintSpecificEntityStorage(DesignEntity right) {
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
		return &(this->printToStmtForwardMap);
	}

	return nullptr;
}

std::unordered_map<std::string, std::unordered_set<std::string>>* NextRelationshipStorage::getAssignSpecificEntityStorage(DesignEntity right) {
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
		return &(this->assignToWhileForwardMap);
	}
	if (right == DesignEntity::IF) {
		return &(this->assignToIfForwardMap);
	}
	if (right == DesignEntity::STMT) {
		return &(this->assignToStmtForwardMap);
	}

	return nullptr;
}

std::unordered_map<std::string, std::unordered_set<std::string>>* NextRelationshipStorage::getCallSpecificEntityStorage(DesignEntity right) {
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
		return &(this->callToStmtForwardMap);
	}

	return nullptr;
}

std::unordered_map<std::string, std::unordered_set<std::string>>* NextRelationshipStorage::getWhileSpecificEntityStorage(DesignEntity right) {
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

std::unordered_map<std::string, std::unordered_set<std::string>>* NextRelationshipStorage::getIfSpecificEntityStorage(DesignEntity right) {
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
		return &(this->ifToStmtForwardMap);
	}

	return nullptr;
}

std::unordered_map<std::string, std::unordered_set<std::string>>* NextRelationshipStorage::getStmtSpecificEntityStorage(DesignEntity right) {
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
		return &(this->stmtToStmtForwardMap);
	}

	return nullptr;
}


std::unordered_map<std::string, std::unordered_set<std::string>>* NextRelationshipStorage::getStorageForward(DesignEntity left, DesignEntity right) {
	if (left == DesignEntity::READ) {
		return getReadSpecificEntityStorage(right);
	}
	if (left == DesignEntity::PRINT) {
		return getPrintSpecificEntityStorage(right);
	}
	if (left == DesignEntity::ASSIGN) {
		return getAssignSpecificEntityStorage(right);
	}
	if (left == DesignEntity::CALL) {
		return getCallSpecificEntityStorage(right);
	}
	if (left == DesignEntity::WHILE) {
		return getWhileSpecificEntityStorage(right);
	}
	if (left == DesignEntity::IF) {
		return getIfSpecificEntityStorage(right);
	}
	if (left == DesignEntity::STMT) {
		return getStmtSpecificEntityStorage(right);
	}
	return nullptr;
}

std::unordered_map<std::string, std::unordered_set<std::string>>* NextRelationshipStorage::getStorageBackward(DesignEntity left) {
	if (left == DesignEntity::READ) {
		return &(this->readToStmtBackwardMap);
	}
	if (left == DesignEntity::PRINT) {
		return &(this->printToStmtBackwardMap);
	}
	if (left == DesignEntity::ASSIGN) {
		return &(this->assignToStmtBackwardMap);
	}
	if (left == DesignEntity::CALL) {
		return &(this->callToStmtBackwardMap);
	}
	if (left == DesignEntity::WHILE) {
		return &(this->whileToStmtBackwardMap);
	}
	if (left == DesignEntity::IF) {
		return &(this->ifToStmtBackwardMap);
	}
	if (left == DesignEntity::STMT) {
		return &(this->stmtToStmtBackwardMap);
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
		bool resultFive = RelationshipUtils::insertEntity(leftToStmtForwardStorage, leftValue, rightValue);
		bool resultSix = RelationshipUtils::insertEntity(leftToStmtBackwardStorage, rightValue, leftValue);

		result = result || resultOne || resultTwo || resultThree || resultFour || resultFive || resultSix;

		return result;
	}
	return false;
}

bool NextRelationshipStorage::handleConstantConstant(TokenObject firstArgument, TokenObject secondArgument) {
	std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};
	storage = getStorageForward(DesignEntity::STMT, DesignEntity::STMT);
	if (storage->find(firstArgument.getValue()) != storage->end()) {
		std::unordered_set<std::string>* set = &storage->find(firstArgument.getValue())->second;
		return set->find(secondArgument.getValue()) != set->end();
	}

	return false;
}

bool NextRelationshipStorage::handleConstantWildcard(TokenObject firstArgument) {
	std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};
	storage = getStorageForward(DesignEntity::STMT, DesignEntity::STMT);
	return storage->find(firstArgument.getValue()) != storage->end();
}

bool NextRelationshipStorage::handleWildcardConstant(TokenObject secondArgument) {
	std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};
	storage = getStorageBackward(DesignEntity::STMT);
	return storage->find(secondArgument.getValue()) != storage->end();
}

bool NextRelationshipStorage::handleWilcardWildcard() {
	std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};
	storage = getStorageForward(DesignEntity::STMT, DesignEntity::STMT);
	return storage->size() != 0;
}

// Answer Next(1, 2)
bool NextRelationshipStorage::getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::NEXT) {
		if (firstArgument.getTokenType() == TokenType::NAME_WITH_QUOTATION && secondArgument.getTokenType() == TokenType::NAME_WITH_QUOTATION) {
			return handleConstantConstant(firstArgument, secondArgument);
		}
		else if (firstArgument.getTokenType() == TokenType::WILDCARD && secondArgument.getTokenType() == TokenType::NAME_WITH_QUOTATION) {
			return handleWildcardConstant(secondArgument);
		}
		else if (firstArgument.getTokenType() == TokenType::NAME_WITH_QUOTATION && secondArgument.getTokenType() == TokenType::WILDCARD) {
			return handleConstantWildcard(firstArgument);
		}
		else if (firstArgument.getTokenType() == TokenType::WILDCARD && secondArgument.getTokenType() == TokenType::WILDCARD) {
			return handleWilcardWildcard();
		}
	}

	return false;
}

// Answer Next(1,a)
std::unordered_set<std::string> NextRelationshipStorage::getRelationshipByFirst(RelationshipType relType, 
																			TokenObject firstArgument, 
																			DesignEntity returnType) {
	if (relType == RelationshipType::NEXT) {
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

// Answer Next(s, 2)
std::unordered_set<std::string> NextRelationshipStorage::getRelationshipBySecond(RelationshipType relType, 
																				DesignEntity returnType, 
																				TokenObject secondArgument) {
	if (relType == RelationshipType::NEXT) {
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

std::unordered_set<std::string> NextRelationshipStorage::getRelationshipWithFirstWilcard(RelationshipType relType, DesignEntity returnType) {
	if (relType == RelationshipType::NEXT) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};

		storage = getStorageBackward(returnType);

		if (storage == nullptr) {
			return std::unordered_set<std::string>();
		}

		std::unordered_set<std::string> result;

		for (auto const& pair : *storage) {
			result.insert(pair.first);
		}

		return result;

	}
	return std::unordered_set<std::string>();
}

std::unordered_set<std::string> NextRelationshipStorage::getRelationshipWithSecondWildcard(RelationshipType relType, DesignEntity returnType) {
	if (relType == RelationshipType::NEXT) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};

		storage = getStorageForward(returnType, DesignEntity::STMT);

		if (storage == nullptr) {
			return std::unordered_set<std::string>();
		}

		std::unordered_set<std::string> result;

		for (auto const& pair : *storage) {
			result.insert(pair.first);
		}

		return result;

	}
	return std::unordered_set<std::string>();
}

std::unordered_map<std::string, std::unordered_set<std::string>> NextRelationshipStorage::getAllRelationship(RelationshipType relType, 
																											DesignEntity returnType1, 
																											DesignEntity returnType2) {
	if (relType == RelationshipType::NEXT) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};

		storage = getStorageForward(returnType1, returnType2);

		if (storage == nullptr) {
			return std::unordered_map<std::string, std::unordered_set<std::string>>();
		}

		return *storage;

	}
	return std::unordered_map<std::string, std::unordered_set<std::string>>();
}
