#include "ReadEntityStorage.h"
#include <typeinfo>
#include "models/Entity/ReadEntity.h"

ReadEntityStorage::ReadEntityStorage() : EntityMappingStorage() {}

bool ReadEntityStorage::storeEntity(Entity* entity) {
	ReadEntity* readEntity = dynamic_cast<ReadEntity*>(entity);
	if (readEntity) {
		return map.insert({ readEntity->getValue(), std::unordered_set<std::string>({readEntity->getValueName()}) }).second;
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

std::unordered_set<std::string> ReadEntityStorage::getStatementMapping(std::unordered_set<std::string>& stmtSet, DesignEntity entityType) {
	return std::unordered_set<std::string>();
}
