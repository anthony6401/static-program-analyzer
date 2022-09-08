#pragma once
#include "models/Entity/Entity.h"
#include <unordered_set>
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"

class EntityStorage {

public:
	EntityStorage();
	virtual bool storeEntity(Entity* entity) = 0;
	virtual std::unordered_set<std::string> getAllEntity(qps::TokenType tokenType) = 0;
	int getSize();
protected:
	std::unordered_set<std::string> set;
};
