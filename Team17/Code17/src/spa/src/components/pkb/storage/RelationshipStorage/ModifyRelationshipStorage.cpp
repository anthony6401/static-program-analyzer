#include "ModifyRelationshipStorage.h"
#include "models/Relationship/ModifyRelationship.h"
#include "models/Entity/ProcedureEntity.h"
#include "models/Entity/AssignEntity.h"
#include "models/Entity/ReadEntity.h"
#include "models/Entity/IfEntity.h"
#include "models/Entity/WhileEntity.h"
#include "utils.h"
#include "typeinfo"

ModifyRelationshipStorage::ModifyRelationshipStorage() : RelationshipStorage(),
stmtForwardStorage(std::unordered_map<std::string, std::unordered_set<std::string>>()),
procForwardStorage(std::unordered_map<std::string, std::unordered_set<std::string>>()),
procBackwardStorage(std::unordered_map<std::string, std::unordered_set<std::string>>()),
assignBackwardStorage(std::unordered_map<std::string, std::unordered_set<std::string>>()),
readBackwardStorage(std::unordered_map<std::string, std::unordered_set<std::string>>()),
ifBackwardStorage(std::unordered_map<std::string, std::unordered_set<std::string>>()),
whileBackwardStorage(std::unordered_map<std::string, std::unordered_set<std::string>>()) {}

bool ModifyRelationshipStorage::storeRelationship(Relationship* rel) {
	ModifyRelationship* modifyRelationship = dynamic_cast<ModifyRelationship*>(rel);
	if (modifyRelationship) {
		Entity* leftEntity = modifyRelationship->getLeftEntity();
		Entity* rightEntity = modifyRelationship->getRightEntity();
		std::string leftValue = leftEntity->getValue();
		std::string rightValue = rightEntity->getValue();

		bool result = false;

		if (typeid(*leftEntity) == typeid(ProcedureEntity)) {
			bool resultOne = Utils::insertEntity(this->procForwardStorage, leftValue, rightValue);
			bool resultTwo = Utils::insertEntity(this->procBackwardStorage, rightValue, leftValue);
			result = result || resultOne || resultTwo;
		}

		if (typeid(*leftEntity) == typeid(AssignEntity)) {
			bool resultOne = Utils::insertEntity(this->stmtForwardStorage, leftValue, rightValue);

			bool resultTwo = Utils::insertEntity(this->assignBackwardStorage, rightValue, leftValue);
			result = result || resultOne || resultTwo;
		}

		if (typeid(*leftEntity) == typeid(ReadEntity)) {
			bool resultOne = Utils::insertEntity(this->stmtForwardStorage, leftValue, rightValue);
			bool resultTwo = Utils::insertEntity(this->readBackwardStorage, rightValue, leftValue);
			result = result || resultOne || resultTwo;
		}

		if (typeid(*leftEntity) == typeid(IfEntity)) {
			bool resultOne = Utils::insertEntity(this->stmtForwardStorage, leftValue, rightValue);
			bool resultTwo = Utils::insertEntity(this->ifBackwardStorage, rightValue, leftValue);
			result = result || resultOne || resultTwo;
		}

		if (typeid(*leftEntity) == typeid(WhileEntity)) {
			bool resultOne = Utils::insertEntity(this->stmtForwardStorage, leftValue, rightValue);
			bool resultTwo = Utils::insertEntity(this->whileBackwardStorage, rightValue, leftValue);
			result = result || resultOne || resultTwo;
		}

		return result;
	}

	return false;
}

// To answer Modify(1, "x")
bool ModifyRelationshipStorage::getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::MODIFIES) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};
		if (firstArgument.getTokenType() == TokenType::INTEGER) {
			storage = &this->stmtForwardStorage;
		}
		else {
			storage = &this->procForwardStorage;
		}

		if (storage->find(firstArgument.getValue()) == storage->end()) {
			return false;
		}

		std::unordered_set<std::string>* set = &storage->find(firstArgument.getValue())->second;

		return set->find(secondArgument.getValue()) != set->end();
	}
	return false;
}

// To answer Modify(1, v)
std::unordered_set<std::string> ModifyRelationshipStorage::getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, TokenType returnType) {
	if (relType == RelationshipType::MODIFIES) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage;
		if (firstArgument.getTokenType() == TokenType::INTEGER) {
			storage = &this->stmtForwardStorage;
		}
		else {
			storage = &this->procForwardStorage;
		}

		if (storage->find(firstArgument.getValue()) != storage->end()) {
			return storage->find(firstArgument.getValue())->second;
		}
		else {
			return std::unordered_set<std::string>();
		}
	}

	return std::unordered_set<std::string>();
}

// To answer Modify(s, 1)
std::unordered_set<std::string> ModifyRelationshipStorage::getRelationshipBySecond(RelationshipType relType, TokenType returnType, TokenObject secondArgument) {
	if (relType == RelationshipType::MODIFIES) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage;
		if (returnType == qps::TokenType::PROCEDURE) {
			storage = &this->procBackwardStorage;
		}
		else if (returnType == qps::TokenType::ASSIGN) {
			storage = &this->assignBackwardStorage;
		}
		else if (returnType == qps::TokenType::READ) {
			storage = &this->readBackwardStorage;
		}
		else if (returnType == qps::TokenType::IF) {
			storage = &this->ifBackwardStorage;
		}
		else if (returnType == qps::TokenType::WHILE) {
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

// To answer Modify(a, v)
std::unordered_set<std::string> ModifyRelationshipStorage::getAllRelationship(RelationshipType relType, TokenType returnType) {
	if (relType == RelationshipType::MODIFIES) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage;
		if (returnType == qps::TokenType::PROCEDURE) {
			storage = &this->procBackwardStorage;
		}
		else if (returnType == qps::TokenType::ASSIGN) {
			storage = &this->assignBackwardStorage;
		}
		else if (returnType == qps::TokenType::READ) {
			storage = &this->readBackwardStorage;
		}
		else if (returnType == qps::TokenType::IF) {
			storage = &this->ifBackwardStorage;
		}
		else if (returnType == qps::TokenType::WHILE) {
			storage = &this->whileBackwardStorage;
		}
		else {
			return std::unordered_set<std::string>();
		}

		std::unordered_set<std::string> result;

		for (auto const& [key, set] : *storage) {
			result.insert(set.begin(), set.end());
		}

		return result;

	}

	return std::unordered_set<std::string>();
}
