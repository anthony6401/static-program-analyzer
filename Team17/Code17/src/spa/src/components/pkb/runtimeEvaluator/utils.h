#pragma once

#include "components/pkb/storage/RelationshipStorage/ModifyRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/UsesRelationshipStorage.h"

#include <unordered_set>

class RuntimeRelationshipUtils {
public:
	static bool isModifies(ModifyRelationshipStorage* modifiesStorage, std::string target, std::string var) {
		std::unordered_set<std::string> modifiesSet = modifiesStorage->getModifiesForAffects(target);
		return modifiesSet.find(var) != modifiesSet.end();
	}

	static std::unordered_set<std::string> getModifiesForBackward(ModifyRelationshipStorage* modifiesStorage, std::string target) {
		return modifiesStorage->getModifiesForAffects(target);
	}

	static bool isUses(UsesRelationshipStorage* usesStorage, std::string target, std::string var) {
		std::unordered_set<std::string> usesSet = usesStorage->getUsesForAssign(target);
		return usesSet.find(var) != usesSet.end();
	}

	static std::unordered_set<std::string> getIntersectionVar(std::unordered_set<std::string>& modifiesSet, std::unordered_set<std::string>& usesSet) {
		std::unordered_set<std::string> result;
		for (auto const& modifiesVar : modifiesSet) {
			if (usesSet.find(modifiesVar) != usesSet.end()) {
				result.insert(modifiesVar);
			}
		}

		return result;
	}
};