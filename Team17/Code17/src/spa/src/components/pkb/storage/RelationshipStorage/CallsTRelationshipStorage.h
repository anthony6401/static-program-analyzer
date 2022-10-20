#pragma once
#include "CallsRelationshipStorageInterface.h"

class CallsTRelationshipStorage : public CallsRelationshipStorageInterface {

public:
	CallsTRelationshipStorage();
	bool storeRelationship(Relationship* rel);
};
