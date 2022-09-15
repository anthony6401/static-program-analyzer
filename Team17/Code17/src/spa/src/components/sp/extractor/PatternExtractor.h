#pragma once

#include "Extractor.h"
#include "../SimpleToken.h"
#include "../../../models/Pattern/AssignPattern.h"

class PatternExtractor {
public:
	static void extractPattern(Extractor extractor, SimpleToken simpleToken);
	static std::string getExpressionAsString(SimpleToken expression);
};
