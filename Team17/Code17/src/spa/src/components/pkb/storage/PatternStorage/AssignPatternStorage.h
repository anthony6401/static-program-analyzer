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
	bool storePattern(kb::Pattern* pattern);
	std::unordered_set<std::string> getPattern(DesignEntity designEntity, TokenObject firstArgument, TokenObject secondArgument);
	std::vector<std::pair<std::string, std::string>> getPatternPair(DesignEntity designEntity, TokenObject secondArgument);

private:
	void getPatternController(TokenObject token,
		std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set,
		std::unordered_set<std::string>& result);
	void handleExpressionAndNameForSet(std::string targetString,
		std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set,
		std::unordered_set<std::string>& result);
	void handleSubexpressionForSet(std::string targetString,
		std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set,
		std::unordered_set<std::string>& result);
	void handleWildcardForSet(std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set,
		std::unordered_set<std::string>& result);
	void getPatternPairsController(TokenObject token, std::string variable,
		std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set,
		std::vector<std::pair<std::string, std::string>>& result);
	void handleExpressionAndNameForVector(std::string targetString, std::string variable,
		std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set,
		std::vector<std::pair<std::string, std::string>>& result);
	void handleSubexpressionForVector(std::string targetString, std::string variable,
		std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set,
		std::vector<std::pair<std::string, std::string>>& result);
	void handleWildcardForVector(std::string variable,
		std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set,
		std::vector<std::pair<std::string, std::string>>& result);
	// Note that the storage takes in the firstValue of the Pattern as the key, and not the lineNum. If we use lineNum, we needs to go to every line to return the values anyway,
	// defeating the purpose of using map.
	std::unordered_map<std::string, std::unordered_set<std::pair<std::string, std::string>, pair_hash>> assignPatternStorage;
};
