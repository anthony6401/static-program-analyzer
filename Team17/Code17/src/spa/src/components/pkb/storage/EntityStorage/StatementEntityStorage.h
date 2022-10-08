#pragma once
#include "models/Entity/Entity.h"
#include "models/Entity/DesignEntity.h"
#include "EntityStorage.h"

class StatementEntityStorage : public EntityStorage {

public:
	StatementEntityStorage();
	bool storeEntity(Entity* entity);
	std::unordered_set<std::string> getAllEntity(DesignEntity returnType);
protected:
	std::unordered_set<std::string> set;
};
