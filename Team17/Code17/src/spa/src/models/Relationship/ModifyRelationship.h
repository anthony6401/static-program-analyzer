#pragma once
#include "Relationship.h"
#include <string>

class ModifyRelationship : public Relationship {

public:
	ModifyRelationship(Entity leftEntity, Entity rightEntity);
};