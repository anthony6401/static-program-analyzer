#pragma once
#include "models/Entity/Entity.h"
#include "models/Entity/DesignEntity.h"
#include "EntityMappingStorage.h"

class ReadEntityStorage : public EntityMappingStorage {

public:
	ReadEntityStorage();
	bool storeEntity(Entity* entity);
	std::unordered_set<std::string> getAllEntity(DesignEntity returnType);
	std::unordered_set<std::string> getStatementMapping(std::unordered_set<std::string>& stmtSet, DesignEntity entityType);
};
