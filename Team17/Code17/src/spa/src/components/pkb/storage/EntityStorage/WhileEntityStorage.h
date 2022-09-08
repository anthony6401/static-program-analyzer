#pragma once
#include "models/Entity/Entity.h"
#include "EntityStorage.h"

class WhileEntityStorage : public EntityStorage {

public:
	WhileEntityStorage();
	bool storeEntity(Entity* entity);
	std::unordered_set<std::string> getAllEntity(qps::TokenType returnType);
};
