#pragma once

#include "StatementEntity.h"

#include <string>

class ReadEntity : public StatementEntity {
public:
	ReadEntity(std::string stmtNumber, std::string n);
	bool operator==(const ReadEntity& other) const {
		return (valueName == other.valueName) && (value == other.value);
	}
	std::string getValueName();
private:
	std::string valueName;
};
