#include "NextTRelationshipEvaluator.h"
#include "utils.h"

NextTRelationshipEvaluator::NextTRelationshipEvaluator(NextRelationshipStorage* nextStorage) : RuntimeRelationshipEvaluator(), nextStorage(nextStorage) {}

// DFS search to answer Next* queries with 2 integer values
bool NextTRelationshipEvaluator::DFSNextTForward(std::string curr, std::string target, std::unordered_set<std::string>& visited) {

	if (getForwardCacheKV(curr, target)) {
		return true;
	}

	visited.insert(curr);

	std::unordered_set<std::string> neighbours = this->nextStorage->getNextForward(curr);

	for (std::string neighbour : neighbours) {
		if (target == neighbour || (visited.find(neighbour) == visited.end() && DFSNextTForward(neighbour, target, visited))) {
			return true;
		}
	}

	return false;
}

// DFS search forward to answer Next* queries with synonym
void NextTRelationshipEvaluator::DFSNextTForwardWithSynonym(std::string curr, std::unordered_set<std::string>& visited,
															std::unordered_set<std::string>& result,
															std::unordered_set<std::string>& filter) {
	std::unordered_set<std::string> cache = getForwardCache(curr);
	if (cache.size() != 0) {
		std::unordered_set<std::string> intersectionRes = RuntimeRelationshipUtils::getSetIntersection(cache, filter);
		for (auto const& el : intersectionRes) {
			result.insert(el);
		}
	} else {
		visited.insert(curr);

		std::unordered_set<std::string> neighbours = this->nextStorage->getNextForward(curr);


		for (std::string neighbour : neighbours) {
			std::unordered_set<std::string>::const_iterator exist = visited.find(neighbour);
			result.insert(neighbour);
			if (exist == visited.end()) {
				DFSNextTForwardWithSynonym(neighbour, visited, result, filter);

			}
		}

		visited.erase(curr);
	}

}

// DFS search backward to answer Next* queries with synonym
void NextTRelationshipEvaluator::DFSNextTBackwardWithSynonym(std::string curr, std::unordered_set<std::string>& visited,
														std::unordered_set<std::string>& result,
														std::unordered_set<std::string>& filter) {
	std::unordered_set<std::string> cache = getBackwardCache(curr);
	if (cache.size() != 0) {
		std::unordered_set<std::string> intersectionRes = RuntimeRelationshipUtils::getSetIntersection(cache, filter);
		for (auto const& el : intersectionRes) {
			result.insert(el);
		}
	} else {
		visited.insert(curr);

		std::unordered_set<std::string> neighbours = this->nextStorage->getNextBackward(curr);

		for (std::string neighbour : neighbours) {
			std::unordered_set<std::string>::const_iterator exist = visited.find(neighbour);
			result.insert(neighbour);
			if (exist == visited.end()) {
				DFSNextTBackwardWithSynonym(neighbour, visited, result, filter);
			}
		}
		visited.erase(curr);

	}
}

// DFS search to answer Next* queries with 2 synonyms
void NextTRelationshipEvaluator::DFSNextTWithTwoSynonyms(std::unordered_set<std::string>& filter1,
														std::unordered_set<std::string>& filter2,
														std::unordered_map<std::string, std::unordered_set<std::string>>& result_map) {
	for (const auto& ele : filter1) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> result;
		std::string start = ele;
		DFSNextTForwardWithSynonym(start, visited, result, filter2);
		if (!isExistKeyForwardCache(start)) {
			storeForwardCache(start, result);
		}
		result = RuntimeRelationshipUtils::getSetIntersection(result, filter2);
		if (result.size() != 0) {
			result_map[start] = result;
		}
	}
}

std::unordered_set<std::string> NextTRelationshipEvaluator::DFSNextTWildcardForward(std::unordered_set<std::string>& filter1,
	std::unordered_set<std::string>& filter2, std::unordered_set<std::string>& result) {
	std::unordered_set<std::string> ans;
	for (const auto& ele : filter1) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> result;
		std::string start = ele;
		DFSNextTForwardWithSynonym(start, visited, result, filter2);
		if (result.size() != 0) {
			ans.insert(start);
		}
	}
	return ans;
}

std::unordered_set<std::string> NextTRelationshipEvaluator::DFSNextTWildcardBackward(std::unordered_set<std::string>& filter1,
	std::unordered_set<std::string>& filter2, std::unordered_set<std::string>& result) {
	std::unordered_set<std::string> ans;
	for (const auto& ele : filter2) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> result;
		std::string start = ele;
		DFSNextTBackwardWithSynonym(start, visited, result, filter1);
		if (result.size() != 0) {
			ans.insert(start);
		}
	}
	return ans;
}

