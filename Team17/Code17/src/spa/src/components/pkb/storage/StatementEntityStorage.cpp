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
