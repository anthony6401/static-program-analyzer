#include "Pattern.h"

using namespace kb;

Pattern::Pattern(std::string lineNum, std::string firstValue) : lineNum(lineNum), firstValue(firstValue) {}

std::string Pattern::getLineNum() {
	return this->lineNum;
}

std::string Pattern::getFirstValue() {
	return this->firstValue;
}
