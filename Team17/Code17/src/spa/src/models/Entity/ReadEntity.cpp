#include "ReadEntity.h"
#include "Entity.h"

#include <string>

ReadEntity::ReadEntity(std::string stmtNumber, std::string entityValue) : StatementEntity(entityValue), stmtNumber(stmtNumber) {};

std::string ReadEntity::getStmtNumber() {
	return this->stmtNumber;
}
