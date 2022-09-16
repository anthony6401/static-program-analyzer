#include "PatternExtractor.h"

#include <stdio.h>

std::vector<AssignPattern*> PatternExtractor::extractPattern(SimpleToken procOrWhileIfToken) {
	std::vector<AssignPattern*> assignPatternVector;

	std::vector<SimpleToken> children = procOrWhileIfToken.getChildren();

	if (procOrWhileIfToken.type == SpTokenType::TPROCEDURE) {
		std::vector<SimpleToken> stmtSeries = children;
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
	}
	if (procOrWhileIfToken.type == SpTokenType::TWHILE) {
		std::vector<SimpleToken> stmtSeries = children.at(1).getChildren();
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
	}
	if (procOrWhileIfToken.type == SpTokenType::TIF) {
		std::vector<SimpleToken> stmtSeries_1 = children.at(1).getChildren();
		std::vector<SimpleToken> stmtSeries_2 = children.at(2).getChildren();
		for (int i = 0; i < stmtSeries_1.size(); i++) {
			SimpleToken current = stmtSeries_1.at(i);
			if (current.type == SpTokenType::TASSIGN) {
				std::vector<SimpleToken> assignChildren = current.getChildren();
				std::string lineNum = std::to_string(current.statementNumber);
				std::string firstVal = assignChildren.at(0).value;
				std::string seconVal = getExpressionAsString(assignChildren.at(1));
				AssignPattern* assignPattern = new AssignPattern(lineNum, firstVal, seconVal);
				assignPatternVector.push_back(assignPattern);
			}
		}
		for (int i = 0; i < stmtSeries_2.size(); i++) {
			SimpleToken current = stmtSeries_2.at(i);
			if (current.type == SpTokenType::TASSIGN) {
				std::vector<SimpleToken> assignChildren = current.getChildren();
				std::string lineNum = std::to_string(current.statementNumber);
				std::string firstVal = assignChildren.at(0).value;
				std::string seconVal = getExpressionAsString(assignChildren.at(1));
				AssignPattern* assignPattern = new AssignPattern(lineNum, firstVal, seconVal);
				assignPatternVector.push_back(assignPattern);
			}
		}
	}
	
	for (int i = 0; i < children.size(); i++) {
		SimpleToken current = children.at(i);
		if (current.type == SpTokenType::TWHILE || current.type == SpTokenType::TIF || current.type == SpTokenType::TSTMT) {
			std::vector<AssignPattern*> moreAssignPatternVector = PatternExtractor::extractPattern(current);
			assignPatternVector.insert(assignPatternVector.end(), moreAssignPatternVector.begin(), moreAssignPatternVector.end());
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
