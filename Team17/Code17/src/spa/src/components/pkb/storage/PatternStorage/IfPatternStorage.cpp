#include "IfPatternStorage.h"
#include "models/Pattern/IfPattern.h"

IfPatternStorage::IfPatternStorage() : PatternStorage() {}

bool IfPatternStorage::storePattern(kb::Pattern* pattern) {
	IfPattern* ifPattern = dynamic_cast<IfPattern*>(pattern);
	if (ifPattern) {
		std::string lineNum = ifPattern->getLineNum();
		std::string firstValue = ifPattern->getFirstValue();
		
		if (this->ifPatternStorage.find(firstValue) == this->ifPatternStorage.end()) {
			this->ifPatternStorage.insert({ firstValue, std::unordered_set<std::string>()});
		}

		return this->ifPatternStorage.find(firstValue)->second.insert(lineNum).second;
		
	}

	return false;
}


// This method is used to answer pattern query with NAME_WITH_QUOTES TokenType for the firstArgument i.e. if("x",_,_)
std::unordered_set<std::string> IfPatternStorage::getPattern(DesignEntity designEntity, TokenObject firstArgument, TokenObject secondArgument) {
	std::unordered_set<std::string> result;

	if (designEntity == DesignEntity::IF) {
		if (this->ifPatternStorage.find(firstArgument.getValue()) != this->ifPatternStorage.end()) {
			return this->ifPatternStorage.find(firstArgument.getValue())->second;
		}
	}

	return result;
}

// This method is used to answer pattern query with SYNONYM and WILDCARD TokenType for the firstArgument i.e. if(v,_,_), if(_,_,_)
std::vector<std::pair<std::string, std::string>> IfPatternStorage::getPatternPair(DesignEntity designEntity, TokenObject secondArgument) {
	std::vector<std::pair<std::string, std::string>> result;

	if (designEntity == DesignEntity::IF) {
		for (auto it = this->ifPatternStorage.begin(); it != this->ifPatternStorage.end(); it++) {
			std::string variable = it->first;
			std::unordered_set<std::string>* set = &this->ifPatternStorage.find(variable)->second;
			PatternUtils::populatePairFromSet(set, variable, &result);
		}
	}
	return result;
}
