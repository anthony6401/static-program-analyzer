#pragma once
#include "models/Entity/Entity.h"
#include "models/Entity/DesignEntity.h"
#include "EntityMappingStorage.h"

class CallEntityStorage : public EntityMappingStorage {

public:
	CallEntityStorage();
	bool storeEntity(Entity* entity);
	std::unordered_set<std::string> getAllEntity(DesignEntity returnType);
	std::string getStatementMapping(std::string& stmtNumber, DesignEntity entityType);
};
