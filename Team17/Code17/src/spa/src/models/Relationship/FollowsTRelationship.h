#pragma once

#include "Relationship.h"
#include "models/Entity/Entity.h"

class FollowsTRelationship : public Relationship {
public:
	FollowsTRelationship(Entity* leftEntity, Entity* rightEntity);
};
