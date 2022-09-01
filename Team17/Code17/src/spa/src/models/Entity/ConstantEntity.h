#pragma once

#include "Entity.h"

class ConstantEntity : public Entity {
public:
	ConstantEntity(std::string n);
	bool operator==(const ConstantEntity& other) const {
		return value == other.value;
	}
};
