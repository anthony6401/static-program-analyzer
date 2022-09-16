#pragma once

#include "Extractor.h"
#include "../SimpleToken.h"

#include <vector>

class ModifyExtractor {
public:
	static std::vector<ModifyRelationship*> extractModify(SimpleToken procOrWhileIfToken);
	static std::vector<ModifyRelationship*> getModifyRelationships(std::vector<SimpleToken> stmtSeries);
	static Entity* generateEntity(SimpleToken token);
};
