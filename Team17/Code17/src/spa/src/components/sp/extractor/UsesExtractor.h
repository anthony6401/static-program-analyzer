#pragma once

#include "Extractor.h"
#include "../SimpleToken.h"

#include <vector>

class UsesExtractor {
public:
	static std::vector<UsesRelationship*> extractUses(SimpleToken procOrStmtLstToken);
	static Entity* generateEntity(SimpleToken token);
};
