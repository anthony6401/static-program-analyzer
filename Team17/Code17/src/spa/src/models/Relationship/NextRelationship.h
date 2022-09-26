#pragma once

#include "Relationship.h"
#include "models/Entity/Entity.h"

class NextRelationship : public Relationship {
public:
	NextRelationship(Entity* leftEntity, Entity* rightEntity);
};