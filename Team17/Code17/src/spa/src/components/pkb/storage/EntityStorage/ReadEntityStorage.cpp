#include "ReadEntityStorage.h"
#include <typeinfo>
#include "models/Entity/ReadEntity.h"

ReadEntityStorage::ReadEntityStorage() : EntityStorage() {}

bool ReadEntityStorage::storeEntity(Entity* entity) {
	ReadEntity* readEntity = dynamic_cast<ReadEntity*>(entity);
	if (readEntity) {
		return this->set->insert(readEntity).second;
	}

	return false;
}

std::unordered_set<Entity*>* ReadEntityStorage::getAllEntity(qps::TokenType returnType) {
	if (returnType == qps::TokenType::READ) {
		return this->set;
	}
	return nullptr;
}
