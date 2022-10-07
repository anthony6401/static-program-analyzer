#pragma once

#include "../storage/EntityStorage/EntityStorage.h"
#include "../storage/EntityStorage/EntityMappingStorage.h"
#include  "models/Entity/DesignEntity.h"

#include <string>
#include <vector>

class EntityManager {
public:
	EntityManager();
	std::vector<EntityStorage*> getEntityStorage();
	std::unordered_set<std::string> getAllEntity(DesignEntity returnType);
	std::unordered_set<std::string> getStatementMapping(std::unordered_set<std::string>& stmtSet, DesignEntity entityType);
	bool storeEntity(Entity* entity);

private:
	 std::vector<EntityStorage*> entityStore;
	 std::vector<EntityMappingStorage*> stmtMappingStore;
};
