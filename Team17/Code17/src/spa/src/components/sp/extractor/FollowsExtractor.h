#pragma once

#include "Extractor.h"
#include "../SimpleToken.h"

#include <vector>

class FollowsExtractor {
public:
	static std::vector<FollowsRelationship*> extractFollows(SimpleToken procOrStmtLstToken);
	static Entity* generateEntity(SimpleToken token);
	
	
	
	
	
	
	
	
	
	







	// =========
	void static extractFollows(Extractor extractor, std::vector<SimpleToken> seriesOfStmts);
	void static extractFollowsT(Extractor extractor, std::vector<SimpleToken> seriesOfStmts);
};
