#pragma once

#include "../storage/EntityStorage.h"
#include "../../qps/query_preprocessor/query_tokenizer/TokenType.h"

#include <string>
#include <vector>

class EntityManager {
public:
	EntityManager();
	std::vector<EntityStorage*> getEntityStorage();
	std::vector<std::string> getAllEntity(qps::TokenType returnType);
	bool storeEntity(Entity* entity);

private:
	 std::vector<EntityStorage*> entityStore;
};

