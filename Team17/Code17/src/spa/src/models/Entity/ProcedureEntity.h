#pragma once

#include "Entity.h"

class ProcedureEntity : public Entity {
	public:
		ProcedureEntity(std::string n);
		bool operator==(const ProcedureEntity& other) const {
			return value == other.value;
		}
};
