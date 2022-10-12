#pragma once

#include "StatementEntity.h"

#include <string>

class PrintEntity : public StatementEntity {
public:
	PrintEntity(std::string entityValue, std::string valueName);
	bool operator==(const PrintEntity& other) const {
		return (valueName == other.valueName) && (value == other.value);
	}
	std::string getValueName();
private:
	std::string valueName;
};
