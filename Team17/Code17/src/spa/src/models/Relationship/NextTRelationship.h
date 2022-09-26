#pragma once

#include "Relationship.h"
#include "models/Entity/Entity.h"

class NextTRelationship : public Relationship {
public:
	NextTRelationship(Entity* leftEntity, Entity* rightEntity);
};