#pragma once

#include "Extractor.h"
#include "../SimpleToken.h"

#include <vector>

class FollowsExtractor {
public:
	static std::vector<FollowsRelationship*> extractFollows(SimpleToken procOrWhileIfToken);
	static std::vector<FollowsTRelationship*> extractFollowsT(SimpleToken procOrWhileIfToken);
	static Entity* generateEntity(SimpleToken token);
};
