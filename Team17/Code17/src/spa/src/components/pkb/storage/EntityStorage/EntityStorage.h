#pragma once
#include "models/Entity/Entity.h"
#include "models/Entity/DesignEntity.h"
#include <unordered_set>

class EntityStorage {

public:
	EntityStorage();
	virtual bool storeEntity(Entity* entity) = 0;
	virtual std::unordered_set<std::string> getAllEntity(DesignEntity tokenType) = 0;
	int getSize();
protected:
	std::unordered_set<std::string> set;
};
