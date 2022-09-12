#include "PatternManager.h"
#include "models/Pattern/Pattern.h"
#include "models/Entity/DesignEntity.h"
#include "../storage/PatternStorage/AssignPatternStorage.h"

#include "../../qps/query_preprocessor/query_tokenizer/TokenType.h"

#include <unordered_set>

PatternManager::PatternManager() {
	AssignPatternStorage* assignStorage = new AssignPatternStorage();

	patternStorage.push_back(assignStorage);

}

std::vector<PatternStorage*> PatternManager::getPatternStorage() {
	return patternStorage;
}

//Returns true, if it manage to stored, else false
bool PatternManager::storePattern(Pattern* pattern) {
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
		;if (ret.size() != 0) {
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
