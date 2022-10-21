#pragma once
#include "FollowsRelationshipStorageInterface.h"

class FollowsRelationshipStorage : public FollowsRelationshipStorageInterface {
public:
	FollowsRelationshipStorage();
	bool storeRelationship(Relationship* rel);
};