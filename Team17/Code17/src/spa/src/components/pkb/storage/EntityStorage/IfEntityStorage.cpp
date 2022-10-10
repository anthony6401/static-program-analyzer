#include "IfEntityStorage.h"
#include "models/Entity/IfEntity.h"

IfEntityStorage::IfEntityStorage() : EntityStorage() {}

bool IfEntityStorage::storeEntity(Entity* entity) {
	IfEntity* ifEntity = dynamic_cast<IfEntity*>(entity);
	if (ifEntity) {
		return set.insert(ifEntity->getValue()).second;
	}

	return false;
}

std::unordered_set<std::string> IfEntityStorage::getAllEntity(DesignEntity returnType) {
	if (returnType == DesignEntity::IF) {
		return set;
	}
	return std::unordered_set<std::string>();
}
