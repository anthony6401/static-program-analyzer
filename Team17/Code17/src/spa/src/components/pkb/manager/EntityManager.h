#pragma once

#include "../storage/EntityStorage/EntityStorage.h"
#include "../storage/EntityStorage/EntityMappingStorage.h"

#include <string>
#include <vector>

class EntityManager {
public:
	EntityManager();
	std::vector<EntityStorage*> getEntityStorage();
	std::unordered_set<std::string> getAllEntity(DesignEntity returnType);
	std::string getStatementMapping(std::string& stmtNumber, DesignEntity entityType);
	bool storeEntity(Entity* entity);

private:
	 std::vector<EntityStorage*> entityStore;
	 std::vector<EntityMappingStorage*> stmtMappingStore;
};
