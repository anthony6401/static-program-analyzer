#pragma once

#include "StatementEntity.h"

class WhileEntity : public StatementEntity {
public:
	WhileEntity(std::string entityValue);
	bool operator==(const WhileEntity& other) const {
		return value == other.value;
	}
};
