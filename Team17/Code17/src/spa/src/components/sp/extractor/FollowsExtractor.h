#pragma once

#include "Extractor.h"
#include "../SimpleToken.h"

#include <vector>

class FollowsExtractor {
public:
	static std::vector<FollowsRelationship*> extractFollows(SimpleToken procOrStmtLstToken);
	static Entity* generateEntity(SimpleToken token);
};
