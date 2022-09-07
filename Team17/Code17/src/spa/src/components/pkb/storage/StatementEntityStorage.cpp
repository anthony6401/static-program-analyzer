#include "StatementEntityStorage.h"
#include <typeinfo>
#include "models/Entity/StatementEntity.h"

StatementEntityStorage::StatementEntityStorage() : EntityStorage() {}

bool StatementEntityStorage::storeEntity(Entity* entity) {
	StatementEntity* statementEntity = dynamic_cast<StatementEntity*>(entity);
	if (statementEntity) {
		return set.insert(statementEntity->getValue()).second;
	}

	return false;
}

std::unordered_set<std::string> StatementEntityStorage::getAllEntity(qps::TokenType returnType) {
	if (returnType == qps::TokenType::STMT) {
		return set;
	}
	return std::unordered_set<std::string>();
}
