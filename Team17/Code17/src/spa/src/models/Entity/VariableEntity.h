#pragma once

#include "Entity.h"

class VariableEntity : public Entity {
public:
	VariableEntity(std::string n);
	bool operator==(const VariableEntity& other) const {
		return value == other.value;
	}
};
