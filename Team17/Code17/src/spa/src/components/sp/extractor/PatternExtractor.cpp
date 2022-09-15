#include "PatternExtractor.h"

#include <stdio.h>

void PatternExtractor::extractPattern(Extractor extractor, SimpleToken simpleToken) {
	std::string lineNum = std::to_string(simpleToken.statementNumber);
	std::vector<SimpleToken> children = simpleToken.getChildren();
	SimpleToken variable = children.at(0);
	SimpleToken expression = children.at(1);

	std::string firstValue = variable.value;
	std::string secondValue = getExpressionAsString(expression);

	AssignPattern* assignPattern = new AssignPattern(lineNum, firstValue, secondValue);

	extractor.client->storePattern(assignPattern);
}

std::string PatternExtractor::getExpressionAsString(SimpleToken expression) {
	std::string expressionString;
	std::vector<SimpleToken> expressionChildren = expression.getChildren();
	for (int i = 0; i < expressionChildren.size(); i++) {
		std::string nextString = expressionChildren.at(i).value;
		expressionString = expressionString + nextString;
	}

	return expressionString;
}
