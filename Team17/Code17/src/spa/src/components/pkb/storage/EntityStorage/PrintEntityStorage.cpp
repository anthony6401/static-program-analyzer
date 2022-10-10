#include "PrintEntityStorage.h"
#include <typeinfo>
#include "models/Entity/PrintEntity.h"

PrintEntityStorage::PrintEntityStorage() : EntityMappingStorage() {}

bool PrintEntityStorage::storeEntity(Entity* entity) {
	PrintEntity* printEntity = dynamic_cast<PrintEntity*>(entity);
	if (printEntity) {
		std::string stmtNum = printEntity->getValue();
		std::string varName = printEntity->getValueName();
		bool result1 = forwardMap.insert({ stmtNum, varName }).second;
		if (backwardMap.find(varName) == backwardMap.end()) {
			backwardMap.insert({ varName, std::unordered_set<std::string>() });
		}
		std::unordered_set<std::string> mapValue = backwardMap.find(varName)->second;
		bool result2 = mapValue.insert(stmtNum).second;

		return result1 || result2;
	}

	return false;
}

std::unordered_set<std::string> PrintEntityStorage::getAllEntity(DesignEntity returnType) {
	if (returnType == DesignEntity::PRINT) {
		std::unordered_set<std::string> result;
		for (const auto& [key, _] : forwardMap) {
			result.insert(key);
		}

		return result;
	}
	return std::unordered_set<std::string>();
}

std::string PrintEntityStorage::getStatementMapping(std::string& stmtNumber, DesignEntity entityType) {
	if (entityType == DesignEntity::PRINT) {
		if (forwardMap.find(stmtNumber) != forwardMap.end()) {
			return forwardMap.find(stmtNumber)->second;
		}
	}

	return std::string();
}

std::unordered_set<std::string> PrintEntityStorage::getStatementByName(std::string& name, DesignEntity entityType) {
	if (entityType == DesignEntity::PRINT) {
		if (backwardMap.find(name) != backwardMap.end()) {
			return backwardMap.find(name)->second;
		}
	}
	return std::unordered_set<std::string>();
}

std::unordered_set<std::string> PrintEntityStorage::getAllName(DesignEntity returnType) {
	if (returnType == DesignEntity::PRINT) {
		std::unordered_set<std::string> result;
		for (const auto& [key, _] : backwardMap) {
			result.insert(key);
		}

		return result;
	}
	return std::unordered_set<std::string>();
}
