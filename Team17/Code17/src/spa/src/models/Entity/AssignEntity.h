#pragma once

#include "StatementEntity.h"

#include <string>

class AssignEntity : public StatementEntity {
public:
	AssignEntity(std::string entityValue);
	bool operator==(const AssignEntity& other) const {
		return value == other.value;
	}
};
