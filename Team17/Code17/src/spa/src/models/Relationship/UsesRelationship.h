#pragma once
#include "Relationship.h"
#include <string>

class UsesRelationship : public SuchThat {

public:
	UsesRelationship(Entity leftEntity, Entity rightEntity);
};
