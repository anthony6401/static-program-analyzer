#pragma once
#include <string>

class Pattern {
private:
	std::string lineNum;
	std::string firstValue;
	std::string secondValue;

public:
	Pattern(std::string lineNum, std::string firstValue, std::string secondValue);
	virtual ~Pattern() = default;
	std::string getLineNum();
	std::string getFirstValue();
	std::string getSecondValue();
};
