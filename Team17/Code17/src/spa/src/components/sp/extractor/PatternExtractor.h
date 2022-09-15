#pragma once

#include "Extractor.h"
#include "../SimpleToken.h"
#include "../../../models/Pattern/AssignPattern.h"

class PatternExtractor {
public:
	static std::vector<AssignPattern*> extractPattern(SimpleToken procOrStmtLstToken);
	static std::string getExpressionAsString(SimpleToken expression);
};
