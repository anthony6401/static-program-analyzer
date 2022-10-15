#include "PatternManager.h"
#include "../storage/PatternStorage/AssignPatternStorage.h"
#include "../storage/PatternStorage/IfPatternStorage.h"
#include "../storage/PatternStorage/WhilePatternStorage.h"

PatternManager::PatternManager() {
	AssignPatternStorage* assignStorage = new AssignPatternStorage();
	IfPatternStorage* ifPatternStorage = new IfPatternStorage();
	WhilePatternStorage* whilePatternStorage = new WhilePatternStorage();

	patternStorage.push_back(assignStorage);
	patternStorage.push_back(ifPatternStorage);
	patternStorage.push_back(whilePatternStorage);

}

std::vector<PatternStorage*> PatternManager::getPatternStorage() {
	return patternStorage;
}

//Returns true, if it manage to stored, else false
bool PatternManager::storePattern(kb::Pattern* pattern) {
	bool ret = false;
	for (auto& pt : patternStorage) {
		ret = ret || pt->storePattern(pattern);
	}
	return ret;
}

std::unordered_set<std::string> PatternManager::getPattern(DesignEntity designEntity, TokenObject firstArgument, TokenObject secondArgument) {
	std::unordered_set<std::string> ret;

	for (auto& pt : patternStorage) {
		ret = pt->getPattern(designEntity, firstArgument, secondArgument);
		if (ret.size() != 0) {
			return ret;
		}
	}
	return std::unordered_set<std::string>();
}

std::vector<std::pair<std::string, std::string>> PatternManager::getPatternPair(DesignEntity designEntity, TokenObject secondArgument) {
	std::vector<std::pair<std::string, std::string>> ret;

	for (auto& pt : patternStorage) {
		ret = pt->getPatternPair(designEntity, secondArgument);
		if (ret.size() != 0) {
			return ret;
		}
	}
	return std::vector<std::pair<std::string, std::string>>();
}

PatternManager::~PatternManager() {
	for (auto store : patternStorage) {
		delete store;
	}
	patternStorage.clear();
}
