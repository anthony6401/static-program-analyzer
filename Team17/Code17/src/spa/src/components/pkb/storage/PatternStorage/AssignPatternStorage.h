#pragma once
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "models/Relationship/Relationship.h"
#include "models/Relationship/RelationshipType.h"
#include "PatternStorage.h"
#include "../../../qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "../../../qps/query_preprocessor/query_tokenizer/TokenObject.h"

class AssignPatternStorage : public PatternStorage {

public:
	AssignPatternStorage();
	bool storePattern(Pattern* pattern);
	//std::unordered_set<std::string> getPattern(DesignEntity designEntity, TokenObject firstArgument, TokenObject secondArgument);
	//std::vector<std::pair<std::string, std::string>> getPatternPair(DesignEntity designEntity, TokenObject secondArgument);

private:
	std::unordered_map<std::string, std::pair<std::string, std::string>> assignPatternStorage;
};
