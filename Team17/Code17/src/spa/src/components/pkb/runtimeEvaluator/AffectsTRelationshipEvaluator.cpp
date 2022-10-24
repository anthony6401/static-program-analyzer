#include "AffectsTRelationshipEvaluator.h"
#include "utils.h"

AffectsTRelationshipEvaluator::AffectsTRelationshipEvaluator(NextRelationshipStorage* nextStorage, ModifyRelationshipStorage* modifiesStorage, UsesRelationshipStorage* usesStorage)
	: nextStorage(nextStorage),
	modifiesStorage(modifiesStorage),
	usesStorage(usesStorage) {}


bool AffectsTRelationshipEvaluator::isModifiesAssign(std::string target) {
	std::unordered_set<std::string> modifiesSet = modifiesStorage->getModifiesForAssign(target);
	return modifiesSet.size() != 0;
}


// DFS search to answer Next* queries with 2 integer values
bool AffectsTRelationshipEvaluator::DFSAffectsTForward(std::string curr, std::string target, std::string var, std::unordered_set<std::string>& visited) {
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


// DFS search forward to answer Next* queries with synonym
void AffectsTRelationshipEvaluator::DFSAffectsTForwardWithSynonym(std::string curr, std::string var,
																std::unordered_set<std::string>& visited,
																std::unordered_set<std::string>& result,
																std::unordered_set<std::string>& filter) {
	visited.insert(curr);

	std::unordered_set<std::string> neighbours = this->nextStorage->getNextForward(curr);

	for (std::string neighbour : neighbours) {
		if ((filter.find(neighbour) != filter.end()) && RuntimeRelationshipUtils::isUses(usesStorage, neighbour, var)) {
			result.insert(neighbour);
			startNewDFSPath(visited, neighbour, result, filter);
		}

		if (visited.find(neighbour) == visited.end() && !RuntimeRelationshipUtils::isModifies(modifiesStorage,neighbour, var)) {
			DFSAffectsTForwardWithSynonym(neighbour, var, visited, result, filter);
		}
	}

	visited.erase(curr);
}

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

void AffectsTRelationshipEvaluator::startNewDFSPathForBackward(std::unordered_set<std::string>& result, std::unordered_set<std::string>& filter, std::string neighbour, 
																std::unordered_set<std::string>::const_iterator& exist, std::unordered_set<std::string>& visited) {
	if ((filter.find(neighbour) != filter.end()) && isModifiesAssign(neighbour)) {
		result.insert(neighbour);

		if (exist == visited.end()) {
			std::unordered_set<std::string> newUsesSet = usesStorage->getUsesForAssign(neighbour);
			std::unordered_set<std::string> newVisited;
			DFSAffectsTBackwardWithSynonym(neighbour, newUsesSet, newVisited, result, filter);
		}
	}
}

// DFS search backward to answer Next* queries with synonym
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
		std::unordered_set<std::string> intersectionSet = RuntimeRelationshipUtils::getIntersectionVar(modifiesSet, usesSet);
		bool isModifiesForBackward = intersectionSet.size() != 0;

		if (isModifiesForBackward) {
			
			removeUsesSet(usesSet, intersectionSet);

			startNewDFSPathForBackward(result, filter, neighbour, exist, visited);
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

// DFS search to answer Next* queries with 2 synonyms
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

		std::string var = *(modifiesSet.begin());
		DFSAffectsTForwardWithSynonym(start, var, visited, result, filter2);
		if (result.size() != 0) {
			result_map[start] = result;
		}
	}
}

bool AffectsTRelationshipEvaluator::getRuntimeRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::AFFECTS_T) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> modifiesSet = modifiesStorage->getModifiesForAssign(firstArgument.getValue());


		if (modifiesSet.size() != 0) {
			std::string var = *modifiesSet.begin();
			return DFSAffectsTForward(firstArgument.getValue(), secondArgument.getValue(), var, visited);
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
			DFSAffectsTForwardWithSynonym(firstArgument.getValue(), var, visited, result, filter);
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
		DFSAffectsTBackwardWithSynonym(secondArgument.getValue(), usesSet, visited, result, filter);
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

void AffectsTRelationshipEvaluator::startNewDFSPath(std::unordered_set<std::string>& visited, std::string neighbour, std::unordered_set<std::string>& result, std::unordered_set<std::string>& filter) {
	if (visited.find(neighbour) == visited.end()) {
		std::unordered_set<std::string> modifiesSet = modifiesStorage->getModifiesForAssign(neighbour);

		std::string newVar = *modifiesSet.begin();
		std::unordered_set<std::string> newVisited;

		DFSAffectsTForwardWithSynonym(neighbour, newVar, newVisited, result, filter);
	}
}
