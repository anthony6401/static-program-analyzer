#include "AffectsTRelationshipEvaluator.h"
#include "AffectsRelationshipInterface.h"
#include "utils.h"

AffectsTRelationshipEvaluator::AffectsTRelationshipEvaluator(NextRelationshipStorage* nextStorage, ModifyRelationshipStorage* modifiesStorage, UsesRelationshipStorage* usesStorage)
	: AffectsRelationshipInterface(modifiesStorage, usesStorage, nextStorage) {};


void AffectsTRelationshipEvaluator::removeUsesSet(std::unordered_set<std::string>& usesSet, std::unordered_set<std::string>& intersectionSet) {
	for (auto const& var : intersectionSet) {
		usesSet.erase(var);
	}
}

void AffectsTRelationshipEvaluator::insertUsesSet(std::unordered_set<std::string>& usesSet, std::unordered_set<std::string>& intersectionSet) {
	for (auto const& var : intersectionSet) {
		usesSet.insert(var);
	}
}

// DFS search to answer Next* queries with 2 integer values
bool AffectsTRelationshipEvaluator::DFSAffectsTForward(std::string curr, std::string target, std::string var, std::unordered_set<std::string>& visited) {
	if (getForwardCacheKV(curr, target)) {
		return true;
	}
	visited.insert(curr);

	std::unordered_set<std::string> neighbours = this->nextStorage->getNextForward(curr);

	for (std::string neighbour : neighbours) {
		if (target == neighbour && RuntimeRelationshipUtils::isUses(usesStorage, neighbour, var)) {
			return true;
		}
		
		if ((visited.find(neighbour) == visited.end() && (!RuntimeRelationshipUtils::isModifies(modifiesStorage,neighbour, var)) && DFSAffectsTForward(neighbour, target, var, visited))) {
			return true;
		}

		if (visited.find(neighbour) == visited.end()) {
			if (RuntimeRelationshipUtils::isUses(usesStorage,neighbour, var)) {
				std::unordered_set<std::string> modifiesSet = modifiesStorage->getModifiesForAssign(neighbour);

				std::string newVar = *modifiesSet.begin();
				std::unordered_set<std::string> newVisited;

				bool result = DFSAffectsTForward(neighbour, target, newVar, newVisited);

				if (result) {
					return true;
				}
			}
		}
	}

	visited.erase(curr);

	return false;
}

// DFS search forward to answer Affects* queries with synonym
void AffectsTRelationshipEvaluator::DFSAffectsTForwardWithSynonym(std::string curr, std::string var,
																std::unordered_set<std::string>& visited,
																std::unordered_set<std::string>& result,
																std::unordered_set<std::string>& filter) {
	visited.insert(curr);

	std::unordered_set<std::string> neighbours = this->nextStorage->getNextForward(curr);

	for (std::string neighbour : neighbours) {
		if ((filter.find(neighbour) != filter.end()) && RuntimeRelationshipUtils::isUses(usesStorage, neighbour, var) && result.find(neighbour) == result.end()) {
			result.insert(neighbour);
			startNewDFSPath(visited, neighbour, result, filter);
		}

		if (visited.find(neighbour) == visited.end() && !RuntimeRelationshipUtils::isModifies(modifiesStorage, neighbour, var)) {
			DFSAffectsTForwardWithSynonym(neighbour, var, visited, result, filter);
		}
	}

	visited.erase(curr);
}



void AffectsTRelationshipEvaluator::startNewDFSPathForBackward(std::unordered_set<std::string>& result, std::unordered_set<std::string>& filter, std::string neighbour, 
																std::unordered_set<std::string>::const_iterator& exist, std::unordered_set<std::string>& visited) {
	if ((filter.find(neighbour) != filter.end())) {
		result.insert(neighbour);

		if (exist == visited.end()) {
			std::unordered_set<std::string> newUsesSet = usesStorage->getUsesForAssign(neighbour);
			std::unordered_set<std::string> newVisited;
			DFSAffectsTBackwardWithSynonym(neighbour, newUsesSet, newVisited, result, filter);
		}
	}
}

// DFS search backward to answer Affects* queries with synonym
void AffectsTRelationshipEvaluator::DFSAffectsTBackwardWithSynonym(std::string curr, std::unordered_set<std::string>& usesSet,
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
		std::unordered_set<std::string> modifiesSet = RuntimeRelationshipUtils::getModifiesForBackward(modifiesStorage,neighbour);
		std::unordered_set<std::string> intersectionSet = RuntimeRelationshipUtils::getSetIntersection(modifiesSet, usesSet);
		bool isModifiesForBackward = intersectionSet.size() != 0;

		if (isModifiesForBackward) {
			
			removeUsesSet(usesSet, intersectionSet);

			if (result.find(neighbour) == result.end()) {
				startNewDFSPathForBackward(result, filter, neighbour, exist, visited);
			}
		}

		if (exist == visited.end()) {
			DFSAffectsTBackwardWithSynonym(neighbour, usesSet, visited, result, filter);
		}

		if (isModifiesForBackward) {
			insertUsesSet(usesSet, intersectionSet);
		}
	}

	visited.erase(curr);
}

// DFS search to answer Affects* queries with 2 synonyms
void AffectsTRelationshipEvaluator::DFSAffectsTWithTwoSynonyms(std::unordered_set<std::string>& filter1,
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

		if (isExistKeyForwardCache(start)) {
			result = getForwardCache(start);
		} else {
			std::string var = *(modifiesSet.begin());
			DFSAffectsTForwardWithSynonym(start, var, visited, result, filter2);
		}
	
		if (result.size() != 0) {
			result_map[start] = result;
		}
	}
}

