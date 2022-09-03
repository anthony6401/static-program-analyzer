#include "../../models/Relationship/Relationship.h"

#include "./manager/EntityManager.h"

#include "pkb.h"

#include "../qps/query_preprocessor/query_tokenizer/TokenType.h"

PKB::PKB() {
	entityManager = new EntityManager();
};

std::vector<std::string> PKB::getAllEntity(qps::TokenType returnType) {
	return entityManager->getAllEntity(returnType);
}

bool PKB::storeRelationship(Relationship* rel) {
	//to be implemented
	return 0;
}