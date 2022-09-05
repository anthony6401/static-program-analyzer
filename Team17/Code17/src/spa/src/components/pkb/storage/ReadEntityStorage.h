#pragma once
#include "models/Entity/Entity.h"
#include "EntityStorage.h"

class ReadEntityStorage : public EntityStorage {

public:
	ReadEntityStorage();
	bool storeEntity(Entity* entity);
	std::unordered_set<Entity*>* getAllEntity(qps::TokenType returnType);
};