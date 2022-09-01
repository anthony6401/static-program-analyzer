#pragma once

#include "Entity.h"

class StatementEntity : public Entity {
public:
	StatementEntity(std::string entityValue);
	virtual bool operator==(const StatementEntity& other) const {
		return value == other.value;
	}
};
