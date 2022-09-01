#pragma once

#include "StatementEntity.h"

#include <string>

class PrintEntity : public StatementEntity {
public:
	PrintEntity(std::string entityValue);
	bool operator==(const PrintEntity& other) const {
		return value == other.value;
	}
};
