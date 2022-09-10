#include "CallEntityStorage.h"
#include <typeinfo>
#include "models/Entity/CallEntity.h"

CallEntityStorage::CallEntityStorage() : EntityStorage() {}

bool CallEntityStorage::storeEntity(Entity* entity) {
	CallEntity* callEntity = dynamic_cast<CallEntity*>(entity);
	if (callEntity) {
		return set.insert(callEntity->getValue()).second;
	}

	return false;
}

std::unordered_set<std::string> CallEntityStorage::getAllEntity(DesignEntity returnType) {
	if (returnType == DesignEntity::CALL) {
		return set;
	}
	return std::unordered_set<std::string>();
}
