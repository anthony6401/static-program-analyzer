#include "../pkb.h"
#include "SPClient.h"
#include "models/Relationship/Relationship.h"
#include "models/Pattern/Pattern.h"

#include <iostream>

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
