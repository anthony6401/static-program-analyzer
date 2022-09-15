#pragma once

#include "Extractor.h"
#include "../SimpleToken.h"

#include <vector>

class ParentExtractor {
public:
	static std::vector<ParentRelationship*> extractParent(SimpleToken procOrWhileIfToken);
	static Entity* generateEntity(SimpleToken token);















	// ===
	void static extractParent(Extractor extractor, SimpleToken parent, std::vector<SimpleToken> seriesOfStmts);
	void static extractParentT(Extractor extractor, SimpleToken parent, std::vector<SimpleToken> seriesOfStmts);
};
