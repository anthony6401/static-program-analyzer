#include "ProcedureEntityStorage.h"
#include <typeinfo>
#include "models/Entity/ProcedureEntity.h"

ProcedureEntityStorage::ProcedureEntityStorage() : EntityStorage() {}

bool ProcedureEntityStorage::storeEntity(Entity* entity) {
	ProcedureEntity* procedureEntity = dynamic_cast<ProcedureEntity*>(entity);
	if (procedureEntity) {
		return this->set->insert(procedureEntity).second;
	}

	return false;
}
