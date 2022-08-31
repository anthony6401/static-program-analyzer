#pragma once

#include "StatementEntity.h"

class WhileEntity : public StatementEntity {
	public:
		WhileEntity(std::string n);
		bool operator==(const WhileEntity& other) const {
			return value == other.value;
		}
};
