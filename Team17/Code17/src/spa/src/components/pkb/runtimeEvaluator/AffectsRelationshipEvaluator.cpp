#include "AffectsRelationshipEvaluator.h"
#include "AffectsRelationshipInterface.h"
#include "utils.h"

AffectsRelationshipEvaluator::AffectsRelationshipEvaluator(NextRelationshipStorage* nextStorage, ModifyRelationshipStorage* modifiesStorage, UsesRelationshipStorage* usesStorage)
				: AffectsRelationshipInterface(modifiesStorage, usesStorage, nextStorage) {};


// DFS search to answer Affects queries with 2 integer values
bool AffectsRelationshipEvaluator::DFSAffectsForward(std::string curr, std::string target, std::string var, std::unordered_set<std::string>& visited) {
	if (getForwardCacheKV(curr, target)) {
		return true;
	}
	
	visited.insert(curr);

	std::unordered_set<std::string> neighbours = this->nextStorage->getNextForward(curr);

	for (std::string neighbour : neighbours) {
		if (target == neighbour || (visited.find(neighbour) == visited.end() && !RuntimeRelationshipUtils::isModifies(modifiesStorage ,neighbour, var) && DFSAffectsForward(neighbour, target, var, visited))) {
			return true;
		}
	}

	return false;
}

void AffectsRelationshipEvaluator::DFSAffectsForwardWithSynonym(std::string curr, std::string var,
	std::unordered_set<std::string>& visited, std::unordered_set<std::string>& result,
	std::unordered_set<std::string>& filter) {
	visited.insert(curr);

	std::unordered_set<std::string> neighbours = this->nextStorage->getNextForward(curr);

	for (std::string neighbour : neighbours) {
		std::unordered_set<std::string>::const_iterator exist = visited.find(neighbour);
		if ((filter.find(neighbour) != filter.end()) && RuntimeRelationshipUtils::isUses(usesStorage, neighbour, var)) {
			result.insert(neighbour);
		}
		if (exist == visited.end() && !RuntimeRelationshipUtils::isModifies(modifiesStorage, neighbour, var)) {
			DFSAffectsForwardWithSynonym(neighbour, var, visited, result, filter);
		}
	}
}

// DFS search backward to answer Affects queries with synonym
void AffectsRelationshipEvaluator::DFSAffectsBackwardWithSynonym(std::string curr, std::unordered_set<std::string>& usesSet,
	std::unordered_set<std::string>& visited,
	std::unordered_set<std::string>& result,
	std::unordered_set<std::string>& filter) {

	if (usesSet.size() == 0) {
		return;
	}

	visited.insert(curr);

	std::unordered_set<std::string> neighbours = this->nextStorage->getNextBackward(curr);

	for (std::string neighbour : neighbours) {
		std::unordered_set<std::string>::const_iterator exist = visited.find(neighbour);
		std::unordered_set<std::string> modifiesSet = RuntimeRelationshipUtils::getModifiesForBackward(modifiesStorage, neighbour);
		std::unordered_set<std::string> intersectionSet = RuntimeRelationshipUtils::getSetIntersection(modifiesSet, usesSet);
		bool isModifiesForBackward = intersectionSet.size() != 0;

		if (isModifiesForBackward) {
			for (auto const& var : intersectionSet) {
				usesSet.erase(var);
			}

			if (filter.find(neighbour) != filter.end()) {
				result.insert(neighbour);
			}
		}

		if (exist == visited.end()) {
			DFSAffectsBackwardWithSynonym(neighbour, usesSet, visited, result, filter);
		}

		if (isModifiesForBackward) {
			for (auto const& var : intersectionSet) {
				usesSet.insert(var);
			}
		}
	}

	visited.erase(curr);
}

// DFS search to answer Affects queries with 2 synonyms
void AffectsRelationshipEvaluator::DFSAffectsWithTwoSynonyms(std::unordered_set<std::string>& filter1,
														std::unordered_set<std::string>& filter2,
														std::unordered_map<std::string, std::unordered_set<std::string>>& result_map) {
	for (const auto& ele : filter1) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> result;
		std::string start = ele;
		std::unordered_set<std::string> modifiesSet = modifiesStorage->getModifiesForAssign(start);

		if (modifiesSet.size() == 0) {
			continue;
		}

		std::string var = *(modifiesSet.begin());
		
		if (isExistKeyForwardCache(start)) {
			result = getForwardCache(start);
		}else {
			DFSAffectsForwardWithSynonym(start, var, visited, result, filter2);
		}

		if (result.size() != 0) {
			result_map[start] = result;
		}
	}
}

std::unordered_set<std::string> AffectsRelationshipEvaluator::DFSAffectsWildcardForward(std::unordered_set<std::string>& filter1,
	std::unordered_set<std::string>& filter2, std::unordered_set<std::string>& result) {
	std::unordered_set<std::string> ans;
	for (const auto& ele : filter1) {
		std::string start = ele;

		if (isExistKeyForwardCache(start)) {
			if (forwardCache[start].size() != 0) {
				ans.insert(start);
			} 
		} else {
			std::unordered_set<std::string> modifiesSet = modifiesStorage->getModifiesForAssign(start);
			if (modifiesSet.size() == 0) {
				continue;
			}
			std::unordered_set<std::string> visited;
			std::unordered_set<std::string> result;
			std::string var = *(modifiesSet.begin());
			DFSAffectsForwardWithSynonym(start, var, visited, result, filter2);
			storeForwardCache(start, result);
			if (result.size() != 0) {
				ans.insert(start);
			}
		}
	}
	return ans;
}

