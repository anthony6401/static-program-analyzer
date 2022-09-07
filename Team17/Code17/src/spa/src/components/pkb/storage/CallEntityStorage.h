#pragma once
#include "models/Entity/Entity.h"
#include "EntityStorage.h"

class CallEntityStorage : public EntityStorage {

public:
	CallEntityStorage();
	bool storeEntity(Entity* entity);
	std::unordered_set<std::string>* getAllEntity(qps::TokenType returnType);
};
