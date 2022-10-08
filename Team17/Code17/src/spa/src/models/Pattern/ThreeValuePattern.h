#pragma once
#include "Pattern.h"
#include <string>

using namespace kb;

class ThreeValuePattern : public kb::Pattern {
private:
	std::string secondValue;

public:
	ThreeValuePattern(std::string lineNum, std::string firstValue, std::string secondValue);
	virtual ~ThreeValuePattern() = default;
	std::string getSecondValue();
};

