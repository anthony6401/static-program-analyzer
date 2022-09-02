#include "AssignEntityStorage.h"
#include <typeinfo>
#include "models/Entity/AssignEntity.h"

AssignEntityStorage::AssignEntityStorage() : EntityStorage() {}

bool AssignEntityStorage::storeEntity(Entity* entity) {
	AssignEntity* assignEntity = dynamic_cast<AssignEntity*>(entity);
	if (assignEntity) {
		return this->set->insert(assignEntity).second;
	}

	return false;
}
