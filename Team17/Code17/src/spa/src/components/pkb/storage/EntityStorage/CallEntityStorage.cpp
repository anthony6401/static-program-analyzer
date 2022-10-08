#include "CallEntityStorage.h"
#include <typeinfo>
#include "models/Entity/CallEntity.h"

CallEntityStorage::CallEntityStorage() : EntityMappingStorage() {}

bool CallEntityStorage::storeEntity(Entity* entity) {
	CallEntity* callEntity = dynamic_cast<CallEntity*>(entity);
	if (callEntity) {
		return map.insert({ callEntity->getValue(), callEntity->getValueName() }).second;
	}

	return false;
}

std::unordered_set<std::string> CallEntityStorage::getAllEntity(DesignEntity returnType) {
	if (returnType == DesignEntity::CALL) {
		std::unordered_set<std::string> result;
		for (const auto& [key, _] : map) {
			result.insert(key);
		}

		return result;
	}
	return std::unordered_set<std::string>();
}

std::string CallEntityStorage::getStatementMapping(std::string& stmtNumber, DesignEntity entityType) {
	if (entityType == DesignEntity::CALL) {
		if (map.find(stmtNumber) != map.end()) {
			return map.find(stmtNumber)->second;
		}
	}

	return std::string();
}
