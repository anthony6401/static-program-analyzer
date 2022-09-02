#pragma once
#include "models/Entity/Entity.h"
#include "EntityStorage.h"

class ConstantEntityStorage : public EntityStorage {

public:
	ConstantEntityStorage();
	bool storeEntity(Entity* entity);
};
