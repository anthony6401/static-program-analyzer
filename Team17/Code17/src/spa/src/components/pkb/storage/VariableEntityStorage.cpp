#include "VariableEntityStorage.h"
#include <typeinfo>
#include "models/Entity/VariableEntity.h"

VariableEntityStorage::VariableEntityStorage() : EntityStorage() {}

bool VariableEntityStorage::storeEntity(Entity* entity) {
	VariableEntity* variableEntity = dynamic_cast<VariableEntity*>(entity);
	if (variableEntity) {
		return this->set->insert(variableEntity->getValue()).second;
	}

	return false;
}

std::unordered_set<std::string>* VariableEntityStorage::getAllEntity(qps::TokenType returnType) {
	if (returnType == qps::TokenType::VARIABLE) {
		return this->set;
	}
	return nullptr;
}
