#pragma once
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "PatternStorage.h"
#include "utils.h"
#include "../../../qps/query_preprocessor/query_tokenizer/TokenObject.h"

class AssignPatternStorage : public PatternStorage {

public:
	AssignPatternStorage();
	bool storePattern(Pattern* pattern);
	std::unordered_set<std::string> getPattern(DesignEntity designEntity, TokenObject firstArgument, TokenObject secondArgument);
	std::vector<std::pair<std::string, std::string>> getPatternPair(DesignEntity designEntity, TokenObject secondArgument);

private:
	// Note that the storage takes in the firstValue of the Pattern as the key, and not the lineNum. If we use lineNum, we needs to go to every line to return the values anyway,
	// defeating the purpose of using map.
	std::unordered_map<std::string, std::unordered_set<std::pair<std::string, std::string>, pair_hash>> assignPatternStorage;
};
