#include "PrintEntityStorage.h"
#include <typeinfo>
#include "models/Entity/PrintEntity.h"

PrintEntityStorage::PrintEntityStorage() : EntityStorage() {}

bool PrintEntityStorage::storeEntity(Entity* entity) {
	PrintEntity* printEntity = dynamic_cast<PrintEntity*>(entity);
	if (printEntity) {
		return this->set->insert(printEntity).second;
	}

	return false;
}

std::unordered_set<Entity*>* PrintEntityStorage::getAllEntity(qps::TokenType returnType) {
	if (returnType == qps::TokenType::PRINT) {
		return this->set;
	}
	return nullptr;
}
