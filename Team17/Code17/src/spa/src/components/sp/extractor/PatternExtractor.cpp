#include "PatternExtractor.h"

#include <stdio.h>

std::vector<AssignPattern*> PatternExtractor::extractPattern(SimpleToken procOrStmtLstToken) {
	std::vector<AssignPattern*> assignPatternVector;

	std::vector<SimpleToken> stmtSeries = procOrStmtLstToken.getChildren();

	for (int i = 0; i < stmtSeries.size(); i++) {
		SimpleToken current = stmtSeries.at(i);
		if (current.type == SpTokenType::TASSIGN) {
			std::vector<SimpleToken> assignChildren = current.getChildren();
			std::string lineNum = std::to_string(current.statementNumber);
			std::string firstVal = assignChildren.at(0).value;
			std::string seconVal = getExpressionAsString(assignChildren.at(1));
			AssignPattern* assignPattern = new AssignPattern(lineNum, firstVal, seconVal);
			assignPatternVector.push_back(assignPattern);
		}
	}

	return assignPatternVector;
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
