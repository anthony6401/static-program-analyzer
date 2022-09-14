#pragma once

#include "Extractor.h"
#include "../SimpleToken.h"
#include "../../../models/Pattern/AssignPattern.h"

class PatternExtractor {
public:
	static AssignPattern extractPattern(Extractor extractor, SimpleToken variable, SimpleToken expression);
};
