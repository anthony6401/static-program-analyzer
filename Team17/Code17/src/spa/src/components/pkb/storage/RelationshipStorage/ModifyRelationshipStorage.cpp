#include "ModifyRelationshipStorage.h"
#include "models/Relationship/ModifyRelationship.h"
#include "utils.h"

ModifyRelationshipStorage::ModifyRelationshipStorage() : RelationshipStorage() {}


std::unordered_map<std::string, std::unordered_set<std::string>>* ModifyRelationshipStorage::getStorageForward(DesignEntity designEntity) {
	if (designEntity == DesignEntity::PROCEDURE) {
		return &this->procForwardStorage;
	}

	if (designEntity == DesignEntity::ASSIGN) {
		return  &this->assignForwardStorage;
	}

	if (designEntity == DesignEntity::READ) {
		return &this->readForwardStorage;
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

std::unordered_map<std::string, std::unordered_set<std::string>>* ModifyRelationshipStorage::getStorageBackward(DesignEntity designEntity) {
	if (designEntity == DesignEntity::PROCEDURE) {
		return &this->procBackwardStorage;
	}

	if (designEntity == DesignEntity::ASSIGN) {
		return  &this->assignBackwardStorage;
	}

	if (designEntity == DesignEntity::READ) {
		return &this->readBackwardStorage;
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

std::unordered_set<std::string>* ModifyRelationshipStorage::getSetByFirst(TokenObject firstArgument) {
	if (this->assignForwardStorage.find(firstArgument.getValue()) != this->assignForwardStorage.end()) {
		return &this->assignForwardStorage.find(firstArgument.getValue())->second;
	}
	
	if (this->readForwardStorage.find(firstArgument.getValue()) != this->readForwardStorage.end()) {
		return &this->readForwardStorage.find(firstArgument.getValue())->second;
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
std::unordered_set<std::string>* ModifyRelationshipStorage::getSetBySecond(TokenObject secondArgument) {
	std::unordered_set<std::string>* set = new std::unordered_set<std::string>();
	if (this->assignBackwardStorage.find(secondArgument.getValue()) != this->assignBackwardStorage.end()) {
		std::unordered_set<std::string>* temp = &this->assignBackwardStorage.find(secondArgument.getValue())->second;
		set->insert(temp->begin(), temp->end());
	}

	if (this->readBackwardStorage.find(secondArgument.getValue()) != this->readBackwardStorage.end()) {
		std::unordered_set<std::string>* temp = &this->readBackwardStorage.find(secondArgument.getValue())->second;
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

bool ModifyRelationshipStorage::storeRelationship(Relationship* rel) {
	ModifyRelationship* modifyRelationship = dynamic_cast<ModifyRelationship*>(rel);
	if (modifyRelationship) {
		Entity* leftEntity = modifyRelationship->getLeftEntity();
		Entity* rightEntity = modifyRelationship->getRightEntity();
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

// To answer Modify(1, "x")
bool ModifyRelationshipStorage::getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::MODIFIES) {
		std::unordered_set<std::string>* set = getSetByFirst(firstArgument);

		if (set == nullptr) {
			return false;
		}

		return set->find(secondArgument.getValue()) != set->end();

	}
	return false;
}

// To answer Modify(1, v)
std::unordered_set<std::string> ModifyRelationshipStorage::getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType) {
	if (relType == RelationshipType::MODIFIES) {
		std::unordered_set<std::string>* set = getSetByFirst(firstArgument);

		if (set == nullptr) {
			return std::unordered_set<std::string>();
		}

		return *set;
	}

	return std::unordered_set<std::string>();
}

// To answer Modify(s, "x")
std::unordered_set<std::string> ModifyRelationshipStorage::getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument) {
	if (relType == RelationshipType::MODIFIES) {
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

// To answer Modify(a, v)
std::unordered_map<std::string, std::unordered_set<std::string>> ModifyRelationshipStorage::getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returnType2) {
	if (relType == RelationshipType::MODIFIES) {
		if (returnType1 == DesignEntity::STMT) {
			std::unordered_map<std::string, std::unordered_set<std::string>> map;

			map.insert(this->assignForwardStorage.begin(), this->assignForwardStorage.end());
			map.insert(this->readForwardStorage.begin(), this->readForwardStorage.end());
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

std::unordered_set<std::string> ModifyRelationshipStorage::getModifiesForAssign(TokenObject stmtArgument) {
	if (this->assignForwardStorage.find(stmtArgument.getValue()) != this->assignForwardStorage.end()) {
		return this->assignForwardStorage.find(stmtArgument.getValue())->second;
	}

	return std::unordered_set<std::string>();
}

std::unordered_set<std::string> ModifyRelationshipStorage::getModifiesForAffects(std::string stmt) {
	if (this->assignForwardStorage.find(stmt) != this->assignForwardStorage.end()) {
		return this->assignForwardStorage.find(stmt)->second;
	}

	if (this->readForwardStorage.find(stmt) != this->readForwardStorage.end()) {
		return this->readForwardStorage.find(stmt)->second;
	}

	if (this->callsForwardStorage.find(stmt) != this->callsForwardStorage.end()) {
		return this->callsForwardStorage.find(stmt)->second;
	}

	return std::unordered_set<std::string>();
}
