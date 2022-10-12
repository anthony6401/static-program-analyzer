#include "ProcedureEntityStorage.h"
#include "models/Entity/ProcedureEntity.h"

ProcedureEntityStorage::ProcedureEntityStorage() : EntityStorage() {}

bool ProcedureEntityStorage::storeEntity(Entity* entity) {
	ProcedureEntity* procedureEntity = dynamic_cast<ProcedureEntity*>(entity);
	if (procedureEntity) {
		return set.insert(procedureEntity->getValue()).second;
	}

	return false;
}

std::unordered_set<std::string> ProcedureEntityStorage::getAllEntity(DesignEntity returnType) {
	if (returnType == DesignEntity::PROCEDURE) {
		return set;
	}
	return std::unordered_set<std::string>();
}
