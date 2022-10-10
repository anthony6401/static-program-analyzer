#include "CallEntityStorage.h"
#include <typeinfo>
#include "models/Entity/CallEntity.h"

CallEntityStorage::CallEntityStorage() : EntityMappingStorage() {}

bool CallEntityStorage::storeEntity(Entity* entity) {
	CallEntity* callEntity = dynamic_cast<CallEntity*>(entity);
	if (callEntity) {
		std::string stmtNum = callEntity->getValue();
		std::string procName = callEntity->getValueName();
		bool result1 = forwardMap.insert({ stmtNum, procName }).second;
		if (backwardMap.find(procName) == backwardMap.end()) {
			backwardMap.insert({ procName, std::unordered_set<std::string> ()});
		}
		std::unordered_set<std::string>* set = &backwardMap.find(procName)->second;
		bool result2 =  set->insert(stmtNum).second;

		return result1 || result2;
	}

	return false;
}

std::unordered_set<std::string> CallEntityStorage::getAllEntity(DesignEntity returnType) {
	if (returnType == DesignEntity::CALL) {
		std::unordered_set<std::string> result;
		for (const auto& [key, _] : forwardMap) {
			result.insert(key);
		}

		return result;
	}
	return std::unordered_set<std::string>();
}

std::string CallEntityStorage::getStatementMapping(std::string& stmtNumber, DesignEntity entityType) {
	if (entityType == DesignEntity::CALL) {
		if (forwardMap.find(stmtNumber) != forwardMap.end()) {
			return forwardMap.find(stmtNumber)->second;
		}
	}

	return std::string();
}

std::unordered_set<std::string> CallEntityStorage::getStatementByName(std::string& name, DesignEntity entityType) {
	if (entityType == DesignEntity::CALL) {
		if (backwardMap.find(name) != backwardMap.end()) {
			return backwardMap.find(name)->second;
		}
	}
	return std::unordered_set<std::string>();
}

std::unordered_set<std::string> CallEntityStorage::getAllName(DesignEntity returnType) {
	if (returnType == DesignEntity::CALL) {
		std::unordered_set<std::string> result;
		for (const auto& [key, _] : backwardMap) {
			result.insert(key);
		}

		return result;
	}
	return std::unordered_set<std::string>();
}
