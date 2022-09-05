#pragma once
#include "models/Entity/Entity.h"
#include "EntityStorage.h"

class PrintEntityStorage : public EntityStorage {

public:
	PrintEntityStorage();
	bool storeEntity(Entity* entity);
	std::unordered_set<Entity*>* getAllEntity(qps::TokenType returnType);
};