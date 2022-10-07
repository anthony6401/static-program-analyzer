#pragma once

#include "StatementEntity.h"

#include <string>

class CallEntity : public StatementEntity {
public:
	CallEntity(std::string entityValue, std::string valueName);
	bool operator==(const CallEntity& other) const {
		return (valueName == other.valueName) && (value == other.value);
	}
	std::string getValueName();
private:
	std::string valueName;
};
