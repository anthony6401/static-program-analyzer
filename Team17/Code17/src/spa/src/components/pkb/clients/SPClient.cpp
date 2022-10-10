#include "SPClient.h"

SPClient::SPClient(PKB* knowledge){
	pkb = knowledge;
}

PKB* SPClient::getPKB() {
	return pkb;
}

bool SPClient::storeRelationship(Relationship* rel) {
	return pkb->storeRelationship(rel);
}

bool SPClient::storePattern(kb::Pattern* pattern) {
	return pkb->storePattern(pattern);
}

bool SPClient::storeConstant(Entity* entity) {
	return pkb->storeConstant(entity);
}