std::unordered_set<std::string> AffectsRelationshipEvaluator::DFSAffectsWildcardBackward(std::unordered_set<std::string>& filter1,
	std::unordered_set<std::string>& filter2, std::unordered_set<std::string>& result) {
	std::unordered_set<std::string> ans;

	for (const auto& ele : filter2) {
		std::string start = ele;

		if (isExistKeyBackwardCache(start)) {
			if (backwardCache[start].size() != 0) {
				ans.insert(start);
			}
		}
		else {
			std::unordered_set<std::string> visited;
			std::unordered_set<std::string> result;
			std::unordered_set<std::string> usesSet = usesStorage->getUsesForAssign(ele);

			DFSAffectsBackwardWithSynonym(start, usesSet, visited, result, filter1);
			storeBackwardCache(start, result);
			if (result.size() != 0) {
				ans.insert(start);
			}
		}
	}
	return ans;
}

bool AffectsRelationshipEvaluator::getRuntimeRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::AFFECTS) {

		if (firstArgument.getTokenType() == TokenType::INTEGER && secondArgument.getTokenType() == TokenType::INTEGER) {
			return handleConstantConstant(firstArgument, secondArgument);
		} else if (firstArgument.getTokenType() == TokenType::WILDCARD && secondArgument.getTokenType() == TokenType::INTEGER) {
			return handleWildcardConstant(secondArgument);
		} else if (firstArgument.getTokenType() == TokenType::INTEGER && secondArgument.getTokenType() == TokenType::WILDCARD) {
			return handleConstantWildcard(firstArgument);
		} else if (firstArgument.getTokenType() == TokenType::WILDCARD && secondArgument.getTokenType() == TokenType::WILDCARD) {
			return handleWildcardWildcard();
		}
	}

	return false;
}


std::unordered_set<std::string> AffectsRelationshipEvaluator::getRuntimeRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, std::unordered_set<std::string>& filter) {
	if (relType == RelationshipType::AFFECTS) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> result;
		std::unordered_set<std::string> modifiesSet = modifiesStorage->getModifiesForAssign(firstArgument.getValue());

		if (modifiesSet.size() != 0) {
			std::string var = *(modifiesSet.begin());
			std::string start = firstArgument.getValue();
			if (isExistKeyForwardCache(start)) {
				result = getForwardCache(start);
			} else {
				DFSAffectsForwardWithSynonym(start, var, visited, result, filter);
				storeForwardCache(start, result);
			}
			return result;
		}
	}
	return std::unordered_set<std::string>();
}

std::unordered_set<std::string> AffectsRelationshipEvaluator::getRuntimeRelationshipBySecond(RelationshipType relType, TokenObject secondArgument, std::unordered_set<std::string>& filter) {
	if (relType == RelationshipType::AFFECTS) {
		std::string start = secondArgument.getValue();
		std::unordered_set<std::string> result;

		if (isExistKeyBackwardCache(start)) {
			result = getBackwardCache(start);
		} else {
			std::unordered_set<std::string> visited;
			std::unordered_set<std::string> usesSet = usesStorage->getUsesForAssign(secondArgument.getValue());
			DFSAffectsBackwardWithSynonym(start, usesSet, visited, result, filter);
			storeBackwardCache(start, result);
		}
		
		return result;
	}
	return std::unordered_set<std::string>();
}

std::unordered_map<std::string, std::unordered_set<std::string>> AffectsRelationshipEvaluator::getAllRuntimeRelationship(RelationshipType relType,
																												std::unordered_set<std::string>& filter1,
																												std::unordered_set<std::string>& filter2) {
	if (relType == RelationshipType::AFFECTS) {
		std::unordered_map<std::string, std::unordered_set<std::string>> result_map;
		DFSAffectsWithTwoSynonyms(filter1, filter2, result_map);
		return result_map;
	}
	return std::unordered_map<std::string, std::unordered_set<std::string>>();
}

std::unordered_set<std::string> AffectsRelationshipEvaluator::getRuntimeRelationshipWithFirstWildcard(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2) {
	if (relType == RelationshipType::AFFECTS) {
		std::unordered_set<std::string> result;
		return DFSAffectsWildcardBackward(filter1, filter2, result);
	}
	return std::unordered_set<std::string>();
}

std::unordered_set<std::string> AffectsRelationshipEvaluator::getRuntimeRelationshipWithSecondWildcard(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2) {
	if (relType == RelationshipType::AFFECTS) {
		std::unordered_set<std::string> result;
		return DFSAffectsWildcardForward(filter1, filter2, result);
	}
	return std::unordered_set<std::string>();
}

bool AffectsRelationshipEvaluator::handleConstantConstant(TokenObject firstArgument, TokenObject secondArgument) {
	std::unordered_set<std::string> visited;
	std::unordered_set<std::string> modifiesSet = modifiesStorage->getModifiesForAssign(firstArgument.getValue());
	std::unordered_set<std::string> usesSet = usesStorage->getUsesForAssign(secondArgument.getValue());
	std::unordered_set<std::string> varSet = RuntimeRelationshipUtils::getSetIntersection(modifiesSet, usesSet);

	if (varSet.size() != 0) {
		std::string var = *varSet.begin();
		return DFSAffectsForward(firstArgument.getValue(), secondArgument.getValue(), var, visited);
	}
	return false;
}
