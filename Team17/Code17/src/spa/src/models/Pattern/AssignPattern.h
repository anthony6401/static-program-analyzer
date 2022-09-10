#pragma once
#include "Pattern.h"
#include <string>

class AssignPattern : public Pattern {

public:
	AssignPattern(int lineNum, std::string firstValue, std::string secondValue);
};
