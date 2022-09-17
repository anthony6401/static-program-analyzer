#include "AssignPatternStorage.h"
#include "models/Pattern/Pattern.h"
#include "models/Pattern/AssignPattern.h"

#include <typeinfo>
#include <vector>

AssignPatternStorage::AssignPatternStorage() : PatternStorage(), assignPatternStorage(std::unordered_map<std::string, std::unordered_set<std::pair<std::string, std::string>, pair_hash>>()) {}

bool AssignPatternStorage::storePattern(kb::Pattern* pattern) {
	AssignPattern* assignPattern = dynamic_cast<AssignPattern*>(pattern);
	if (assignPattern) {
		std::string lineNum = assignPattern->getLineNum();
		std::string firstValue = assignPattern->getFirstValue();
		std::string secondValue = assignPattern->getSecondValue();

		std::pair<std::string, std::string> pairValue(lineNum, secondValue);

		if (this->assignPatternStorage.find(firstValue) == this->assignPatternStorage.end()) {
			this->assignPatternStorage.insert({firstValue, std::unordered_set<std::pair<std::string, std::string>, pair_hash>()});
		}

		return this->assignPatternStorage.find(firstValue)->second.insert(pairValue).second;
	}

	return false;
}

// This method is used to answer pattern query with NAME_WITH_QUOTES TokenType for the firstArgument i.e. a("x", "y"), a("x", _"y"_), a("x", _)
std::unordered_set<std::string> AssignPatternStorage::getPattern(DesignEntity designEntity, TokenObject firstArgument, TokenObject secondArgument) {
	std::unordered_set<std::string> result;

	if (designEntity == DesignEntity::ASSIGN) {
		if (this->assignPatternStorage.find(firstArgument.getValue()) != this->assignPatternStorage.end()) {
			std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set = &this->assignPatternStorage.find(firstArgument.getValue())->second;
			std::string secondArgumentValue = secondArgument.getValue();


			if ((secondArgument.getTokenType() == qps::TokenType::EXPRESSION) || (secondArgument.getTokenType() == qps::TokenType::NAME_WITH_QUOTATION)) {
				for (auto it = set->begin(); it != set->end(); ++it) {
					if (it->second == secondArgumentValue) {
						result.insert(it->first);
					}
				}

			} else if (secondArgument.getTokenType() == qps::TokenType::SUBEXPRESSION) {
				for (auto it = set->begin(); it != set->end(); ++it) {
					if (PatternUtils::isSubExpression(secondArgumentValue, it->second)) {
						result.insert(it->first);
					}
				}

			} else if (secondArgument.getTokenType() == qps::TokenType::WILDCARD) {
				for (auto it = set->begin(); it != set->end(); ++it) {
					result.insert(it->first);
				}
				
			}
		}
	}

	return result;
}

// This method is used to answer pattern query with SYNONYM and WILDCARD TokenType for the firstArgument i.e. a(v, "y"), a(v, _"y"_), a(v, _), a(_, "y"), a(_, _"y"_), a(_, _)
std::vector<std::pair<std::string, std::string>> AssignPatternStorage::getPatternPair(DesignEntity designEntity, TokenObject secondArgument) {
	std::vector<std::pair<std::string, std::string>> result;
	if (designEntity == DesignEntity::ASSIGN) {
		std::string secondArgumentValue = secondArgument.getValue();
		for (auto it = this->assignPatternStorage.begin(); it != this->assignPatternStorage.end(); it++) {
			std::string variable = it->first;

			if ((secondArgument.getTokenType() == qps::TokenType::EXPRESSION) || (secondArgument.getTokenType() == qps::TokenType::NAME_WITH_QUOTATION)) {
				for (auto it_set = it->second.begin(); it_set != it->second.end(); ++it_set) {
					if (it_set->second == secondArgumentValue) {
						result.push_back({ it_set->first, variable });
					}
				}

			}
			else if (secondArgument.getTokenType() == qps::TokenType::SUBEXPRESSION) {
				for (auto it_set = it->second.begin(); it_set != it->second.end(); ++it_set) {
					if (PatternUtils::isSubExpression(secondArgumentValue, it_set->second)) {
						result.push_back({ it_set->first, variable });
					}
				}

			}
			else if (secondArgument.getTokenType() == qps::TokenType::WILDCARD) {
				for (auto it_set = it->second.begin(); it_set != it->second.end(); ++it_set) {
					result.push_back({ it_set->first, variable });
				}
			}
		}
	}

	return result;
}
