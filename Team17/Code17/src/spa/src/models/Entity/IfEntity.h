#pragma once

#include "StatementEntity.h"

#include <string>

class IfEntity : public StatementEntity {
public:
	IfEntity(std::string entityValue);
	bool operator==(const IfEntity& other) const {
		return value == other.value;
	}
};
