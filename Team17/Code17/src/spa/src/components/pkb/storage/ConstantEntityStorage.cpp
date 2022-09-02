#include "ConstantEntityStorage.h"
#include <typeinfo>
#include "models/Entity/ConstantEntity.h"

ConstantEntityStorage::ConstantEntityStorage() : EntityStorage() {}

bool ConstantEntityStorage::storeEntity(Entity* entity) {
	ConstantEntity* constantEntity = dynamic_cast<ConstantEntity*>(entity);
	if (constantEntity) {
		return this->set->insert(constantEntity).second;
	}

	return false;
}
