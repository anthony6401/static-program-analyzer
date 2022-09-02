#include "VariableEntityStorage.h"
#include <typeinfo>
#include "models/Entity/VariableEntity.h"

VariableEntityStorage::VariableEntityStorage() : EntityStorage() {}

bool VariableEntityStorage::storeEntity(Entity* entity) {
	VariableEntity* variableEntity = dynamic_cast<VariableEntity*>(entity);
	if (variableEntity) {
		return this->set->insert(variableEntity).second;
	}

	return false;
}
