#pragma once
#include "models/Entity/Entity.h"
#include "EntityStorage.h"

class IfEntityStorage : public EntityStorage {

public:
	IfEntityStorage();
	bool storeEntity(Entity* entity);
	std::unordered_set<std::string>* getAllEntity(qps::TokenType returnType);
};
