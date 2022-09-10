#pragma once
#include "models/Entity/Entity.h"
#include "models/Entity/DesignEntity.h"
#include "EntityStorage.h"

class WhileEntityStorage : public EntityStorage {

public:
	WhileEntityStorage();
	bool storeEntity(Entity* entity);
	std::unordered_set<std::string> getAllEntity(DesignEntity returnType);
};