std::unordered_set<std::string> AffectsTRelationshipEvaluator::DFSAffectsTWildcardForward(std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2, std::unordered_set<std::string>& result) {
	std::unordered_set<std::string> ans;
	for (auto const& start : filter1) {
		if (isExistKeyForwardCache(start)) {
			if (forwardCache[start].size() != 0) {
				ans.insert(start);
			}
		} else {
			std::unordered_set<std::string> visited;
			std::unordered_set<std::string> result;
			std::unordered_set<std::string> modifiesSet = modifiesStorage->getModifiesForAssign(start);
			if (modifiesSet.size() != 0) {
				std::string var = *(modifiesSet.begin());
				DFSAffectsTForwardWithSynonym(start, var, visited, result, filter2);
				storeForwardCache(start, result);
				if (result.size() != 0) {
					ans.insert(start);
				}
			}
		}
	}
	return ans;
}

std::unordered_set<std::string> AffectsTRelationshipEvaluator::DFSAffectsTWildcardBackward(std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2, std::unordered_set<std::string>& result) {
	std::unordered_set<std::string> ans;
	for (auto const& start : filter2) {
		if (isExistKeyBackwardCache(start)) {
			if (backwardCache[start].size() != 0) {
				ans.insert(start);
			}
		}
		else {
			std::unordered_set<std::string> visited;
			std::unordered_set<std::string> result;
			std::unordered_set<std::string> usesSet = usesStorage->getUsesForAssign(start);
			
			DFSAffectsTBackwardWithSynonym(start, usesSet, visited, result, filter1);
			storeBackwardCache(start, result);
			if (result.size() != 0) {
				ans.insert(start);
			}
		}
	}
	return ans;
}

bool AffectsTRelationshipEvaluator::getRuntimeRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::AFFECTS_T) {
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

std::unordered_set<std::string> AffectsTRelationshipEvaluator::getRuntimeRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, std::unordered_set<std::string>& filter) {
	if (relType == RelationshipType::AFFECTS_T) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> result;
		std::unordered_set<std::string> modifiesSet = modifiesStorage->getModifiesForAssign(firstArgument.getValue());

		if (modifiesSet.size() != 0) {
			std::string var = *(modifiesSet.begin());
			std::string start = firstArgument.getValue();
			if (isExistKeyForwardCache(start)) {
				getForwardCache(start);
			} else {
				DFSAffectsTForwardWithSynonym(start, var, visited, result, filter);
				storeForwardCache(start, result);
			}
			return result;
		}
	}
	return std::unordered_set<std::string>();
}

std::unordered_set<std::string> AffectsTRelationshipEvaluator::getRuntimeRelationshipBySecond(RelationshipType relType, TokenObject secondArgument, std::unordered_set<std::string>& filter) {
	if (relType == RelationshipType::AFFECTS_T) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> result;
		std::unordered_set<std::string> usesSet = usesStorage->getUsesForAssign(secondArgument.getValue());
		std::string start = secondArgument.getValue();
		
		if (isExistKeyBackwardCache(start)) {
			result = getBackwardCache(start);
		} else {
			DFSAffectsTBackwardWithSynonym(start, usesSet, visited, result, filter);
			storeBackwardCache(start, result);

		}
		return result;
	}
	return std::unordered_set<std::string>();
}

std::unordered_map<std::string, std::unordered_set<std::string>> AffectsTRelationshipEvaluator::getAllRuntimeRelationship(RelationshipType relType,
											std::unordered_set<std::string>& filter1,
											std::unordered_set<std::string>& filter2) {
	if (relType == RelationshipType::AFFECTS_T) {
		std::unordered_map<std::string, std::unordered_set<std::string>> result_map;
		DFSAffectsTWithTwoSynonyms(filter1, filter2, result_map);
		return result_map;
	}
	return std::unordered_map<std::string, std::unordered_set<std::string>>();
}

std::unordered_set<std::string> AffectsTRelationshipEvaluator::getRuntimeRelationshipWithFirstWildcard(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2) {
	if (relType == RelationshipType::AFFECTS_T) {
		std::unordered_set<std::string> result;
		return DFSAffectsTWildcardBackward(filter1, filter2, result);
	}
	return std::unordered_set<std::string>();
}

std::unordered_set<std::string> AffectsTRelationshipEvaluator::getRuntimeRelationshipWithSecondWildcard(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2) {
	if (relType == RelationshipType::AFFECTS_T) {
		std::unordered_set<std::string> result;
		return DFSAffectsTWildcardForward(filter1, filter2, result);
	}
	return std::unordered_set<std::string>();
}

void AffectsTRelationshipEvaluator::startNewDFSPath(std::unordered_set<std::string>& visited, std::string neighbour, std::unordered_set<std::string>& result, std::unordered_set<std::string>& filter) {
	if (visited.find(neighbour) == visited.end()) {
		std::unordered_set<std::string> modifiesSet = modifiesStorage->getModifiesForAssign(neighbour);

		std::string newVar = *modifiesSet.begin();
		std::unordered_set<std::string> newVisited;

		DFSAffectsTForwardWithSynonym(neighbour, newVar, newVisited, result, filter);
	}
}

bool AffectsTRelationshipEvaluator::handleConstantConstant(TokenObject firstArgument, TokenObject secondArgument) {
	std::unordered_set<std::string> visited;
	std::unordered_set<std::string> modifiesSet = modifiesStorage->getModifiesForAssign(firstArgument.getValue());


	if (modifiesSet.size() != 0) {
		std::string var = *modifiesSet.begin();
		return DFSAffectsTForward(firstArgument.getValue(), secondArgument.getValue(), var, visited);
	}
	return false;
}
