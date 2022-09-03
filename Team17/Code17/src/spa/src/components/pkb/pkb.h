#pragma once

#include "../../models/Relationship/Relationship.h"
#include  "models/Entity/Entity.h"

#include "./manager/EntityManager.h"

#include "../qps/query_preprocessor/query_tokenizer/TokenType.h"

#include <unordered_set>

class PKB {
public:
	PKB();
	//For getting entity
	std::unordered_set<std::string> getAllEntity(qps::TokenType returnType);

	//For storing relationship
	bool storeRelationship(Relationship* rel);
private:
	//Add managers
	EntityManager* entityManager;
};