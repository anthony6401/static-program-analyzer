#include "AssignEntityStorage.h"
#include <typeinfo>
#include "models/Entity/AssignEntity.h"

AssignEntityStorage::AssignEntityStorage() : EntityStorage() {}

bool AssignEntityStorage::storeEntity(Entity* entity) {
	AssignEntity* assignEntity = dynamic_cast<AssignEntity*>(entity);
	if (assignEntity) {
		return this->set->insert(assignEntity).second;
	}

	return false;
}

std::unordered_set<Entity*>* AssignEntityStorage::getAllEntity(qps::TokenType returnType) {
	if (returnType == qps::TokenType::ASSIGN) {
		return this->set;
	}
	return nullptr;
}
