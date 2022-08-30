#include "StatementListEntity.h"
#include "StatementEntity.h"


#include <string>

StatementListEntity::StatementListEntity() {};

std::vector<StatementEntity>StatementListEntity::getStatements() {
	return this->stmts;
}
