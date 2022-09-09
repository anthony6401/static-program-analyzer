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

bool UsesRelationshipStorage::storeRelationship(Relationship* rel) {
	UsesRelationship* usesRelationship = dynamic_cast<UsesRelationship*>(rel);
	if (usesRelationship) {
		Entity* leftEntity = usesRelationship->getLeftEntity();
		Entity* rightEntity = usesRelationship->getRightEntity();
		std::string leftValue = leftEntity->getValue();
		std::string rightValue = rightEntity->getValue();

		bool result = false;

		if (typeid(*leftEntity) == typeid(ProcedureEntity)) {
			bool resultOne = Utils::insertEntity(this->procForwardStorage, leftValue, rightValue);
			bool resultTwo = Utils::insertEntity(this->procBackwardStorage, rightValue, leftValue);
			result = result || resultOne || resultTwo;
		}

		if (typeid(*leftEntity) == typeid(AssignEntity)) {
			bool resultOne = Utils::insertEntity(this->assignForwardStorage, leftValue, rightValue);
			bool resultTwo = Utils::insertEntity(this->assignBackwardStorage, rightValue, leftValue);
			result = result || resultOne || resultTwo;
		}

		if (typeid(*leftEntity) == typeid(PrintEntity)) {
			bool resultOne = Utils::insertEntity(this->printForwardStorage, leftValue, rightValue);
			bool resultTwo = Utils::insertEntity(this->printBackwardStorage, rightValue, leftValue);
			result = result || resultOne || resultTwo;
		}

		if (typeid(*leftEntity) == typeid(IfEntity)) {
			bool resultOne = Utils::insertEntity(this->ifForwardStorage, leftValue, rightValue);
			bool resultTwo = Utils::insertEntity(this->ifBackwardStorage, rightValue, leftValue);
			result = result || resultOne || resultTwo;
		}

		if (typeid(*leftEntity) == typeid(WhileEntity)) {
			bool resultOne = Utils::insertEntity(this->whileForwardStorage, leftValue, rightValue);
			bool resultTwo = Utils::insertEntity(this->whileBackwardStorage, rightValue, leftValue);
			result = result || resultOne || resultTwo;
		}

		return result;
	}

	return false;
}

// To answer Uses(1, "x")
bool UsesRelationshipStorage::getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::USES) {
		std::unordered_set<std::string>* set;
		if (firstArgument.getTokenType() == TokenType::INTEGER) {
			if (this->assignForwardStorage.find(firstArgument.getValue()) != this->assignForwardStorage.end()) {
				set = &this->assignForwardStorage.find(firstArgument.getValue())->second;
			}
			else if (this->printForwardStorage.find(firstArgument.getValue()) != this->printForwardStorage.end()) {
				set = &this->printForwardStorage.find(firstArgument.getValue())->second;
			}
			else if (this->ifForwardStorage.find(firstArgument.getValue()) != this->ifForwardStorage.end()) {
				set = &this->ifForwardStorage.find(firstArgument.getValue())->second;
			}
			else if (this->whileForwardStorage.find(firstArgument.getValue()) != this->whileForwardStorage.end()) {
				set = &this->whileForwardStorage.find(firstArgument.getValue())->second;
			}
			else {
				return false;
			}

		}
		else if (firstArgument.getTokenType() == TokenType::NAME_WITH_QUOTATION) {
			if (this->procForwardStorage.find(firstArgument.getValue()) != this->procForwardStorage.end()) {
				set = &this->procForwardStorage.find(firstArgument.getValue())->second;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}

		return set->find(secondArgument.getValue()) != set->end();
	}
	return false;
}

// To answer Uses(1, v)
std::unordered_set<std::string> UsesRelationshipStorage::getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType) {
	if (relType == RelationshipType::USES) {
		if (firstArgument.getTokenType() == TokenType::INTEGER) {
			if (this->assignForwardStorage.find(firstArgument.getValue()) != this->assignForwardStorage.end()) {
				return this->assignForwardStorage.find(firstArgument.getValue())->second;
			}
			else if (this->printForwardStorage.find(firstArgument.getValue()) != this->printForwardStorage.end()) {
				return this->printForwardStorage.find(firstArgument.getValue())->second;
			}
			else if (this->ifForwardStorage.find(firstArgument.getValue()) != this->ifForwardStorage.end()) {
				return this->ifForwardStorage.find(firstArgument.getValue())->second;
			}
			else if (this->whileForwardStorage.find(firstArgument.getValue()) != this->whileForwardStorage.end()) {
				return this->whileForwardStorage.find(firstArgument.getValue())->second;
			}
		}
		else if (firstArgument.getTokenType() == TokenType::NAME_WITH_QUOTATION) {
			if (this->procForwardStorage.find(firstArgument.getValue()) != this->procForwardStorage.end()) {
				return this->procForwardStorage.find(firstArgument.getValue())->second;
			}
		}

		return std::unordered_set<std::string>();
	}

	return std::unordered_set<std::string>();
}

// To answer Uses(s, "x")
std::unordered_set<std::string> UsesRelationshipStorage::getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument) {
	if (relType == RelationshipType::USES) {
		if (returnType == DesignEntity::STMT) {
			std::unordered_set<std::string> set;
			if (this->assignBackwardStorage.find(secondArgument.getValue()) != this->assignBackwardStorage.end()) {
				std::unordered_set<std::string>* temp = &this->assignBackwardStorage.find(secondArgument.getValue())->second;
				set.insert(temp->begin(), temp->end());
			}

			if (this->printBackwardStorage.find(secondArgument.getValue()) != this->printBackwardStorage.end()) {
				std::unordered_set<std::string>* temp = &this->printBackwardStorage.find(secondArgument.getValue())->second;
				set.insert(temp->begin(), temp->end());
			}

			if (this->whileBackwardStorage.find(secondArgument.getValue()) != this->whileBackwardStorage.end()) {
				std::unordered_set<std::string>* temp = &this->whileBackwardStorage.find(secondArgument.getValue())->second;
				set.insert(temp->begin(), temp->end());
			}

			if (this->ifBackwardStorage.find(secondArgument.getValue()) != this->ifBackwardStorage.end()) {
				std::unordered_set<std::string>* temp = &this->ifBackwardStorage.find(secondArgument.getValue())->second;
				set.insert(temp->begin(), temp->end());
			}

			return set;
		}

		std::unordered_map<std::string, std::unordered_set<std::string>>* storage;
		if (returnType == DesignEntity::PROCEDURE) {
			storage = &this->procBackwardStorage;
		}
		else if (returnType == DesignEntity::ASSIGN) {
			storage = &this->assignBackwardStorage;
		}
		else if (returnType == DesignEntity::PRINT) {
			storage = &this->printBackwardStorage;
		}
		else if (returnType == DesignEntity::IF) {
			storage = &this->ifBackwardStorage;
		}
		else if (returnType == DesignEntity::WHILE) {
			storage = &this->whileBackwardStorage;
		}
		else {
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

		if (returnType1 == DesignEntity::PROCEDURE) {
			return this->procForwardStorage;
		}
		else if (returnType1 == DesignEntity::ASSIGN) {
			return this->assignForwardStorage;
		}
		else if (returnType1 == DesignEntity::PRINT) {
			return this->printForwardStorage;
		}
		else if (returnType1 == DesignEntity::IF) {
			return this->ifForwardStorage;
		}
		else if (returnType1 == DesignEntity::WHILE) {
			return this->whileForwardStorage;
		}
		else {
			return std::unordered_map<std::string, std::unordered_set<std::string>>();
		}

	}

	return std::unordered_map<std::string, std::unordered_set<std::string>>();
}
