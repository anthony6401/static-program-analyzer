#include "StatementListEntity.h"
#include "StatementEntity.h"


#include <string>

StatementListEntity::StatementListEntity(std::vector<StatementEntity> statements) {
	this->stmts = statements;
}

std::vector<StatementEntity> StatementListEntity::getStatements() {
	return stmts;
}

//bool StatementListEntity::operator==(StatementListEntity & other) const {
//	return stmts == other.stmts ;
//}