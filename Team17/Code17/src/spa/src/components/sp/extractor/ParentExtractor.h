#pragma once

#include "Extractor.h"
#include "../SimpleToken.h"

class ParentExtractor {
public:
	void static extractParent(Extractor extractor, SimpleToken parent, std::vector<SimpleToken> seriesOfStmts);
	void static extractParentT(Extractor extractor, SimpleToken parent, std::vector<SimpleToken> seriesOfStmts);
};
