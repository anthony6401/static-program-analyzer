#pragma once
#include "models/Entity/Entity.h"
#include <unordered_set>

class EntityStorage {

public:
	EntityStorage();
	virtual bool storeEntity(Entity* entity) = 0;
	int getSize() {
		return  set->size();
	}
	std::unordered_set<Entity*>* getSet() {
		return this->set;
	}
protected:
	std::unordered_set<Entity*>* set;
};
