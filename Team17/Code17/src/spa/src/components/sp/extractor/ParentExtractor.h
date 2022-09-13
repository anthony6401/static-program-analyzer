#pragma once

#include "Extractor.h"
#include "../SimpleToken.h"

#include <vector>

class ParentExtractor {
public:
	void static extractParent(Extractor extractor, SimpleToken parent, std::vector<SimpleToken> seriesOfStmts);
	void static extractParentT(Extractor extractor, SimpleToken parent, std::vector<SimpleToken> seriesOfStmts);

private:
	static Entity* generateEntity(SimpleToken token);
};
