#include "WhileEntityStorage.h"
#include <typeinfo>
#include "models/Entity/WhileEntity.h"

WhileEntityStorage::WhileEntityStorage() : EntityStorage() {}

bool WhileEntityStorage::storeEntity(Entity* entity) {
	WhileEntity* whileEntity = dynamic_cast<WhileEntity*>(entity);
	if (whileEntity) {
		return set.insert(whileEntity->getValue()).second;
	}

	return false;
}

std::unordered_set<std::string> WhileEntityStorage::getAllEntity(qps::TokenType returnType) {
	if (returnType == qps::TokenType::WHILE) {
		return set;
	}
	return std::unordered_set<std::string>();
}
