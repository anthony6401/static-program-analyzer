#include "UsesRelationshipStorage.h"
#include "models/Relationship/UsesRelationship.h"
#include "models/Entity/ProcedureEntity.h"
#include "models/Entity/AssignEntity.h"
#include "models/Entity/PrintEntity.h"
#include "models/Entity/IfEntity.h"
#include "models/Entity/WhileEntity.h"
#include "utils.h"
#include "typeinfo"
#include <iostream>

UsesRelationshipStorage::UsesRelationshipStorage() : RelationshipStorage(), 
														stmtForwardStorage(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														procForwardStorage(std::unordered_map<std::string, std::unordered_set<std::string>>()),
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
			bool resultOne = insertEntity(this->procForwardStorage, leftValue, rightValue);
			bool resultTwo = insertEntity(this->procBackwardStorage, rightValue, leftValue);
			result = result || resultOne || resultTwo;
		}

		if (typeid(*leftEntity) == typeid(AssignEntity)) {
			bool resultOne = insertEntity(this->stmtForwardStorage, leftValue, rightValue);

			bool resultTwo = insertEntity(this->assignBackwardStorage, rightValue, leftValue);
			result = result || resultOne || resultTwo;
		}

		if (typeid(*leftEntity) == typeid(PrintEntity)) {
			bool resultOne = insertEntity(this->stmtForwardStorage, leftValue, rightValue);
			bool resultTwo = insertEntity(this->printBackwardStorage, rightValue, leftValue);
			result = result || resultOne || resultTwo;
		}

		if (typeid(*leftEntity) == typeid(IfEntity)) {
			bool resultOne = insertEntity(this->stmtForwardStorage, leftValue, rightValue);
			bool resultTwo = insertEntity(this->ifBackwardStorage, rightValue, leftValue);
			result = result || resultOne || resultTwo;
		}

		if (typeid(*leftEntity) == typeid(WhileEntity)) {
			bool resultOne = insertEntity(this->stmtForwardStorage, leftValue, rightValue);
			bool resultTwo = insertEntity(this->whileBackwardStorage, rightValue, leftValue);
			result = result || resultOne || resultTwo;
		}

		return result;
	}

	return false;
}

// To answer Uses(1, "x")
bool UsesRelationshipStorage::getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::USES) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};
		if (firstArgument.getTokenType() == TokenType::INTEGER) {
			storage = &this->stmtForwardStorage;
		} else {
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

// To answer Uses(1, v)
std::unordered_set<std::string> UsesRelationshipStorage::getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, TokenType returnType) {
	if (relType == RelationshipType::USES) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};
		if (firstArgument.getTokenType() == TokenType::INTEGER) {
			storage = &this->stmtForwardStorage;
		} else {
			storage = &this->procForwardStorage;
		}

		if (storage->find(firstArgument.getValue()) != storage->end()) {
			return storage->find(firstArgument.getValue())->second;
		} else {
			return std::unordered_set<std::string>();
		}
	}

	return std::unordered_set<std::string>();
}

// To answer Uses(s, 1)
std::unordered_set<std::string> UsesRelationshipStorage::getRelationshipBySecond(RelationshipType relType, TokenType returnType, TokenObject secondArgument) {
	if (relType == RelationshipType::USES) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};
		if (returnType == qps::TokenType::PROCEDURE) {
			storage = &this->procBackwardStorage;
		} else if (returnType == qps::TokenType::ASSIGN) {
			storage = &this->assignBackwardStorage;
		} else if (returnType == qps::TokenType::PRINT) {
			storage = &this->printBackwardStorage;
		} else if (returnType == qps::TokenType::IF) {
			storage = &this->ifBackwardStorage;
		} else if (returnType == qps::TokenType::WHILE) {
			storage = &this->whileBackwardStorage;
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

std::unordered_set<std::string> UsesRelationshipStorage::getAllRelationship(RelationshipType relType, TokenType returnType) {
	if (relType == RelationshipType::USES) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};
		if (returnType == qps::TokenType::PROCEDURE) {
			storage = &this->procBackwardStorage;
		}
		else if (returnType == qps::TokenType::ASSIGN) {
			storage = &this->assignBackwardStorage;
		}
		else if (returnType == qps::TokenType::PRINT) {
			storage = &this->printBackwardStorage;
		}
		else if (returnType == qps::TokenType::IF) {
			storage = &this->ifBackwardStorage;
		}
		else if (returnType == qps::TokenType::WHILE) {
			storage = &this->whileBackwardStorage;
		}

		std::unordered_set<std::string> result;

		for (auto const& [key, set] : *storage) {
			result.insert(set.begin(), set.end());
		}

		return result;
		
	}

	return std::unordered_set<std::string>();
}
