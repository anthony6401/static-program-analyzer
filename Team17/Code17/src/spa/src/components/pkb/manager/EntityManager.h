#pragma once

#include "../storage/EntityStorage.h"

#include <string>
#include <vector>

class EntityManager {
public:
	EntityManager();
	std::vector<EntityStorage*> getEntityStorage();
	std::vector<std::string> getEntity(Entity entity);
	bool storeEntity(Entity* entity);

private:
	 std::vector<EntityStorage*> entityStore;
};

