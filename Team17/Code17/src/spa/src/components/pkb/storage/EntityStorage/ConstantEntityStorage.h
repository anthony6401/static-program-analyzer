#pragma once
#include "models/Entity/Entity.h"
#include "models/Entity/DesignEntity.h"
#include "EntityStorage.h"

class ConstantEntityStorage : public EntityStorage {

public:
	ConstantEntityStorage();
	bool storeEntity(Entity* entity);
	std::unordered_set<std::string> getAllEntity(DesignEntity returnType);
};
