#include "ReadEntityStorage.h"
#include <typeinfo>
#include "models/Entity/ReadEntity.h"

ReadEntityStorage::ReadEntityStorage() : EntityStorage() {}

bool ReadEntityStorage::storeEntity(Entity* entity) {
	ReadEntity* readEntity = dynamic_cast<ReadEntity*>(entity);
	if (readEntity) {
		return set.insert(readEntity->getValue()).second;
	}

	return false;
}

std::unordered_set<std::string> ReadEntityStorage::getAllEntity(DesignEntity returnType) {
	if (returnType == DesignEntity::READ) {
		return set;
	}
	return std::unordered_set<std::string>();
}