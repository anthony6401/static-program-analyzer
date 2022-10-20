#pragma once
#include "FollowsRelationshipStorageInterface.h"

class FollowsTRelationshipStorage : public FollowsRelationshipStorageInterface {
public:
	FollowsTRelationshipStorage();
	bool storeRelationship(Relationship* rel);
};
