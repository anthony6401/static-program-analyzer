#include "AssignEntityStorage.h"
#include <typeinfo>
#include "models/Entity/AssignEntity.h"

AssignEntityStorage::AssignEntityStorage() : EntityStorage() {}

bool AssignEntityStorage::storeEntity(Entity* entity) {
	AssignEntity* assignEntity = dynamic_cast<AssignEntity*>(entity);
	if (assignEntity) {
		return set.insert(assignEntity->getValue()).second;
	}

	return false;
}

std::unordered_set<std::string> AssignEntityStorage::getAllEntity(DesignEntity returnType) {
	if (returnType == DesignEntity::ASSIGN) {
		return set;
	}
	return std::unordered_set<std::string>();
}
