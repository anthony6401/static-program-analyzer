#pragma once
#include "Pattern.h"
#include <string>

using namespace kb;

class WhilePattern : public kb::Pattern {

public:
	WhilePattern(std::string lineNum, std::string firstValue);
};
