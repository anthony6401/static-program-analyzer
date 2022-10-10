#include "ReadEntityStorage.h"
#include <typeinfo>
#include "models/Entity/ReadEntity.h"

ReadEntityStorage::ReadEntityStorage() : EntityMappingStorage() {}

bool ReadEntityStorage::storeEntity(Entity* entity) {
	ReadEntity* readEntity = dynamic_cast<ReadEntity*>(entity);
	if (readEntity) {
		std::string stmtNum = readEntity->getValue();
		std::string varName = readEntity->getValueName();
		bool result1 = forwardMap.insert({ stmtNum, varName }).second;
		if (backwardMap.find(varName) == backwardMap.end()) {
			backwardMap.insert({ varName, std::unordered_set<std::string>() });
		}
		std::unordered_set<std::string>* set = &backwardMap.find(varName)->second;
		bool result2 = set->insert(stmtNum).second;

		return result1 || result2;
	}

	return false;
}

std::unordered_set<std::string> ReadEntityStorage::getAllEntity(DesignEntity returnType) {
	if (returnType == DesignEntity::READ) {
		std::unordered_set<std::string> result;
		for (const auto& [key, _] : forwardMap) {
			result.insert(key);
		}

		return result;
	}
	return std::unordered_set<std::string>();
}

std::string ReadEntityStorage::getStatementMapping(std::string& stmtNumber, DesignEntity entityType) {
	if (entityType == DesignEntity::READ) {
		if (forwardMap.find(stmtNumber) != forwardMap.end()) {
			return forwardMap.find(stmtNumber)->second;
		}
	}

	return std::string();
}

std::unordered_set<std::string> ReadEntityStorage::getStatementByName(std::string& name, DesignEntity entityType) {
	if (entityType == DesignEntity::READ) {
		if (backwardMap.find(name) != backwardMap.end()) {
			return backwardMap.find(name)->second;
		}
	}
	return std::unordered_set<std::string>();
}

std::unordered_set<std::string> ReadEntityStorage::getAllName(DesignEntity returnType) {
	if (returnType == DesignEntity::READ) {
		std::unordered_set<std::string> result;
		for (const auto& [key, _] : backwardMap) {
			result.insert(key);
		}

		return result;
	}
	return std::unordered_set<std::string>();
}
