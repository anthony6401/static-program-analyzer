#pragma once

#include "../SimpleToken.h"
#include "../../../models/Pattern/AssignPattern.h"

class PatternExtractor {
public:
	static AssignPattern extractPattern(SimpleToken variable, SimpleToken expression);
};
