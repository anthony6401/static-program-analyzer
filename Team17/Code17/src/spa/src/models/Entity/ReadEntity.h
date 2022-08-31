#pragma once

#include "StatementEntity.h"

#include <string>

class ReadEntity : public StatementEntity {
	public:
		ReadEntity(std::string n);
		bool operator==(const ReadEntity& other) const {
			return value == other.value;
		}
};
