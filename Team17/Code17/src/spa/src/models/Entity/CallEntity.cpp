#include "CallEntity.h"
#include "Entity.h"

#include <string>

CallEntity::CallEntity(std::string stmtNumber, std::string entityValue) : StatementEntity(entityValue), stmtNumber(stmtNumber) {};

std::string CallEntity::getStmtNumber() {
	return this->stmtNumber;
}
