#pragma once
#include "PatternStorage.h"
#include "utils.h"

class IfPatternStorage : public PatternStorage {

public:
	IfPatternStorage();
	bool storePattern(kb::Pattern* pattern);
	std::unordered_set<std::string> getPattern(DesignEntity designEntity, TokenObject firstArgument, TokenObject secondArgument);
	std::unordered_set<std::string> getPatternWildcard(DesignEntity designEntity, TokenObject secondArgument);
	std::vector<std::pair<std::string, std::string>> getPatternPair(DesignEntity designEntity, TokenObject secondArgument);

private:
	// Note that the storage takes in the lineNum of the Pattern as the key and firstValue as value.
	std::unordered_map<std::string, std::unordered_set<std::string>> ifPatternStorage;
};
