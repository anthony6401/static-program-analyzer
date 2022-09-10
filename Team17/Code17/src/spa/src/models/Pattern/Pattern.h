#pragma once
#include <string>

class Pattern {
private:
	int lineNum;
	std::string firstValue;
	std::string secondValue;

public:
	Pattern(int lineNum, std::string firstValue, std::string secondValue);
	int getLineNum();
	std::string getFirstValue();
	std::string getSecondValue();
};
