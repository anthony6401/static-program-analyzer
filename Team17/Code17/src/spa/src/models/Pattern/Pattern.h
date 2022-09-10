#pragma once
#include <string>

class Pattern {
private:
	std::string lineNum;
	std::string firstValue;
	std::string secondValue;

public:
	Pattern(std::string lineNum, std::string firstValue, std::string secondValue);
	std::string getLineNum();
	std::string getFirstValue();
	std::string getSecondValue();
};
