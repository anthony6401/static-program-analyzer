#pragma once
#include "Relationship.h"
#include <string>

class ModifyRelationship : public SuchThat {

public:
	ModifyRelationship(Entity leftEntity, Entity rightEntity);
};
