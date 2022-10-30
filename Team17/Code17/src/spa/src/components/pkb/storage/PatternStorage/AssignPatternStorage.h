#pragma once
#include "PatternStorage.h"
#include "utils.h"

class AssignPatternStorage : public PatternStorage {

public:
	AssignPatternStorage();
	bool storePattern(kb::Pattern* pattern);
	std::unordered_set<std::string> getPattern(DesignEntity designEntity, TokenObject firstArgument, TokenObject secondArgument);
	std::unordered_set<std::string> getPatternWildcard(DesignEntity designEntity, TokenObject secondArgument);
	std::vector<std::pair<std::string, std::string>> getPatternPair(DesignEntity designEntity, TokenObject secondArgument);

private:
	std::unordered_set<std::string> getPatternController(TokenObject token, std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set);
	std::unordered_set<std::string> handleExpressionAndNameForSet(std::string targetString, std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set);
	std::unordered_set<std::string> handleSubexpressionForSet(std::string targetString, std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set);
	std::unordered_set<std::string> handleWildcardForSet(std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set);
	std::unordered_set<std::string> getPatternWildcardController(TokenObject token);
	void handleExpressionAndNameForWildcard(std::string targetString,
										std::unordered_map<std::string, std::unordered_set<std::pair<std::string, std::string>, pair_hash>>::iterator& it,
										std::unordered_set<std::string>& result);
	void handleSubexpressionForWildcard(std::string targetString,
									std::unordered_map<std::string, std::unordered_set<std::pair<std::string, std::string>, pair_hash>>::iterator& it,
									std::unordered_set<std::string>& result);
	void handleWildcardForWildcard(std::unordered_map<std::string, std::unordered_set<std::pair<std::string, std::string>, pair_hash>>::iterator& it,
									std::unordered_set<std::string>& result);
	std::vector<std::pair<std::string, std::string>> getPatternPairsController(TokenObject token);
	void handleExpressionAndNameForVector(std::string targetString,
										std::unordered_map<std::string, std::unordered_set<std::pair<std::string, std::string>, pair_hash>>::iterator& it,
										std::vector<std::pair<std::string, std::string>>& result);
	void handleSubexpressionForVector(std::string targetString,
										std::unordered_map<std::string, std::unordered_set<std::pair<std::string, std::string>, pair_hash>>::iterator& it,
										std::vector<std::pair<std::string, std::string>>& result);
	void handleWildcardForVector(std::unordered_map<std::string, std::unordered_set<std::pair<std::string, std::string>, pair_hash>>::iterator& it,
								std::vector<std::pair<std::string, std::string>>& result);
	// Note that the storage takes in the firstValue of the Pattern as the key, and not the lineNum. If we use lineNum, we needs to go to every line to return the values anyway,
	// defeating the purpose of using map.
	std::unordered_map<std::string, std::unordered_set<std::pair<std::string, std::string>, pair_hash>> assignPatternStorage;
};
