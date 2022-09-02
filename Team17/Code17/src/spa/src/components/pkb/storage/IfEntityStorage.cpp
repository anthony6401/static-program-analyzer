#include "IfEntityStorage.h"
#include <typeinfo>
#include "models/Entity/IfEntity.h"

IfEntityStorage::IfEntityStorage() : EntityStorage() {}

bool IfEntityStorage::storeEntity(Entity* entity) {
	IfEntity* ifEntity = dynamic_cast<IfEntity*>(entity);
	if (ifEntity) {
		return this->set->insert(ifEntity).second;
	}

	return false;
}
