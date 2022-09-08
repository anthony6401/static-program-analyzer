#pragma once
#include "models/Entity/Entity.h"
#include "EntityStorage.h"

class VariableEntityStorage : public EntityStorage {

public:
	VariableEntityStorage();
	bool storeEntity(Entity* entity);
	std::unordered_set<std::string> getAllEntity(qps::TokenType returnType);
};
