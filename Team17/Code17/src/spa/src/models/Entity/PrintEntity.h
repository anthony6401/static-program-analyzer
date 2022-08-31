#pragma once

#include "StatementEntity.h"

#include <string>

class PrintEntity : public StatementEntity {
	public:
		PrintEntity(std::string n);
		bool operator==(const PrintEntity& other) const {
			return value == other.value;
		}
};
