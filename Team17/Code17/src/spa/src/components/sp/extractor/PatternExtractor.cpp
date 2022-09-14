#include "PatternExtractor.h"

#include <stdio.h>

AssignPattern PatternExtractor::extractPattern(Extractor extractor, SimpleToken variable, SimpleToken expression) {
	std::string lineNum = std::to_string(variable.statementNumber);
	std::string firstValue = variable.value;
	std::string secondValue = expression.value;

	AssignPattern* assignPattern = new AssignPattern(lineNum, firstValue, secondValue);

	extractor.client->storePattern(assignPattern);
}
