#pragma once
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "PatternStorage.h"
#include "utils.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

class WhilePatternStorage : public PatternStorage {

public:
	WhilePatternStorage();
	bool storePattern(kb::Pattern* pattern);
	std::unordered_set<std::string> getPattern(DesignEntity designEntity, TokenObject firstArgument, TokenObject secondArgument);
	std::vector<std::pair<std::string, std::string>> getPatternPair(DesignEntity designEntity, TokenObject secondArgument);

private:
	// Note that the storage takes in the lineNum of the Pattern as the key and firstValue as value.
	std::unordered_map<std::string, std::unordered_set<std::string>> whilePatternStorage;
};
