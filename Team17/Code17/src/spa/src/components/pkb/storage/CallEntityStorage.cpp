#include "CallEntityStorage.h"
#include <typeinfo>
#include "models/Entity/CallEntity.h"

CallEntityStorage::CallEntityStorage() : EntityStorage() {}

bool CallEntityStorage::storeEntity(Entity* entity) {
	CallEntity* callEntity = dynamic_cast<CallEntity*>(entity);
	if (callEntity) {
		return set->insert(callEntity->getValue()).second;
	}

	return false;
}

std::unordered_set<std::string>* CallEntityStorage::getAllEntity(qps::TokenType returnType) {
	if (returnType == qps::TokenType::CALL) {
		return this->set;
	}
	return nullptr;
}
