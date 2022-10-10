#pragma once
#include "models/Pattern/Pattern.h"
#include "models/Entity/DesignEntity.h"
#include "../../../qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>

class PatternStorage {

public:
	PatternStorage();
	virtual bool storePattern(kb::Pattern* pattern) = 0;
	virtual std::unordered_set<std::string> getPattern(DesignEntity designEntity, TokenObject firstArgument, TokenObject secondArgument) = 0;
	virtual std::vector<std::pair<std::string, std::string>> getPatternPair(DesignEntity designEntity, TokenObject secondArgument) = 0;
};
