#pragma once
#include "models/Entity/Entity.h"
#include <unordered_set>

class EntityStorage {

public:
	EntityStorage();
	virtual bool storeEntity(Entity* entity) = 0;
protected:
	std::unordered_set<Entity*>* set;
};
