#include "PatternExtractor.h"

#include <stdio.h>

AssignPattern PatternExtractor::extractPattern(SimpleToken variable, SimpleToken expression) {
	std::string lineNum = std::to_string(variable.statementNumber);
	std::string firstValue = variable.value;
	std::string secondValue = "";

	AssignPattern* assignPattern = new AssignPattern(lineNum, firstValue, secondValue);

	return *assignPattern;
}
