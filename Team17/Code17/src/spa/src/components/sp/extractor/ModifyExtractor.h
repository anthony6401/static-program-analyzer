#pragma once

#include "Extractor.h"
#include "../SimpleToken.h"

#include <vector>

class ModifyExtractor {
public:
	static std::vector<ModifyRelationship*> extractModify(SimpleToken procOrStmtLstToken);
	static Entity* generateEntity(SimpleToken token);
};
