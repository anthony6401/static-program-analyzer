#include "UsesRelationshipStorage.h"
#include "models/Relationship/UsesRelationship.h"
#include "utils.h"

UsesRelationshipStorage::UsesRelationshipStorage() : RelationshipStorage() {}

std::unordered_map<std::string, std::unordered_set<std::string>>* UsesRelationshipStorage::getStorageForward(DesignEntity designEntity) {
	if (designEntity == DesignEntity::PROCEDURE) {
		return &this->procForwardStorage;
	}

	if (designEntity == DesignEntity::ASSIGN) {
		return &this->assignForwardStorage;
	}

	if (designEntity == DesignEntity::PRINT) {
		return  &this->printForwardStorage ;
	}

	if (designEntity == DesignEntity::IF) {
		return &this->ifForwardStorage;
	}

	if (designEntity == DesignEntity::WHILE) {
		return &this->whileForwardStorage;
	}

	if (designEntity == DesignEntity::CALL) {
		return &this->callsForwardStorage;
	}
	return nullptr;
}

std::unordered_map<std::string, std::unordered_set<std::string>>* UsesRelationshipStorage::getStorageBackward(DesignEntity designEntity) {
	if (designEntity == DesignEntity::PROCEDURE) {
		return &this->procBackwardStorage;
	}

	if (designEntity == DesignEntity::ASSIGN) {
		return &this->assignBackwardStorage;
	}

	if (designEntity == DesignEntity::PRINT) {
		return  &this->printBackwardStorage;
	}

	if (designEntity == DesignEntity::IF) {
		return &this->ifBackwardStorage;
	}

	if (designEntity == DesignEntity::WHILE) {
		return &this->whileBackwardStorage;
	}

	if (designEntity == DesignEntity::CALL) {
		return &this->callsBackwardStorage;
	}

	return nullptr;
}

std::unordered_set<std::string>* UsesRelationshipStorage::getSetByFirst(TokenObject firstArgument) {
	if (this->assignForwardStorage.find(firstArgument.getValue()) != this->assignForwardStorage.end()) {
		return &this->assignForwardStorage.find(firstArgument.getValue())->second;
	}

	if (this->printForwardStorage.find(firstArgument.getValue()) != this->printForwardStorage.end()) {
		return &this->printForwardStorage.find(firstArgument.getValue())->second;
	}

	if (this->ifForwardStorage.find(firstArgument.getValue()) != this->ifForwardStorage.end()) {
		return &this->ifForwardStorage.find(firstArgument.getValue())->second;
	}

	if (this->whileForwardStorage.find(firstArgument.getValue()) != this->whileForwardStorage.end()) {
		return &this->whileForwardStorage.find(firstArgument.getValue())->second;
	}

	if (this->procForwardStorage.find(firstArgument.getValue()) != this->procForwardStorage.end()) {
		return &this->procForwardStorage.find(firstArgument.getValue())->second;
	}

	if (this->callsForwardStorage.find(firstArgument.getValue()) != this->callsForwardStorage.end()) {
		return &this->callsForwardStorage.find(firstArgument.getValue())->second;
	}

	return nullptr;
}

// This method is used to concantenate all the set values if the return type is statement
std::unordered_set<std::string>* UsesRelationshipStorage::getSetBySecond(TokenObject secondArgument) {
	std::unordered_set<std::string>* set = new std::unordered_set<std::string>();
	if (this->assignBackwardStorage.find(secondArgument.getValue()) != this->assignBackwardStorage.end()) {
		std::unordered_set<std::string>* temp = &this->assignBackwardStorage.find(secondArgument.getValue())->second;
		set->insert(temp->begin(), temp->end());
	}

	if (this->printBackwardStorage.find(secondArgument.getValue()) != this->printBackwardStorage.end()) {
		std::unordered_set<std::string>* temp = &this->printBackwardStorage.find(secondArgument.getValue())->second;
		set->insert(temp->begin(), temp->end());
	}

	if (this->whileBackwardStorage.find(secondArgument.getValue()) != this->whileBackwardStorage.end()) {
		std::unordered_set<std::string>* temp = &this->whileBackwardStorage.find(secondArgument.getValue())->second;
		set->insert(temp->begin(), temp->end());
	}

	if (this->ifBackwardStorage.find(secondArgument.getValue()) != this->ifBackwardStorage.end()) {
		std::unordered_set<std::string>* temp = &this->ifBackwardStorage.find(secondArgument.getValue())->second;
		set->insert(temp->begin(), temp->end());
	}

	if (this->callsBackwardStorage.find(secondArgument.getValue()) != this->callsBackwardStorage.end()) {
		std::unordered_set<std::string>* temp = &this->callsBackwardStorage.find(secondArgument.getValue())->second;
		set->insert(temp->begin(), temp->end());
	}

	return set;
}

std::unordered_set<std::string> UsesRelationshipStorage::getAllStmt() {
	std::unordered_set<std::string> result;
	for (auto const& assignPair : this->assignForwardStorage) {
		result.insert(assignPair.first);
	}

	for (auto const& printPair : this->printForwardStorage) {
		result.insert(printPair.first);
	}

	for (auto const& whilePair : this->whileForwardStorage) {
		result.insert(whilePair.first);
	}

	for (auto const& ifPair : this->ifForwardStorage) {
		result.insert(ifPair.first);
	}

	for (auto const& callPair : this->callsForwardStorage) {
		result.insert(callPair.first);
	}

	return result;
}

