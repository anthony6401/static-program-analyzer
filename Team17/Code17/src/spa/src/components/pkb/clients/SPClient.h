#pragma once
#include "../pkb.h"

class SPClient {
private:
	PKB* pkb;

public:
	PKB* getPKB();
	SPClient(PKB* knowledge);
	bool storeRelationship(Relationship* rel);
	bool storePattern(kb::Pattern* pattern);
	bool storeConstant(Entity* entity);
};
