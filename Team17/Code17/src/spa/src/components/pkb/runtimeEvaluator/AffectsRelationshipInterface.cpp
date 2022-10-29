#include "AffectsRelationshipInterface.h"
#include "utils.h"

AffectsRelationshipInterface::AffectsRelationshipInterface(ModifyRelationshipStorage* modifiesStorage, UsesRelationshipStorage* usesStorage,
	NextRelationshipStorage* nextStorage) : RuntimeRelationshipEvaluator(), modifiesStorage(modifiesStorage), usesStorage(usesStorage), nextStorage(nextStorage) {};

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
		std::unordered_set<std::string> intersectionSet = RuntimeRelationshipUtils::getSetIntersection(modifiesSet, usesSet);
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
	if (isExistKeyForwardCache(start)) {
		return forwardCache[start].size() != 0 ? true : false;
	}

	if (modifiesSet.size() != 0) {
		std::string var = *(modifiesSet.begin());
		return DFSAffectsConstantWildcard(start, var, visited);
	}

	return false;
}

bool AffectsRelationshipInterface::handleWildcardConstant(TokenObject secondArgument) {
	std::unordered_set<std::string> visited;
	std::string start = secondArgument.getValue();
	if (isExistKeyBackwardCache(start)) {
		return backwardCache[start].size() != 0 ? true : false;
	}
	std::unordered_set<std::string> usesSet = usesStorage->getUsesForAssign(start);
	return DFSAffectsWildcardConstant(start, usesSet, visited);
}

bool AffectsRelationshipInterface::handleWildcardWildcard() {
	std::unordered_set<std::string> filter = modifiesStorage->getAllModifiesAssign();
	for (auto const& start : filter) {
		if (isExistKeyForwardCache(start)) {
			return forwardCache[start].size() != 0 ? true : false;
		}

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
