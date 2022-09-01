#pragma once

#include "Entity.h"
#include "StatementEntity.h"

#include <vector>

class StatementListEntity {
public:
	StatementListEntity(std::vector<StatementEntity> statements);
	std::vector<StatementEntity> getStatements();

	bool operator==(const StatementListEntity &other) const {
		return stmts == other.stmts;
	}
private:
	std::vector<StatementEntity> stmts;
};
