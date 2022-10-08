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

std::string PrintEntityStorage::getStatementMapping(std::string& stmtNumber, DesignEntity entityType) {
	if (entityType == DesignEntity::PRINT) {
		if (map.find(stmtNumber) != map.end()) {
			return map.find(stmtNumber)->second;
		}
	}

	return std::string();
}
