#include "ThreeValuePattern.h"
#include "Pattern.h"
#include <string>


ThreeValuePattern::ThreeValuePattern(std::string lineNum, std::string firstValue, std::string secondValue) : Pattern(lineNum, firstValue) ,secondValue(secondValue) {}


std::string ThreeValuePattern::getSecondValue() {
	return this->secondValue;
}
