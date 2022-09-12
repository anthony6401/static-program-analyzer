#pragma once

#include "../pkb.h"
#include "models/Relationship/Relationship.h"
#include "models/Pattern/Pattern.h"

class SPClient {
private:
	PKB* pkb;

public:
	PKB* getPKB();
	SPClient(PKB* knowledge);
	bool storeRelationship(Relationship* rel);
	bool storePattern(kb::Pattern* pattern);
};