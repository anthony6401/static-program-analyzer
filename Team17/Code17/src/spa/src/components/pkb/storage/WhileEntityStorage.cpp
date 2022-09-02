#include "WhileEntityStorage.h"
#include <typeinfo>
#include "models/Entity/WhileEntity.h"

WhileEntityStorage::WhileEntityStorage() : EntityStorage() {}

bool WhileEntityStorage::storeEntity(Entity* entity) {
	WhileEntity* whileEntity = dynamic_cast<WhileEntity*>(entity);
	if (whileEntity) {
		return this->set->insert(whileEntity).second;
	}

	return false;
}
