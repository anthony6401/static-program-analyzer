#pragma once

#include "Relationship.h"


class ParentRelationship : public Relationship {
public:
	ParentRelationship(Entity* leftEntity, Entity* rightEntity);
};