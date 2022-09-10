#pragma once
#include "Pattern.h"
#include <string>

class AssignPattern : public Pattern {

public:
	AssignPattern(std::string lineNum, std::string firstValue, std::string secondValue);
};
