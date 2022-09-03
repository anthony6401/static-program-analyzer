#include "StatementEntityStorage.h"
#include <typeinfo>
#include "models/Entity/StatementEntity.h"

StatementEntityStorage::StatementEntityStorage() : EntityStorage() {}

bool StatementEntityStorage::storeEntity(Entity* entity) {
	StatementEntity* statementEntity = dynamic_cast<StatementEntity*>(entity);
	if (statementEntity) {
		return this->set->insert(statementEntity).second;
	}

	return false;
}

std::unordered_set<Entity*>* StatementEntityStorage::getAllEntity(qps::TokenType returnType) {
	if (returnType == qps::TokenType::STMT) {
		return this->set;
	}
	return nullptr;
}
