#pragma once
#include "CallsRelationshipStorageInterface.h"

class CallsRelationshipStorage : public CallsRelationshipStorageInterface {

public:
	CallsRelationshipStorage();
	bool storeRelationship(Relationship* rel);
};
