#pragma once

#include "Entity.h"
#include "StatementEntity.h"

#include <vector>

class StatementListEntity {
	public:
		StatementListEntity();
		std::vector<StatementEntity> getStatements();
	private:
		std::vector<StatementEntity> stmts;
};
