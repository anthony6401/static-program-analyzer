#include "../../models/Relationship/Relationship.h"

#include "./manager/EntityManager.h"

#include "pkb.h"

#include "../qps/query_preprocessor/query_tokenizer/TokenType.h"

#include <unordered_set>

PKB::PKB() {
	entityManager = new EntityManager();
};

std::unordered_set<std::string> PKB::getAllEntity(qps::TokenType returnType) {
	return entityManager->getAllEntity(returnType);
}

bool PKB::storeRelationship(Relationship* rel) {
	bool ret = true;

	//Store entity first if haven't
	ret = ret && entityManager->storeEntity(rel->getLeftEntity());
	ret = ret && entityManager->storeEntity(rel->getRightEntity());

	//TODO need to store relationship soon!!
	//For now just store entity from the given relationship

	return ret;
}