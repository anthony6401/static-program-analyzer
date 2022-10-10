#include "AssignPatternStorage.h"
#include "models/Pattern/AssignPattern.h"


AssignPatternStorage::AssignPatternStorage() : PatternStorage() {}

bool AssignPatternStorage::storePattern(kb::Pattern* pattern) {
	AssignPattern* assignPattern = dynamic_cast<AssignPattern*>(pattern);
	if (assignPattern) {
		std::string lineNum = assignPattern->getLineNum();
		std::string firstValue =assignPattern->getFirstValue();
		std::string secondValue = PatternUtils::convertInfixToPostfix(assignPattern->getSecondValue());
		std::pair<std::string, std::string> pairValue(lineNum, secondValue);

		if (this->assignPatternStorage.find(firstValue) == this->assignPatternStorage.end()) {
			this->assignPatternStorage.insert({firstValue, std::unordered_set<std::pair<std::string, std::string>, pair_hash>()});
		}

		return this->assignPatternStorage.find(firstValue)->second.insert(pairValue).second;
	}

	return false;
}

void AssignPatternStorage::getPatternController(TokenObject token, 
											std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set,
											std::unordered_set<std::string>& result) {
	std::string targetString = PatternUtils::convertInfixToPostfix(token.getValue());

	if ((token.getTokenType() == qps::TokenType::EXPRESSION) || (token.getTokenType() == qps::TokenType::NAME_WITH_QUOTATION)) {
		handleExpressionAndNameForSet(targetString, set, result);
	}
	else if (token.getTokenType() == qps::TokenType::SUBEXPRESSION) {
		handleSubexpressionForSet(targetString, set, result);
	}
	else if (token.getTokenType() == qps::TokenType::WILDCARD) {
		handleWildcardForSet(set, result);
	}
}

void AssignPatternStorage::handleExpressionAndNameForSet(std::string targetString,
												std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set,
												std::unordered_set<std::string>& result) {
	for (const auto& ele : *set) {
		if (ele.second == targetString) {
			result.insert(ele.first);
		}
	}
}

void AssignPatternStorage::handleSubexpressionForSet(std::string targetString,
								std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set,
								std::unordered_set<std::string>& result) {
	for (const auto& ele : *set) {
		if (PatternUtils::isSubExpression(targetString, ele.second)) {
			result.insert(ele.first);
		}
	}
}

void AssignPatternStorage::handleWildcardForSet(std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set,
						std::unordered_set<std::string>& result) {
	for (const auto& ele : *set) {
		result.insert(ele.first);
	}
}

void AssignPatternStorage::getPatternPairsController(TokenObject token, std::string variable,
						std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set,
						std::vector<std::pair<std::string, std::string>>& result) {
	std::string targetString = PatternUtils::convertInfixToPostfix(token.getValue());

	if ((token.getTokenType() == qps::TokenType::EXPRESSION) || (token.getTokenType() == qps::TokenType::NAME_WITH_QUOTATION)) {
		handleExpressionAndNameForVector(targetString, variable, set, result);
	}
	else if (token.getTokenType() == qps::TokenType::SUBEXPRESSION) {
		handleSubexpressionForVector(targetString, variable, set, result);
	}
	else if (token.getTokenType() == qps::TokenType::WILDCARD) {
		handleWildcardForVector(variable, set, result);
	}
}

void AssignPatternStorage::handleExpressionAndNameForVector(std::string targetString, std::string variable,
									std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set,
									std::vector<std::pair<std::string, std::string>>& result) {
	for (const auto& ele : *set) {
		if (ele.second == targetString) {
			result.push_back({ ele.first, variable });
		}
	}
}


void AssignPatternStorage::handleSubexpressionForVector(std::string targetString, std::string variable,
								std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set,
								std::vector<std::pair<std::string, std::string>>& result) {
	for (const auto& ele : *set) {
		if (PatternUtils::isSubExpression(targetString, ele.second)) {
			result.push_back({ ele.first, variable });
		}
	}
}

void AssignPatternStorage::handleWildcardForVector(std::string variable,
							std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set,
							std::vector<std::pair<std::string, std::string>>& result) {
	for (const auto& ele : *set) {
		result.push_back({ ele.first, variable });
	}
}

// This method is used to answer pattern query with NAME_WITH_QUOTES TokenType for the firstArgument i.e. a("x", "y"), a("x", _"y"_), a("x", _)
std::unordered_set<std::string> AssignPatternStorage::getPattern(DesignEntity designEntity, TokenObject firstArgument, TokenObject secondArgument) {
	std::unordered_set<std::string> result;
	if (designEntity == DesignEntity::ASSIGN) {
		if (this->assignPatternStorage.find(firstArgument.getValue()) != this->assignPatternStorage.end()) {
			std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set = &this->assignPatternStorage.find(firstArgument.getValue())->second;
			getPatternController(secondArgument, set, result);
		}
	}

	return result;
}

// This method is used to answer pattern query with SYNONYM and WILDCARD TokenType for the firstArgument i.e. a(v, "y"), a(v, _"y"_), a(v, _), a(_, "y"), a(_, _"y"_), a(_, _)
std::vector<std::pair<std::string, std::string>> AssignPatternStorage::getPatternPair(DesignEntity designEntity, TokenObject secondArgument) {
	std::vector<std::pair<std::string, std::string>> result;
	if (designEntity == DesignEntity::ASSIGN) {
		for (auto it = this->assignPatternStorage.begin(); it != this->assignPatternStorage.end(); it++) {
			std::string variable = it->first;
			getPatternPairsController(secondArgument, variable, &it->second, result);
		}
	}

	return result;
}
