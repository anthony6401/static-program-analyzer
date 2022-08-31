#pragma once

#include "StatementEntity.h"

#include <string>

class CallEntity : public StatementEntity {
	public:
		CallEntity(std::string n);
		bool operator==(const CallEntity& other) const {
			return value == other.value;
		}
};
