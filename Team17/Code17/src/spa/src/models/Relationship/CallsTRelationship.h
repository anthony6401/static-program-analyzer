#pragma once

#include "Relationship.h"
#include "models/Entity/Entity.h"

class CallsTRelationship : public Relationship {
public:
	CallsTRelationship(Entity* leftEntity, Entity* rightEntity);
};
