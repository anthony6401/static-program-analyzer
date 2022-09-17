#pragma once

#include "Extractor.h"
#include "../SimpleToken.h"

#include <vector>

class UsesExtractor {
public:
	static std::vector<UsesRelationship*> extractUses(SimpleToken procOrWhileIfToken);
	static std::vector<UsesRelationship*> getUsesRelationships(SimpleToken procOrWhileIfToken, std::vector<SimpleToken> stmtSeries);
	static Entity* generateEntity(SimpleToken token);
};
