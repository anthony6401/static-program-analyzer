#pragma once

#include "Extractor.h"
#include "../SimpleToken.h"

#include <vector>

class ParentExtractor {
public:
	static std::vector<ParentRelationship*> extractParent(SimpleToken procOrWhileIfToken);
	static Entity* generateEntity(SimpleToken token);
};
