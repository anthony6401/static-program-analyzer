#pragma once
#include "models/Entity/Entity.h"
#include "EntityStorage.h"

class AssignEntityStorage : public EntityStorage {

public:
	AssignEntityStorage();
	bool storeEntity(Entity* entity);
	std::unordered_set<std::string> getAllEntity(qps::TokenType returnType);
};
