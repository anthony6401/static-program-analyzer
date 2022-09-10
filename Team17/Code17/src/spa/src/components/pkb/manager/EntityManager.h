#pragma once

#include "../storage/EntityStorage/EntityStorage.h"
#include  "models/Entity/DesignEntity.h"

#include <string>
#include <vector>

class EntityManager {
public:
	EntityManager();
	std::vector<EntityStorage*> getEntityStorage();
	std::unordered_set<std::string> getAllEntity(DesignEntity returnType);
	bool storeEntity(Entity* entity);

private:
	 std::vector<EntityStorage*> entityStore;
};

