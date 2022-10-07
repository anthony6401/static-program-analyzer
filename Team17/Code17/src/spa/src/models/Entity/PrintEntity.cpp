#include "PrintEntity.h"
#include "Entity.h"

#include <string>

PrintEntity::PrintEntity(std::string stmtNumber, std::string entityValue) : StatementEntity(entityValue), stmtNumber(stmtNumber) {};

std::string PrintEntity::getStmtNumber() {
	return this->stmtNumber;
}
