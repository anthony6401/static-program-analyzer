#include "ReadEntityStorage.h"
#include <typeinfo>
#include "models/Entity/ReadEntity.h"

ReadEntityStorage::ReadEntityStorage() : EntityMappingStorage() {}

bool ReadEntityStorage::storeEntity(Entity* entity) {
	ReadEntity* readEntity = dynamic_cast<ReadEntity*>(entity);
	if (readEntity) {
		return map.insert({ readEntity->getValue(), readEntity->getValueName() }).second;
	}

	return false;
}

std::unordered_set<std::string> ReadEntityStorage::getAllEntity(DesignEntity returnType) {
	if (returnType == DesignEntity::READ) {
		std::unordered_set<std::string> result;
		for (const auto& [key, _] : map) {
			result.insert(key);
		}

		return result;
	}
	return std::unordered_set<std::string>();
}

std::string ReadEntityStorage::getStatementMapping(std::string& stmtNumber, DesignEntity entityType) {
	if (entityType == DesignEntity::READ) {
		if (map.find(stmtNumber) != map.end()) {
			return map.find(stmtNumber)->second;
		}
	}

	return std::string();
}
