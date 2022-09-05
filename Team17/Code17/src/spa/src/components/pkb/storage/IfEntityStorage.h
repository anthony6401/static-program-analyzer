#pragma once
#include "models/Entity/Entity.h"
#include "EntityStorage.h"

class IfEntityStorage : public EntityStorage {

public:
	IfEntityStorage();
	bool storeEntity(Entity* entity);
	std::unordered_set<Entity*>* getAllEntity(qps::TokenType returnType);
};