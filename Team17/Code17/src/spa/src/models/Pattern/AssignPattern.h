#pragma once
#include "ThreeValuePattern.h"
#include <string>


class AssignPattern : public ThreeValuePattern {

public:
	AssignPattern(std::string lineNum, std::string firstValue, std::string secondValue);
};
