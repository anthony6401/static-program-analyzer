#pragma once
#include "models/Entity/Entity.h"
#include "EntityStorage.h"

class VariableEntityStorage : public EntityStorage {

public:
	VariableEntityStorage();
	bool storeEntity(Entity* entity);
	std::unordered_set<Entity*>* getAllEntity(qps::TokenType returnType);
};
