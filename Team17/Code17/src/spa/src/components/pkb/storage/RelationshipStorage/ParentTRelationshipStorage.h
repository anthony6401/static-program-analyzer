#pragma once
#include "ParentRelationshipStorageInterface.h"

class ParentTRelationshipStorage : public ParentRelationshipStorageInterface {
public:
	ParentTRelationshipStorage();
	
	bool storeRelationship(Relationship* rel);
};
