#pragma once
#include "../Entity/Entity.h"
#include <string>

class Relationship {
private:
	Entity* leftEntity;
	Entity* rightEntity;

public:
	Relationship(Entity* leftEntity, Entity* rightEntity);
	virtual ~Relationship() = default;
	Entity* getLeftEntity();
	Entity* getRightEntity();
};
