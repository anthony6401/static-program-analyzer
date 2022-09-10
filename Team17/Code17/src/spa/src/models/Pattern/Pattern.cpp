#include "Pattern.h"


Pattern::Pattern(int lineNum, std::string firstValue, std::string secondValue) : lineNum(lineNum), firstValue(firstValue), secondValue(secondValue) {}

int Pattern::getLineNum() {
	return this->lineNum;
}

std::string Pattern::getFirstValue() {
	return this->firstValue;
}

std::string Pattern::getSecondValue() {
	return this->secondValue;
}
