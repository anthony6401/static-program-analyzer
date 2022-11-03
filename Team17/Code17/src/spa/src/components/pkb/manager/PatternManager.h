#pragma once
#include "../storage/PatternStorage/PatternStorage.h"

#include <string>
#include <vector>
#include <unordered_set>

class PatternManager {
public:
	PatternManager();
	std::vector<PatternStorage*> getPatternStorage();
	std::unordered_set<std::string> getPattern(DesignEntity designEntity, TokenObject firstArgument, TokenObject secondArgument);
	std::unordered_set<std::string> getPatternWildcard(DesignEntity designEntity, TokenObject secondArgument);
	std::vector<std::pair<std::string, std::string>> getPatternPair(DesignEntity designEntity, TokenObject secondArgument);
	bool storePattern(kb::Pattern* pattern);
	~PatternManager();

private:
	std::vector<PatternStorage*> patternStorage;
};
