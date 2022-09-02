#pragma once
#include "../Entity/Entity.h"
#include <string>

class SuchThat {
private:
	Entity leftEntity;
	Entity rightEntity;

public:
	SuchThat(Entity leftEntity, Entity rightEntity);
	Entity getLeftEntity();
	Entity getRightEntity();
};
