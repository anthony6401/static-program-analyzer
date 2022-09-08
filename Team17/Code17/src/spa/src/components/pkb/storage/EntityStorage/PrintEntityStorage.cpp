#include "PrintEntityStorage.h"
#include <typeinfo>
#include "models/Entity/PrintEntity.h"

PrintEntityStorage::PrintEntityStorage() : EntityStorage() {}

bool PrintEntityStorage::storeEntity(Entity* entity) {
	PrintEntity* printEntity = dynamic_cast<PrintEntity*>(entity);
	if (printEntity) {
		return set.insert(printEntity->getValue()).second;
	}

	return false;
}

std::unordered_set<std::string> PrintEntityStorage::getAllEntity(qps::TokenType returnType) {
	if (returnType == qps::TokenType::PRINT) {
		return set;
	}
	return std::unordered_set<std::string>();
}
