#pragma once
#include "models/Entity/Entity.h"
#include "EntityStorage.h"
#include <unordered_set>

class AssignEntityStorage : public EntityStorage {

public:
	AssignEntityStorage();
	bool storeEntity(Entity* entity);
};