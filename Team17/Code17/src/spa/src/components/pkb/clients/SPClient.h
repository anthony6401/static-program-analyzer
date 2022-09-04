#pragma once

#include "../pkb.h"
#include "../../../models/Relationship/Relationship.h"

class SPClient {
private:
	PKB* pkb;

public:
	PKB* getPKB();
	SPClient(PKB* knowledge);
	bool storeRelationship(Relationship* rel);

};