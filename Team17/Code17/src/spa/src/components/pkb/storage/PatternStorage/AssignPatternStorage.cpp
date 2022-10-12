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

std::unordered_set<std::string> AssignPatternStorage::getPatternController(TokenObject token, std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set) {
	std::string targetString = PatternUtils::convertInfixToPostfix(token.getValue());

	if ((token.getTokenType() == qps::TokenType::EXPRESSION) || (token.getTokenType() == qps::TokenType::NAME_WITH_QUOTATION)) {
		return handleExpressionAndNameForSet(targetString, set);
	}
	else if (token.getTokenType() == qps::TokenType::SUBEXPRESSION) {
		return handleSubexpressionForSet(targetString, set);
	}
	else if (token.getTokenType() == qps::TokenType::WILDCARD) {
		return handleWildcardForSet(set);
	}

	return std::unordered_set<std::string>();
}

std::unordered_set<std::string> AssignPatternStorage::handleExpressionAndNameForSet(std::string targetString, std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set) {
	std::unordered_set<std::string> result;
	for (const auto& ele : *set) {
		if (ele.second == targetString) {
			result.insert(ele.first);
		}
	}

	return result;
}

std::unordered_set<std::string> AssignPatternStorage::handleSubexpressionForSet(std::string targetString, std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set) {
	std::unordered_set<std::string> result;
	for (const auto& ele : *set) {
		if (PatternUtils::isSubExpression(targetString, ele.second)) {
			result.insert(ele.first);
		}
	}

	return result;
}

std::unordered_set<std::string> AssignPatternStorage::handleWildcardForSet(std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set) {
	std::unordered_set<std::string> result;
	for (const auto& ele : *set) {
		result.insert(ele.first);
	}

	return result;
}

std::vector<std::pair<std::string, std::string>> AssignPatternStorage::getPatternPairsController(TokenObject token) {
	std::string targetString = PatternUtils::convertInfixToPostfix(token.getValue());
	std::vector<std::pair<std::string, std::string>> result;
	for (auto it = this->assignPatternStorage.begin(); it != this->assignPatternStorage.end(); it++) {
		if ((token.getTokenType() == qps::TokenType::EXPRESSION) || (token.getTokenType() == qps::TokenType::NAME_WITH_QUOTATION)) {
			handleExpressionAndNameForVector(targetString, it, result);
		}
		else if (token.getTokenType() == qps::TokenType::SUBEXPRESSION) {
			handleSubexpressionForVector(targetString, it, result);
		}
		else if (token.getTokenType() == qps::TokenType::WILDCARD) {
			handleWildcardForVector(it, result);
		}
	}

	return result;
}

void AssignPatternStorage::handleExpressionAndNameForVector(std::string targetString,
													std::unordered_map<std::string, std::unordered_set<std::pair<std::string, std::string>, pair_hash>>::iterator& it,
													std::vector<std::pair<std::string, std::string>>& result) {
	std::string variable = it->first;
	std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set = &it->second;
	for (const auto& ele : *set) {
		if (ele.second == targetString) {
			result.push_back({ ele.first, variable });
		}
	}
}


void AssignPatternStorage::handleSubexpressionForVector(std::string targetString,
													std::unordered_map<std::string, std::unordered_set<std::pair<std::string, std::string>, pair_hash>>::iterator& it,
													std::vector<std::pair<std::string, std::string>>& result) {
	std::string variable = it->first;
	std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set = &it->second;
	for (const auto& ele : *set) {
		if (PatternUtils::isSubExpression(targetString, ele.second)) {
			result.push_back({ ele.first, variable });
		}
	}
}

void AssignPatternStorage::handleWildcardForVector(std::unordered_map<std::string, std::unordered_set<std::pair<std::string, std::string>, pair_hash>>::iterator& it,
											std::vector<std::pair<std::string, std::string>>& result) {
	std::string variable = it->first;
	std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set = &it->second;
	for (const auto& ele : *set) {
		result.push_back({ ele.first, variable });
	}
}

// This method is used to answer pattern query with NAME_WITH_QUOTES TokenType for the firstArgument i.e. a("x", "y"), a("x", _"y"_), a("x", _)
std::unordered_set<std::string> AssignPatternStorage::getPattern(DesignEntity designEntity, TokenObject firstArgument, TokenObject secondArgument) {
	if (designEntity == DesignEntity::ASSIGN) {
		std::unordered_set<std::pair<std::string, std::string>, pair_hash>* set = &this->assignPatternStorage.find(firstArgument.getValue())->second;
		if (this->assignPatternStorage.find(firstArgument.getValue()) != this->assignPatternStorage.end()) {
			return getPatternController(secondArgument, set);
		}
	}

	return std::unordered_set<std::string>();
}

// This method is used to answer pattern query with SYNONYM and WILDCARD TokenType for the firstArgument i.e. a(v, "y"), a(v, _"y"_), a(v, _), a(_, "y"), a(_, _"y"_), a(_, _)
std::vector<std::pair<std::string, std::string>> AssignPatternStorage::getPatternPair(DesignEntity designEntity, TokenObject secondArgument) {
	if (designEntity == DesignEntity::ASSIGN) {
		return getPatternPairsController(secondArgument);
	}

	return std::vector<std::pair<std::string, std::string>>();
}
