#include "WhilePatternStorage.h"
#include "models/Pattern/WhilePattern.h"

WhilePatternStorage::WhilePatternStorage() : PatternStorage() {}

bool WhilePatternStorage::storePattern(kb::Pattern* pattern) {
	WhilePattern* ifPattern = dynamic_cast<WhilePattern*>(pattern);
	if (ifPattern) {
		std::string lineNum = ifPattern->getLineNum();
		std::string firstValue = ifPattern->getFirstValue();

		if (this->whilePatternStorage.find(firstValue) == this->whilePatternStorage.end()) {
			this->whilePatternStorage.insert({ firstValue, std::unordered_set<std::string>() });
		}

		return this->whilePatternStorage.find(firstValue)->second.insert(lineNum).second;

	}

	return false;
}

// This method is used to answer pattern query with NAME_WITH_QUOTES TokenType for the firstArgument i.e. if("x",_,_)
std::unordered_set<std::string> WhilePatternStorage::getPattern(DesignEntity designEntity, TokenObject firstArgument, TokenObject secondArgument) {
	std::unordered_set<std::string> result;

	if (designEntity == DesignEntity::WHILE) {
		if (this->whilePatternStorage.find(firstArgument.getValue()) != this->whilePatternStorage.end()) {
			return this->whilePatternStorage.find(firstArgument.getValue())->second;
		}
	}

	return result;
}

std::unordered_set<std::string> WhilePatternStorage::getPatternWildcard(DesignEntity designEntity, TokenObject secondArgument) {
	std::unordered_set<std::string> result;

	if (designEntity == DesignEntity::WHILE) {
		for (auto it = this->whilePatternStorage.begin(); it != this->whilePatternStorage.end(); it++) {
			std::string variable = it->first;
			std::unordered_set<std::string>* set = &it->second;
			result.insert(set->begin(), set->end());
		}
	}
	return result;
}

// This method is used to answer pattern query with SYNONYM and WILDCARD TokenType for the firstArgument i.e. if(v,_,_), if(_,_,_)
std::vector<std::pair<std::string, std::string>> WhilePatternStorage::getPatternPair(DesignEntity designEntity, TokenObject secondArgument) {
	std::vector<std::pair<std::string, std::string>> result;

	if (designEntity == DesignEntity::WHILE) {
		for (auto it = this->whilePatternStorage.begin(); it != this->whilePatternStorage.end(); it++) {
			std::string variable = it->first;
			std::unordered_set<std::string>* set = &this->whilePatternStorage.find(variable)->second;
			PatternUtils::populatePairFromSet(set, variable, &result);
		}
	}
	return result;
}
