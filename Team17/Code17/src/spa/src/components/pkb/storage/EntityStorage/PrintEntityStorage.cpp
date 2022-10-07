#include "PrintEntityStorage.h"
#include <typeinfo>
#include "models/Entity/PrintEntity.h"

PrintEntityStorage::PrintEntityStorage() : EntityMappingStorage() {}

bool PrintEntityStorage::storeEntity(Entity* entity) {
	PrintEntity* printEntity = dynamic_cast<PrintEntity*>(entity);
	if (printEntity) {
		return map.insert({ printEntity->getValue(), printEntity->getValueName() }).second;
	}

	return false;
}

std::unordered_set<std::string> PrintEntityStorage::getAllEntity(DesignEntity returnType) {
	if (returnType == DesignEntity::PRINT) {
		std::unordered_set<std::string> result;
		for (const auto& [key, _] : map) {
			result.insert(key);
		}

		return result;
	}
	return std::unordered_set<std::string>();
}

std::unordered_set<std::string> PrintEntityStorage::getStatementMapping(std::unordered_set<std::string>& stmtSet, DesignEntity entityType) {
	if (entityType == DesignEntity::PRINT) {
		std::unordered_set<std::string> result;
		for (const auto& stmt : stmtSet) {
			if (map.find(stmt) != map.end()) {
				result.insert(map.find(stmt)->second);
			}
		}

		return result;
	}

	return std::unordered_set<std::string>();
}
