#pragma once

#include "Entity.h"

class VariableEntity : public Entity {
public:
	VariableEntity(std::string entityValue);
	bool operator==(const VariableEntity& other) const {
		return value == other.value;
	}
};
