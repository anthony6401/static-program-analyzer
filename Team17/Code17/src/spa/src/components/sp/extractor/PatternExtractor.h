#pragma once

#include "../SimpleToken.h"

#include "../../../models/Pattern/AssignPattern.h"
#include "../../../models/Entity/VariableEntity.h"

class PatternExtractor {
public:
	static AssignPattern extractPattern(SimpleToken variable, SimpleToken expression);
};
