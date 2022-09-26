#include "UsesRelationshipStorage.h"
#include "models/Relationship/UsesRelationship.h"
#include "models/Entity/ProcedureEntity.h"
#include "models/Entity/AssignEntity.h"
#include "models/Entity/PrintEntity.h"
#include "models/Entity/IfEntity.h"
#include "models/Entity/WhileEntity.h"
#include "utils.h"
#include "typeinfo"

UsesRelationshipStorage::UsesRelationshipStorage() : RelationshipStorage(),
													procForwardStorage(std::unordered_map<std::string, std::unordered_set<std::string>>()),
													assignForwardStorage(std::unordered_map<std::string, std::unordered_set<std::string>>()),
													printForwardStorage(std::unordered_map<std::string, std::unordered_set<std::string>>()),
													ifForwardStorage(std::unordered_map<std::string, std::unordered_set<std::string>>()),
													whileForwardStorage(std::unordered_map<std::string, std::unordered_set<std::string>>()),
													procBackwardStorage(std::unordered_map<std::string, std::unordered_set<std::string>>()),
													assignBackwardStorage(std::unordered_map<std::string, std::unordered_set<std::string>>()),
													printBackwardStorage(std::unordered_map<std::string, std::unordered_set<std::string>>()),
													ifBackwardStorage(std::unordered_map<std::string, std::unordered_set<std::string>>()),
													whileBackwardStorage(std::unordered_map<std::string, std::unordered_set<std::string>>()) {}

std::unordered_map<std::string, std::unordered_set<std::string>>* UsesRelationshipStorage::getRelationshipMap(DesignEntity designEntity, bool isForward) {
	if (designEntity == DesignEntity::PROCEDURE) {
		return isForward ? &this->procForwardStorage : &this->procBackwardStorage;
	}

	if (designEntity == DesignEntity::ASSIGN) {
		return isForward ? &this->assignForwardStorage : &this->assignBackwardStorage;
	}

	if (designEntity == DesignEntity::PRINT) {
		return isForward ? &this->printForwardStorage : &this->printBackwardStorage;
	}

	if (designEntity == DesignEntity::IF) {
		return isForward ? &this->ifForwardStorage : &this->ifBackwardStorage;
	}

	if (designEntity == DesignEntity::WHILE) {
		return isForward ? &this->whileForwardStorage : &this->whileBackwardStorage;
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

	return set;
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
		std::unordered_map<std::string, std::unordered_set<std::string>>* forwardStorage = getRelationshipMap(designEntityLeft, true);
		std::unordered_map<std::string, std::unordered_set<std::string>>* backwardStorage = getRelationshipMap(designEntityLeft, false);

		bool resultOne = RelationshipUtils::insertEntity(forwardStorage, leftValue, rightValue);
		bool resultTwo = RelationshipUtils::insertEntity(backwardStorage, rightValue, leftValue);

		result = result || resultOne || resultTwo;

		return result;
	}

	return false;
}

// To answer Uses(1, "x")
bool UsesRelationshipStorage::getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::USES) {
		std::unordered_set<std::string>* set = getSetByFirst(firstArgument);

		if (set == nullptr) {
			return false;
		}

		return set->find(secondArgument.getValue()) != set->end();
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

		std::unordered_map<std::string, std::unordered_set<std::string>>* storage = getRelationshipMap(returnType, false);

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

// To answer Uses(a, v)
std::unordered_map<std::string, std::unordered_set<std::string>> UsesRelationshipStorage::getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returnType2) {
	if (relType == RelationshipType::USES) {
		if (returnType1 == DesignEntity::STMT) {
			std::unordered_map<std::string, std::unordered_set<std::string>> map;

			map.insert(this->assignForwardStorage.begin(), this->assignForwardStorage.end());
			map.insert(this->printForwardStorage.begin(), this->printForwardStorage.end());
			map.insert(this->whileForwardStorage.begin(), this->whileForwardStorage.end());
			map.insert(this->ifForwardStorage.begin(), this->ifForwardStorage.end());

			return map;
		}

		std::unordered_map<std::string, std::unordered_set<std::string>>* storage = getRelationshipMap(returnType1, true);

		if (storage == nullptr) {
			return std::unordered_map<std::string, std::unordered_set<std::string>>();
		}

		return *storage;

	}

	return std::unordered_map<std::string, std::unordered_set<std::string>>();
}
