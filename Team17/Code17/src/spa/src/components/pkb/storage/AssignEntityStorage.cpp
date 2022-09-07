#include "AssignEntityStorage.h"
#include <typeinfo>
#include "models/Entity/AssignEntity.h"

AssignEntityStorage::AssignEntityStorage() : EntityStorage() {}

bool AssignEntityStorage::storeEntity(Entity* entity) {
	AssignEntity* assignEntity = dynamic_cast<AssignEntity*>(entity);
	if (assignEntity) {
		return set->insert(assignEntity->getValue()).second;
	}

	return false;
}

std::unordered_set<std::string>* AssignEntityStorage::getAllEntity(qps::TokenType returnType) {
	if (returnType == qps::TokenType::ASSIGN) {
		return this->set;
	}
	return nullptr;
}