#pragma once
#include "models/Entity/Entity.h"
#include "EntityStorage.h"

class AssignEntityStorage : public EntityStorage {

public:
	AssignEntityStorage();
	bool storeEntity(Entity* entity);
};
