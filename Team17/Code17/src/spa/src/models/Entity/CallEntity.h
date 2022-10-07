#pragma once

#include "StatementEntity.h"

#include <string>

class CallEntity : public StatementEntity {
public:
	CallEntity(std::string stmtNumber, std::string n);
	bool operator==(const CallEntity& other) const {
		return (stmtNumber == other.stmtNumber) && (value == other.value);
	}
	std::string getStmtNumber();
private:
	std::string stmtNumber;
};
