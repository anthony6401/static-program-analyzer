#pragma once

#include "Relationship.h"
#include "models/Entity/Entity.h"

class CallsRelationship : public Relationship {
public:
	CallsRelationship(Entity* leftEntity, Entity* rightEntity);
};