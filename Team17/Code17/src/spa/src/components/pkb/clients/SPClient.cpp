#include "../pkb.h"
#include "SPClient.h"
#include "../../../models/Relationship/Relationship.h"

SPClient::SPClient(PKB* knowledge){
	pkb = knowledge;
}

PKB* SPClient::getPKB() {
	return pkb;
}

bool SPClient::storeRelationship(Relationship* rel) {
	return pkb->storeRelationship(rel);
}