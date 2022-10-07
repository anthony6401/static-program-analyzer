#pragma once

#include "StatementEntity.h"

#include <string>

class PrintEntity : public StatementEntity {
public:
	PrintEntity(std::string stmtNumber, std::string n);
	bool operator==(const PrintEntity& other) const {
		return (stmtNumber == other.stmtNumber) && (value == other.value);
	}
	std::string getStmtNumber();
private:
	std::string stmtNumber;
};
