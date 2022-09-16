#pragma once

#include "Extractor.h"
#include "../SimpleToken.h"

#include <vector>

class ParentExtractor {
public:
	static std::vector<ParentRelationship*> extractParent(SimpleToken procOrWhileIfToken);
	static std::vector<ParentTRelationship*> extractParentT(SimpleToken procOrWhileIfToken);
	static Entity* generateEntity(SimpleToken token);
};
