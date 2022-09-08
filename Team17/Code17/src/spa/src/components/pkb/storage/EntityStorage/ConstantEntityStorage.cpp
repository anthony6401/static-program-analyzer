#include "ConstantEntityStorage.h"
#include <typeinfo>
#include "models/Entity/ConstantEntity.h"

ConstantEntityStorage::ConstantEntityStorage() : EntityStorage() {}

bool ConstantEntityStorage::storeEntity(Entity* entity) {
	ConstantEntity* constantEntity = dynamic_cast<ConstantEntity*>(entity);
	if (constantEntity) {
		return set.insert(constantEntity->getValue()).second;
	}

	return false;
}

std::unordered_set<std::string> ConstantEntityStorage::getAllEntity(qps::TokenType returnType) {
	if (returnType == qps::TokenType::CONSTANT) {
		return set;
	}
	return std::unordered_set<std::string>();
}
