#include "IfEntityStorage.h"
#include <typeinfo>
#include "models/Entity/IfEntity.h"

IfEntityStorage::IfEntityStorage() : EntityStorage() {}

bool IfEntityStorage::storeEntity(Entity* entity) {
	IfEntity* ifEntity = dynamic_cast<IfEntity*>(entity);
	if (ifEntity) {
		return this->set->insert(ifEntity).second;
	}

	return false;
}

std::unordered_set<Entity*>* IfEntityStorage::getAllEntity(qps::TokenType returnType) {
	if (returnType == qps::TokenType::IF) {
		return this->set;
	}
	return nullptr;
}
