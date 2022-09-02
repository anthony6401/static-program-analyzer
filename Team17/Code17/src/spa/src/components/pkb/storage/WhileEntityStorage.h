#pragma once
#include "models/Entity/Entity.h"
#include "EntityStorage.h"

class WhileEntityStorage : public EntityStorage {

public:
	WhileEntityStorage();
	bool storeEntity(Entity* entity);
};
