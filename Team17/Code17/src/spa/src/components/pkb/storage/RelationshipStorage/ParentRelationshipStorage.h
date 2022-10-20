#pragma once
#include "ParentRelationshipStorageInterface.h"

class ParentRelationshipStorage : public ParentRelationshipStorageInterface {
public:
	ParentRelationshipStorage();

	bool storeRelationship(Relationship* rel);
};	
