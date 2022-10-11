#pragma once
#include "models/Entity/Entity.h"
#include "models/Entity/DesignEntity.h"
#include "EntityMappingStorage.h"

class PrintEntityStorage : public EntityMappingStorage {

public:
	PrintEntityStorage();
	bool storeEntity(Entity* entity);
	std::unordered_set<std::string> getAllEntity(DesignEntity returnType);
	std::string getStatementMapping(std::string& stmtSet, DesignEntity entityType);
	std::unordered_set<std::string> getStatementByName(std::string& name, DesignEntity entityType);
	std::unordered_set<std::string> getAllName(DesignEntity entityType);
};