bool UsesRelationshipStorage::storeRelationship(Relationship* rel) {
	UsesRelationship* usesRelationship = dynamic_cast<UsesRelationship*>(rel);
	if (usesRelationship) {
		Entity* leftEntity = usesRelationship->getLeftEntity();
		Entity* rightEntity = usesRelationship->getRightEntity();
		std::string leftValue = leftEntity->getValue();
		std::string rightValue = rightEntity->getValue();

		bool result = false;

		DesignEntity designEntityLeft = RelationshipUtils::entityToDesignEntity(leftEntity);
		std::unordered_map<std::string, std::unordered_set<std::string>>* forwardStorage = getStorageForward(designEntityLeft);
		std::unordered_map<std::string, std::unordered_set<std::string>>* backwardStorage = getStorageBackward(designEntityLeft);

		bool resultOne = RelationshipUtils::insertEntity(forwardStorage, leftValue, rightValue);
		bool resultTwo = RelationshipUtils::insertEntity(backwardStorage, rightValue, leftValue);

		result = result || resultOne || resultTwo;

		return result;
	}

	return false;
}

bool UsesRelationshipStorage::handleConstantConstant(TokenObject firstArgument, TokenObject secondArgument) {
	std::unordered_set<std::string>* set = getSetByFirst(firstArgument);

	if (set == nullptr) {
		return false;
	}

	return set->find(secondArgument.getValue()) != set->end();
}

bool UsesRelationshipStorage::handleConstantWildcard(TokenObject firstArgument) {
	std::unordered_set<std::string>* set = getSetByFirst(firstArgument);

	if (set == nullptr) {
		return false;
	}

	return set->size() != 0;
}

// To answer Uses(1, "x")
bool UsesRelationshipStorage::getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::USES) {
		if ((firstArgument.getTokenType() == TokenType::NAME_WITH_QUOTATION || firstArgument.getTokenType() == TokenType::INTEGER) 
			&& secondArgument.getTokenType() == TokenType::NAME_WITH_QUOTATION) {
			return handleConstantConstant(firstArgument, secondArgument);
		} else if ((firstArgument.getTokenType() == TokenType::NAME_WITH_QUOTATION || firstArgument.getTokenType() == TokenType::INTEGER) 
			&& secondArgument.getTokenType() == TokenType::WILDCARD) {
			return handleConstantWildcard(firstArgument);
		}
	}
	return false;
}

// To answer Uses(1, v)
std::unordered_set<std::string> UsesRelationshipStorage::getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType) {
	if (relType == RelationshipType::USES) {
		std::unordered_set<std::string>* set = getSetByFirst(firstArgument);

		if (set == nullptr) {
			return std::unordered_set<std::string>();
		}

		return *set;
	}

	return std::unordered_set<std::string>();
}

// To answer Uses(s, "x")
std::unordered_set<std::string> UsesRelationshipStorage::getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument) {
	if (relType == RelationshipType::USES) {
		if (returnType == DesignEntity::STMT) {
			return *getSetBySecond(secondArgument);
		}

		std::unordered_map<std::string, std::unordered_set<std::string>>* storage = getStorageBackward(returnType);

		if (storage == nullptr) {
			return std::unordered_set<std::string>();
		}

		if (storage->find(secondArgument.getValue()) != storage->end()) {
			return storage->find(secondArgument.getValue())->second;
		}
		else {
			return std::unordered_set<std::string>();
		}
	}

	return std::unordered_set<std::string>();
}

std::unordered_set<std::string> UsesRelationshipStorage::getRelationshipWithSecondWildcard(RelationshipType relType, DesignEntity returnType) {
	if (relType == RelationshipType::USES) {
		if (returnType == DesignEntity::STMT) {
			return getAllStmt();
		}

		std::unordered_map<std::string, std::unordered_set<std::string>>* storage = getStorageForward(returnType);
		if (storage != nullptr) {
			std::unordered_set<std::string> result;
			for (auto const& pair : *storage) {
				result.insert(pair.first);
			}

			return result;
		}
	}
	return std::unordered_set<std::string>();
}

// To answer Uses(a, v)
std::unordered_map<std::string, std::unordered_set<std::string>> UsesRelationshipStorage::getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returnType2) {
	if (relType == RelationshipType::USES) {
		if (returnType1 == DesignEntity::STMT) {
			std::unordered_map<std::string, std::unordered_set<std::string>> map;

			map.insert(this->assignForwardStorage.begin(), this->assignForwardStorage.end());
			map.insert(this->printForwardStorage.begin(), this->printForwardStorage.end());
			map.insert(this->whileForwardStorage.begin(), this->whileForwardStorage.end());
			map.insert(this->ifForwardStorage.begin(), this->ifForwardStorage.end());
			map.insert(this->callsForwardStorage.begin(), this->callsForwardStorage.end());

			return map;
		}

		std::unordered_map<std::string, std::unordered_set<std::string>>* storage = getStorageForward(returnType1);

		if (storage == nullptr) {
			return std::unordered_map<std::string, std::unordered_set<std::string>>();
		}

		return *storage;

	}

	return std::unordered_map<std::string, std::unordered_set<std::string>>();
}

std::unordered_set<std::string> UsesRelationshipStorage::getUsesForAssign(std::string stmtNum) {
	if (this->assignForwardStorage.find(stmtNum) != this->assignForwardStorage.end()) {
		return this->assignForwardStorage.find(stmtNum)->second;
	}

	return std::unordered_set<std::string>();
}
