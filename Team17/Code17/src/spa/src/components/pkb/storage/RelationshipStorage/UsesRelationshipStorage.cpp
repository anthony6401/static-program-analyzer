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
														stmtForwardStorage(new std::unordered_map<std::string, std::unordered_set<std::string>*>),
														procForwardStorage(new std::unordered_map<std::string, std::unordered_set<std::string>*>),
														procBackwardStorage(new std::unordered_map<std::string, std::unordered_set<std::string>*>),
														assignBackwardStorage(new std::unordered_map<std::string, std::unordered_set<std::string>*>),
														printBackwardStorage(new std::unordered_map<std::string, std::unordered_set<std::string>*>),
														ifBackwardStorage(new std::unordered_map<std::string, std::unordered_set<std::string>*>),
														whileBackwardStorage(new std::unordered_map<std::string, std::unordered_set<std::string>*>) {}

bool UsesRelationshipStorage::storeRelationship(Relationship* rel) {
	UsesRelationship* usesRelationship = dynamic_cast<UsesRelationship*>(rel);
	if (usesRelationship) {
		Entity* leftEntity = usesRelationship->getLeftEntity();
		Entity* rightEntity = usesRelationship->getRightEntity();
		std::string leftValue = leftEntity->getValue();
		std::string rightValue = rightEntity->getValue();

		bool result = false;

		if (typeid(*leftEntity) == typeid(ProcedureEntity)) {
			result = result || insertEntity(this->procForwardStorage, leftValue, rightValue);
			result = result || insertEntity(this->procBackwardStorage, rightValue, leftValue);
		}

		if (typeid(*leftEntity) == typeid(AssignEntity)) {
			result = result || insertEntity(this->stmtForwardStorage, leftValue, rightValue);
			result = result || insertEntity(this->assignBackwardStorage, rightValue, leftValue);
		}

		if (typeid(*leftEntity) == typeid(PrintEntity)) {
			result = result || insertEntity(this->stmtForwardStorage, leftValue, rightValue);
			result = result || insertEntity(this->printBackwardStorage, rightValue, leftValue);
		}

		if (typeid(*leftEntity) == typeid(IfEntity)) {
			result = result || insertEntity(this->stmtForwardStorage, leftValue, rightValue);
			result = result || insertEntity(this->ifBackwardStorage, rightValue, leftValue);
		}

		if (typeid(*leftEntity) == typeid(WhileEntity)) {
			result = result || insertEntity(this->stmtForwardStorage, leftValue, rightValue);
			result = result || insertEntity(this->whileBackwardStorage, rightValue, leftValue);
		}

		return result;
	}

	return false;
}

// To answer Uses(1, "x")
bool UsesRelationshipStorage::getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::USES) {
		std::unordered_map<std::string, std::unordered_set<std::string>*>* storage;
		if (firstArgument.getTokenType() == TokenType::INTEGER) {
			storage = this->stmtForwardStorage;
		} else {
			storage = this->procForwardStorage;
		}
		if (storage->find(firstArgument.getValue()) == storage->end()) {
			return false;
		}

		std::unordered_set<std::string>* set = storage->find(firstArgument.getValue())->second;

		return set->find(secondArgument.getValue()) != set->end();
	}
	return false;
}

std::unordered_set<std::string>* UsesRelationshipStorage::getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, TokenType returnType) {
	if (relType == RelationshipType::USES) {
		std::unordered_map<std::string, std::unordered_set<std::string>*>* storage;
		if (firstArgument.getTokenType() == TokenType::INTEGER) {
			storage = this->stmtForwardStorage;
		}
		else {
			storage = this->procForwardStorage;
		}

		if (storage->find(firstArgument.getValue()) != storage->end()) {
			return storage->find(firstArgument.getValue())->second;
		} else {
			return &std::unordered_set<std::string>();
		}
	}

	return nullptr;
}

std::unordered_set<std::string>* UsesRelationshipStorage::getRelationshipBySecond(RelationshipType relType, TokenType returnType, TokenObject secondArgument) {
	return nullptr;
}

std::unordered_set<std::string>* UsesRelationshipStorage::getAllRelationship(RelationshipType relType, TokenType returnType) {
	return nullptr;
}
