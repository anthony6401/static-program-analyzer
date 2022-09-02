#pragma once
#include "models/Entity/Entity.h"
#include "EntityStorage.h"

class StatementEntityStorage : public EntityStorage {

public:
	StatementEntityStorage();
	bool storeEntity(Entity* entity);
};
