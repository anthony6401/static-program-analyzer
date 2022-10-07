#pragma once

#include "StatementEntity.h"

#include <string>

class ReadEntity : public StatementEntity {
public:
	ReadEntity(std::string stmtNumber, std::string n);
	bool operator==(const ReadEntity& other) const {
		return (stmtNumber == other.stmtNumber) && (value == other.value);
	}
	std::string getStmtNumber();
private:
	std::string stmtNumber;
};
