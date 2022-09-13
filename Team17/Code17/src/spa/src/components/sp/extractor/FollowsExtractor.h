#pragma once

#include "Extractor.h"
#include "../SimpleToken.h"

class FollowsExtractor {
public:
	void static extractFollows(Extractor extractor, std::vector<SimpleToken> seriesOfStmts);
	void static extractFollowsT(Extractor extractor, std::vector<SimpleToken> seriesOfStmts);
};
