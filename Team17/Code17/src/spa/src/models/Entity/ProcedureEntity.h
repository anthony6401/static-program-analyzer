#pragma once

#include "Entity.h"

class ProcedureEntity : public Entity {
public:
	ProcedureEntity(std::string entityValuen);
	bool operator==(const ProcedureEntity& other) const {
		return value == other.value;
	}
};
