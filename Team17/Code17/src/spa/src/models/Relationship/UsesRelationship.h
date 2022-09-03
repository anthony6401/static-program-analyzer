#pragma once
#include "Relationship.h"
#include <string>

class UsesRelationship : public Relationship {

public:
	UsesRelationship(Entity* leftEntity, Entity* rightEntity);
};
