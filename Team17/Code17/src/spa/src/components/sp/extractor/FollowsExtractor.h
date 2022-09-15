#pragma once

#include "Extractor.h"
#include "../SimpleToken.h"

#include <vector>

class FollowsExtractor {
public:
	void static extractFollows(Extractor extractor, std::vector<SimpleToken> seriesOfStmts);
	void static extractFollowsT(Extractor extractor, std::vector<SimpleToken> seriesOfStmts);

private:
	static Entity* generateEntity(SimpleToken token);
};
