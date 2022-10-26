#include "AffectsRelationshipEvaluator.h"
#include "utils.h"

AffectsRelationshipEvaluator::AffectsRelationshipEvaluator(NextRelationshipStorage* nextStorage, ModifyRelationshipStorage* modifiesStorage, UsesRelationshipStorage* usesStorage) 
														: nextStorage(nextStorage),
														  modifiesStorage(modifiesStorage),
														  usesStorage(usesStorage) {}


// DFS search to answer Next* queries with 2 integer values
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

// DFS search forward to answer Next* queries with synonym
void AffectsRelationshipEvaluator::DFSAffectsForwardWithSynonym(std::string curr, std::string var,
																std::unordered_set<std::string>& visited,
																std::unordered_set<std::string>& result,
																std::unordered_set<std::string>& filter) {
	std::unordered_set<std::string> cache = getForwardCache(curr);
	if (cache.size() != 0) {
		std::unordered_set<std::string> intersectionRes = RuntimeRelationshipUtils::getSetIntersection(cache, filter);
		for (auto const& el : intersectionRes) {
			result.insert(el);
		}
		return;
	}
	visited.insert(curr);

	std::unordered_set<std::string> neighbours = this->nextStorage->getNextForward(curr);

	for (std::string neighbour : neighbours) {
		std::unordered_set<std::string>::const_iterator exist = visited.find(neighbour);
		if ((filter.find(neighbour) != filter.end()) && RuntimeRelationshipUtils::isUses(usesStorage,neighbour, var)) {
			result.insert(neighbour);
		}
		if (exist == visited.end() && !RuntimeRelationshipUtils::isModifies(modifiesStorage,neighbour, var)) {
			DFSAffectsForwardWithSynonym(neighbour, var, visited, result, filter);
		}
	}
}

// DFS search backward to answer Next* queries with synonym
void AffectsRelationshipEvaluator::DFSAffectsBackwardWithSynonym(std::string curr, std::unordered_set<std::string>& usesSet,
															std::unordered_set<std::string>& visited,
															std::unordered_set<std::string>& result,
															std::unordered_set<std::string>& filter) {

	if (usesSet.size() == 0) {
		return;
	}

	std::unordered_set<std::string> cache = getBackwardCache(curr);
	if (cache.size() != 0) {
		std::unordered_set<std::string> intersectionRes = RuntimeRelationshipUtils::getSetIntersection(cache, filter);
		for (auto const& el : intersectionRes) {
			result.insert(el);
		}
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
			for (auto const& var : intersectionSet) {
				usesSet.erase(var);
			}

			if ((filter.find(neighbour) != filter.end())) {
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

// DFS search to answer Next* queries with 2 synonyms
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
		DFSAffectsForwardWithSynonym(start, var, visited, result, filter2);
		if (result.size() != 0) {
			result_map[start] = result;
		}
	}
}

bool AffectsRelationshipEvaluator::getRuntimeRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::AFFECTS) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> modifiesSet = modifiesStorage->getModifiesForAssign(firstArgument.getValue());
		std::unordered_set<std::string> usesSet = usesStorage->getUsesForAssign(secondArgument.getValue());
		std::unordered_set<std::string> varSet = RuntimeRelationshipUtils::getSetIntersection(modifiesSet, usesSet);

		if (varSet.size() != 0) {
			std::string var = *varSet.begin();
			return DFSAffectsForward(firstArgument.getValue(), secondArgument.getValue(), var, visited);
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
			DFSAffectsForwardWithSynonym(start, var, visited, result, filter);
			if (!isExistKeyForwardCache(start)) {
				storeForwardCache(start, result);
			}
			return result;
		}
	}
	return std::unordered_set<std::string>();
}

std::unordered_set<std::string> AffectsRelationshipEvaluator::getRuntimeRelationshipBySecond(RelationshipType relType, TokenObject secondArgument, std::unordered_set<std::string>& filter) {
	if (relType == RelationshipType::AFFECTS) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> result;
		std::unordered_set<std::string> usesSet = usesStorage->getUsesForAssign(secondArgument.getValue());
		std::string start = secondArgument.getValue();
		DFSAffectsBackwardWithSynonym(start, usesSet, visited, result, filter);
		if (!isExistKeyBackwardCache(start)) {
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
