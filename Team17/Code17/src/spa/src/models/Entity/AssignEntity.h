#pragma once

#include "StatementEntity.h"

#include <string>

class AssignEntity : public StatementEntity {
public:
	AssignEntity(std::string n);
	bool operator==(const AssignEntity& other) const {
		return value == other.value;
	}
};
