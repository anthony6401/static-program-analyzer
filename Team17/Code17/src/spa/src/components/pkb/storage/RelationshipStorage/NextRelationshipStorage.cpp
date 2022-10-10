#include "NextRelationshipStorage.h"
#include "models/Relationship/NextRelationship.h"
#include "models/Relationship/RelationshipType.h"
#include "models/Entity/Entity.h"
#include "models/Entity/DesignEntity.h"

#include "utils.h"

#include "utils.h"
#include "typeinfo"
#include <iostream>

NextRelationshipStorage::NextRelationshipStorage() : RelationshipStorage(),
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
		return &(this->assignToPrintForwardMap);
	}
	if (right == DesignEntity::IF) {
		return &(this->assignToIfForwardMap);
	}
	if (right == DesignEntity::STMT) {
		return &(this->assignToStmtForwardMap);
	}
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

// DFS search to answer Next* queries with 2 integer values
bool NextRelationshipStorage::DFSNextTForward(std::string curr, std::string target, std::unordered_set<std::string>& visited) {
	visited.insert(curr);

	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator neighboursIterator = this->stmtToStmtForwardMap.find(curr);

	if (neighboursIterator != this->stmtToStmtForwardMap.end()) {
		for (std::string neighbour : neighboursIterator->second) {
			if (target == neighbour || (visited.find(neighbour) == visited.end() && DFSNextTForward(neighbour, target, visited))) {
				return true;
			}
		}
	}

	return false;
}

// DFS search to answer Next* queries with synonyms
void NextRelationshipStorage::DFSNextTForwardWithSynonym(std::string curr, std::unordered_set<std::string>& visited,
													std::unordered_set<std::string>& result, std::unordered_set<std::string>& filter,
													std::unordered_map<std::string, std::unordered_set<std::string>>* storage) {
	visited.insert(curr);

	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator neighboursIterator = storage->find(curr);

	if (neighboursIterator != storage->end()) {
		for (std::string neighbour : neighboursIterator->second) {
			std::unordered_set<std::string>::const_iterator exist = visited.find(neighbour);
			if (filter.find(neighbour) != filter.end()) {
				result.insert(neighbour);
			}
			if (exist == visited.end()) {
				DFSNextTForwardWithSynonym(neighbour, visited, result, filter, storage);
			}
		}
	}
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

// Answer Next(1, 2) and Next*(1, 2)
bool NextRelationshipStorage::getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::NEXT) {
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

// Handle Next* Relationship for 2 integer values i.e. Next(1, 2)
bool NextRelationshipStorage::getNextTRelationship(TokenObject firstArgument, TokenObject secondArgument) {
	std::unordered_set<std::string> visited;
	return DFSNextTForward(firstArgument.getValue(), secondArgument.getValue(), visited);

}

// Answer Next(1,a) and Next*(1,a)
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

// Handle Next* Relationship for first argument integer value and second argument synonym i.e. Next*(1, a)
std::unordered_set<std::string> NextRelationshipStorage::getNextTRelationshipByFirst(TokenObject firstArgument, std::unordered_set<std::string>& filter) {
	std::unordered_set<std::string> visited;
	std::unordered_set<std::string> result;
	std::unordered_map<std::string, std::unordered_set<std::string>>* storage = getStorageForward(DesignEntity::STMT, DesignEntity::STMT);
	DFSNextTForwardWithSynonym(firstArgument.getValue(), visited, result, filter, storage);
	return result;
}

// Answer Next(s, 2) and Next*(s, 2)
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

std::unordered_set<std::string> NextRelationshipStorage::getNextTRelationshipBySecond(TokenObject secondArgument, std::unordered_set<std::string>& filter) {
	std::unordered_set<std::string> visited;
	std::unordered_set<std::string> result;
	std::unordered_map<std::string, std::unordered_set<std::string>>* storage = getStorageBackward(DesignEntity::STMT);
	DFSNextTForwardWithSynonym(secondArgument.getValue(), visited, result, filter, storage);
	return result;
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

std::unordered_map<std::string, std::unordered_set<std::string>> NextRelationshipStorage::getAllNextTRelationship(DesignEntity returnType1, 
																												std::unordered_set<std::string>& filter) {
	std::unordered_map<std::string, std::unordered_set<std::string>> result_map;
	std::unordered_map<std::string, std::unordered_set<std::string>>* storageForFilter = getStorageForward(returnType1, DesignEntity::STMT);
	std::unordered_map<std::string, std::unordered_set<std::string>>* DFSstorage = getStorageForward(DesignEntity::STMT, DesignEntity::STMT);
	for (std::unordered_map<std::string, std::unordered_set<std::string>>::iterator it = storageForFilter->begin(); it != storageForFilter->end(); ++it) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> result;
		std::string start = it->first;
		DFSNextTForwardWithSynonym(start, visited, result, filter, DFSstorage);
		if (result.size() != 0) {
			result_map[start] = result;
		}
	}

	return result_map;
}