bool NextTRelationshipEvaluator::getRuntimeRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::NEXT_T) {
		if (firstArgument.getTokenType() == TokenType::INTEGER && secondArgument.getTokenType() == TokenType::INTEGER) {
			return handleConstantConstant(firstArgument, secondArgument);
		} else if (firstArgument.getTokenType() == TokenType::WILDCARD && secondArgument.getTokenType() == TokenType::INTEGER) {
			return handleWildcardConstant(secondArgument);
		} else if (firstArgument.getTokenType() == TokenType::INTEGER && secondArgument.getTokenType() == TokenType::WILDCARD) {
			return handleConstantWildcard(firstArgument);
		}
		else if (firstArgument.getTokenType() == TokenType::WILDCARD && secondArgument.getTokenType() == TokenType::WILDCARD) {
			return handleWildcardWildcard();
		}
	}

	return false;
}

std::unordered_set<std::string> NextTRelationshipEvaluator::getRuntimeRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, std::unordered_set<std::string>& filter) {
	if (relType == RelationshipType::NEXT_T) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> result;
		std::string start = firstArgument.getValue();
		DFSNextTForwardWithSynonym(start, visited, result, filter);
		if (!isExistKeyForwardCache(start)) {
			storeForwardCache(start, result);
		}
		result = RuntimeRelationshipUtils::getSetIntersection(result, filter);
		return result;
	}
	return std::unordered_set<std::string>();
}

std::unordered_set<std::string> NextTRelationshipEvaluator::getRuntimeRelationshipBySecond(RelationshipType relType, TokenObject secondArgument, std::unordered_set<std::string>& filter) {
	if (relType == RelationshipType::NEXT_T) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> result;
		std::string start = secondArgument.getValue();
		DFSNextTBackwardWithSynonym(start, visited, result, filter);
		if (!isExistKeyBackwardCache(start)) {
			storeBackwardCache(start, result);
		}
		result = RuntimeRelationshipUtils::getSetIntersection(result, filter);
		return result;
	}
	return std::unordered_set<std::string>();
}

std::unordered_map<std::string, std::unordered_set<std::string>> NextTRelationshipEvaluator::getAllRuntimeRelationship(RelationshipType relType,
																						std::unordered_set<std::string>& filter1,
																						std::unordered_set<std::string>& filter2) {
	if (relType == RelationshipType::NEXT_T) {
		std::unordered_map<std::string, std::unordered_set<std::string>> result_map;
		DFSNextTWithTwoSynonyms(filter1, filter2, result_map);
		return result_map;
	}
	return std::unordered_map<std::string, std::unordered_set<std::string>>();
}

std::unordered_set<std::string> NextTRelationshipEvaluator::getRuntimeRelationshipWithFirstWildcard(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2) {
	if (relType == RelationshipType::NEXT_T) {
		std::unordered_set<std::string> result;
		return DFSNextTWildcardBackward(filter1, filter2, result);
	}
	return std::unordered_set<std::string>();
}
std::unordered_set<std::string> NextTRelationshipEvaluator::getRuntimeRelationshipWithSecondWildcard(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2) {
	if (relType == RelationshipType::NEXT_T) {
		std::unordered_set<std::string> result;
		return DFSNextTWildcardForward(filter1, filter2, result);
	}
	return std::unordered_set<std::string>();
}

bool NextTRelationshipEvaluator::handleConstantConstant(TokenObject firstArgument, TokenObject secondArgument) {
	std::unordered_set<std::string> visited;
	return DFSNextTForward(firstArgument.getValue(), secondArgument.getValue(), visited);
}

bool NextTRelationshipEvaluator::handleConstantWildcard(TokenObject firstArgument) {
	std::unordered_set<std::string> nextStore = nextStorage->getNextForward(firstArgument.getValue());
	return nextStore.size() != 0;
}

bool NextTRelationshipEvaluator::handleWildcardConstant(TokenObject secondArgument) {
	std::unordered_set<std::string> nextStore = nextStorage->getNextBackward(secondArgument.getValue());
	return nextStore.size() != 0;
}

bool NextTRelationshipEvaluator::handleWildcardWildcard() {
	return !nextStorage->isEmpty();
}
