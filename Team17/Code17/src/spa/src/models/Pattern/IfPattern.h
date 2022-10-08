#pragma once
#include "Pattern.h"
#include <string>

using namespace kb;

class IfPattern : public kb::Pattern {

public:
	IfPattern(std::string lineNum, std::string firstValue, std::string secondValue = "");
};
