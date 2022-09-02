#pragma once

#include "../../models/Relationship/Relationship.h"

#include "./manager/EntityManager.h"

class PKB {
public:
	PKB();
	bool storeRelationship(Relationship* rel);
private:
	//Add managers
	EntityManager* entityManager;
};