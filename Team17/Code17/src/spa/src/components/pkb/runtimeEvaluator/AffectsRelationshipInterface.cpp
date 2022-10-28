#include "AffectsRelationshipInterface.h"
#include "utils.h"

AffectsRelationshipInterface::AffectsRelationshipInterface(ModifyRelationshipStorage* modifiesStorage, UsesRelationshipStorage* usesStorage,
	NextRelationshipStorage* nextS0torage) : modifiesStorage(modifiesStorage), usesStorage(usesStorage), nextStorage(nextStorage) {};

void AffectsRelationshipInterface::DFSAffectsForwardWithSynonym(std::string curr, std::string var,
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

// DFS search backward to answer Next* queries with synonym
void AffectsRelationshipInterface::DFSAffectsBackwardWithSynonym(std::string curr, std::unordered_set<std::string>& usesSet,
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
		std::unordered_set<std::string> intersectionSet = RuntimeRelationshipUtils::getIntersectionVar(modifiesSet, usesSet);
		bool isModifiesForBackward = intersectionSet.size() != 0;

		if (isModifiesForBackward) {
			for (auto const& var : intersectionSet) {
				usesSet.erase(var);
			}

			if (filter.find(neighbour) != filter.end() && RuntimeRelationshipUtils::isModifiesAssign(modifiesStorage, neighbour)) {
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

std::unordered_set<std::string> AffectsRelationshipInterface::DFSAffectsWildcardForward(std::unordered_set<std::string>& filter1,
	std::unordered_set<std::string>& filter2, std::unordered_set<std::string>& result) {
	std::unordered_set<std::string> ans;
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
			ans.insert(start);
		}
	}
	return ans;
}

std::unordered_set<std::string> AffectsRelationshipInterface::DFSAffectsWildcardBackward(std::unordered_set<std::string>& filter1,
	std::unordered_set<std::string>& filter2, std::unordered_set<std::string>& result) {
	std::unordered_set<std::string> ans;

	for (const auto& ele : filter2) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> result;
		std::string start = ele;
		std::unordered_set<std::string> usesSet = usesStorage->getUsesForAssign(ele);

		DFSAffectsBackwardWithSynonym(start, usesSet, visited, result, filter1);
		if (result.size() != 0) {
			ans.insert(start);
		}
	}
	return ans;
}

bool AffectsRelationshipInterface::DFSAffectsConstantWildcard(std::string curr, std::string var, std::unordered_set<std::string>& visited) {
	visited.insert(curr);

	std::unordered_set<std::string> neighbours = this->nextStorage->getNextForward(curr);

	for (std::string neighbour : neighbours) {
		std::unordered_set<std::string>::const_iterator exist = visited.find(neighbour);
		if (RuntimeRelationshipUtils::isUses(usesStorage, neighbour, var)
			|| (exist == visited.end() && !RuntimeRelationshipUtils::isModifies(modifiesStorage, neighbour, var)
				&& DFSAffectsConstantWildcard(neighbour, var, visited))) {
			return true;
		}
	}
	return false;
}

bool AffectsRelationshipInterface::DFSAffectsWildcardConstant(std::string curr, std::unordered_set<std::string>& usesSet, std::unordered_set<std::string>& visited) {

	if (usesSet.size() == 0) {
		return false;
	}

	visited.insert(curr);

	std::unordered_set<std::string> neighbours = this->nextStorage->getNextBackward(curr);

	for (std::string neighbour : neighbours) {
		std::unordered_set<std::string>::const_iterator exist = visited.find(neighbour);
		std::unordered_set<std::string> modifiesSet = RuntimeRelationshipUtils::getModifiesForBackward(modifiesStorage, neighbour);
		std::unordered_set<std::string> intersectionSet = RuntimeRelationshipUtils::getIntersectionVar(modifiesSet, usesSet);
		bool isModifiesForBackward = intersectionSet.size() != 0;

		if (isModifiesForBackward) {

			if (RuntimeRelationshipUtils::isModifiesAssign(modifiesStorage, neighbour)) {
				return true;
			}

			for (auto const& var : intersectionSet) {
				usesSet.erase(var);
			}
		}

		if (exist == visited.end() && DFSAffectsWildcardConstant(neighbour, usesSet, visited)) {
			return true;
		}

		if (isModifiesForBackward) {
			for (auto const& var : intersectionSet) {
				usesSet.insert(var);
			}
		}
	}

	visited.erase(curr);
	return false;
}



bool AffectsRelationshipInterface::handleConstantWildcard(TokenObject firstArgument) {
	std::unordered_set<std::string> visited;
	std::unordered_set<std::string> modifiesSet = modifiesStorage->getModifiesForAssign(firstArgument.getValue());
	std::string start = firstArgument.getValue();
	if (modifiesSet.size() != 0) {
		std::string var = *(modifiesSet.begin());
		return DFSAffectsConstantWildcard(start, var, visited);
	}

	return false;
}

bool AffectsRelationshipInterface::handleWildcardConstant(TokenObject secondArgument) {
	std::unordered_set<std::string> visited;
	std::string start = secondArgument.getValue();
	std::unordered_set<std::string> usesSet = usesStorage->getUsesForAssign(start);
	return DFSAffectsWildcardConstant(start, usesSet, visited);
}

bool AffectsRelationshipInterface::handleWildcardWildcard() {
	std::unordered_set<std::string> filter = modifiesStorage->getAllModifiesAssign();
	for (auto const& start : filter) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> modifiesSet = modifiesStorage->getModifiesForAssign(start);
		if (modifiesSet.size() != 0) {
			std::string var = *(modifiesSet.begin());
			if (DFSAffectsConstantWildcard(start, var, visited)) {
				return true;
			}
		}
	}

	return false;
}
