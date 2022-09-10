#include "AssignPatternStorage.h"
#include "models/Pattern/Pattern.h"
#include "models/Pattern/AssignPattern.h"

#include <typeinfo>

AssignPatternStorage::AssignPatternStorage() : PatternStorage(), assignPatternStorage(std::unordered_map<std::string, std::pair<std::string, std::string>>()) {}

bool AssignPatternStorage::storePattern(Pattern* pattern) {
	AssignPattern* assignPattern = dynamic_cast<AssignPattern*>(pattern);
	if (assignPattern) {
		std::string lineNum = assignPattern->getLineNum();
		std::string firstValue = assignPattern->getFirstValue();
		std::string secondValue = assignPattern->getSecondValue();

		std::pair<std::string, std::string> pairValue(firstValue, secondValue);

		return this->assignPatternStorage.insert({ lineNum, pairValue }).second;
	}

	return false;
}
