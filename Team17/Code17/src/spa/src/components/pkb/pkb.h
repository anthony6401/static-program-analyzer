#pragma once

#include "../../models/Relationship/Relationship.h"

#include "./manager/EntityManager.h"

#include "../qps/query_preprocessor/query_tokenizer/TokenType.h"

class PKB {
public:
	PKB();
	//For getting entity
	std::vector<std::string> getAllEntity(qps::TokenType returnType);

	//For getting relationship
	bool storeRelationship(Relationship* rel);
private:
	//Add managers
	EntityManager* entityManager;
};