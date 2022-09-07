#pragma once
#include "models/Entity/Entity.h"
#include "EntityStorage.h"

class ProcedureEntityStorage : public EntityStorage {

public:
	ProcedureEntityStorage();
	bool storeEntity(Entity* entity);
	std::unordered_set<std::string>* getAllEntity(qps::TokenType returnType);
};
