#include "RelationshipManager.h"
#include "components/pkb/storage/RelationshipStorage/RelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/ModifyRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/UsesRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/FollowsRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/FollowsTRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/ParentRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/ParentTRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/CallsRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/CallsTRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/NextRelationshipStorage.h"
#include "components/pkb/runtimeEvaluator/NextTRelationshipEvaluator.h"
#include "components/pkb/runtimeEvaluator/AffectsRelationshipEvaluator.h"
#include "components/pkb/runtimeEvaluator/AffectsTRelationshipEvaluator.h"

RelationshipManager::RelationshipManager() {
	ModifyRelationshipStorage* modifyRelStorage = new ModifyRelationshipStorage();
	UsesRelationshipStorage* usesRelStorage = new UsesRelationshipStorage();
	FollowsRelationshipStorage* followsRelStorage = new FollowsRelationshipStorage();
	FollowsTRelationshipStorage* followsTRelStorage = new FollowsTRelationshipStorage();
	ParentRelationshipStorage* parentRelStorage = new ParentRelationshipStorage();
	ParentTRelationshipStorage* parentTRelStorage = new ParentTRelationshipStorage();
	CallsRelationshipStorage* callsRelStorage = new CallsRelationshipStorage();
	CallsTRelationshipStorage* callsTRelStorage = new CallsTRelationshipStorage();
	NextRelationshipStorage* nextRelStorage = new NextRelationshipStorage();

	NextTRelationshipEvaluator* nextTRelEvaluator = new NextTRelationshipEvaluator(nextRelStorage);
	AffectsRelationshipEvaluator* affectsRelEvaluator = new AffectsRelationshipEvaluator(nextRelStorage, modifyRelStorage, usesRelStorage);
	AffectsTRelationshipEvaluator* affectsTRelEvaluator = new AffectsTRelationshipEvaluator(nextRelStorage, modifyRelStorage, usesRelStorage);

	relStorages.push_back(modifyRelStorage);
	relStorages.push_back(usesRelStorage);
	relStorages.push_back(followsRelStorage);
	relStorages.push_back(followsTRelStorage);
	relStorages.push_back(parentRelStorage);
	relStorages.push_back(parentTRelStorage);
	relStorages.push_back(callsRelStorage);
	relStorages.push_back(callsTRelStorage);
	relStorages.push_back(nextRelStorage);

	relFirstWildcardStorages.push_back(followsRelStorage);
	relFirstWildcardStorages.push_back(followsTRelStorage);
	relFirstWildcardStorages.push_back(parentRelStorage);
	relFirstWildcardStorages.push_back(parentTRelStorage);
	relFirstWildcardStorages.push_back(callsRelStorage);
	relFirstWildcardStorages.push_back(callsTRelStorage);
	relFirstWildcardStorages.push_back(nextRelStorage);

	runtimeRelStorages.push_back(nextTRelEvaluator);
	runtimeRelStorages.push_back(affectsRelEvaluator);
	runtimeRelStorages.push_back(affectsTRelEvaluator);
}

std::vector<RelationshipStorage*> RelationshipManager::getRelationshipStorage() {
	return relStorages;
}

bool RelationshipManager::getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	bool ret = false;

	for (auto& store : relStorages) {
		ret = store->getRelationship(relType, firstArgument, secondArgument);
		if (ret) {
			return ret;
		}
	}
	return false;
}

std::unordered_set<std::string> RelationshipManager::getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType) {
	std::unordered_set<std::string> set = std::unordered_set<std::string>();
	std::unordered_set<std::string> emptySet = std::unordered_set<std::string>();

	for (auto& store : relStorages) {
		set = store->getRelationshipByFirst(relType, firstArgument, returnType);
		if (set != emptySet) {
			return set;
		}
	}
	return emptySet;
}

std::unordered_set<std::string> RelationshipManager::getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument) {
	std::unordered_set<std::string> set = std::unordered_set<std::string>();
	std::unordered_set<std::string> emptySet = std::unordered_set<std::string>();

	for (auto& store : relStorages) {
		set = store->getRelationshipBySecond(relType, returnType, secondArgument);
		if (set != emptySet) {
			return set;
		}
	}
	return emptySet;
}

std::unordered_set<std::string> RelationshipManager::getRelationshipWithFirstWildcard(RelationshipType relType, DesignEntity returnType) {
	std::unordered_set<std::string> set = std::unordered_set<std::string>();
	std::unordered_set<std::string> emptySet = std::unordered_set<std::string>();

	for (auto& store : relFirstWildcardStorages) {
		set = store->getRelationshipWithFirstWildcard(relType, returnType);
		if (set != emptySet) {
			return set;
		}
	}
	return emptySet;
}

std::unordered_set<std::string> RelationshipManager::getRelationshipWithSecondWildcard(RelationshipType relType, DesignEntity returnType) {
	std::unordered_set<std::string> set = std::unordered_set<std::string>();
	std::unordered_set<std::string> emptySet = std::unordered_set<std::string>();

	for (auto& store : relStorages) {
		set = store->getRelationshipWithSecondWildcard(relType, returnType);
		if (set != emptySet) {
			return set;
		}
	}
	return emptySet;
}

std::unordered_set<std::string> RelationshipManager::getRuntimeRelationshipWithFirstWildcard(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2) {
	std::unordered_set<std::string> set = std::unordered_set<std::string>();
	std::unordered_set<std::string> emptySet = std::unordered_set<std::string>();

	for (auto& store : runtimeRelStorages) {
		set = store->getRuntimeRelationshipWithFirstWildcard(relType, filter1, filter2);
		if (set != emptySet) {
			return set;
		}
	}
	return emptySet;
}
std::unordered_set<std::string>RelationshipManager::getRuntimeRelationshipWithSecondWildcard(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2) {
	std::unordered_set<std::string> set = std::unordered_set<std::string>();
	std::unordered_set<std::string> emptySet = std::unordered_set<std::string>();

	for (auto& store : runtimeRelStorages) {
		set = store->getRuntimeRelationshipWithSecondWildcard(relType, filter1, filter2);
		if (set != emptySet) {
			return set;
		}
	}
	return emptySet;
}

std::unordered_map<std::string, std::unordered_set<std::string>> RelationshipManager::getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returnType2) {

	std::unordered_map<std::string, std::unordered_set<std::string>> map = std::unordered_map<std::string, std::unordered_set<std::string>>();
	std::unordered_map<std::string, std::unordered_set<std::string>> emptyMap = std::unordered_map<std::string, std::unordered_set<std::string>>();


	for (auto& store : relStorages) {
		map = store->getAllRelationship(relType, returnType1, returnType2);
		if (map != emptyMap) {
			return map;
		}
	}

	return emptyMap;
}

bool RelationshipManager::storeRelationship(Relationship* rel) {
	bool ret = false;

	for (auto& store : relStorages) {
		bool result = store->storeRelationship(rel);
		ret = ret || result;
	}

	return ret;
}

bool RelationshipManager::getRuntimeRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	bool ret = false;

	for (auto& store : runtimeRelStorages) {
		ret = store->getRuntimeRelationship(relType, firstArgument, secondArgument);
		if (ret) {
			return ret;
		}
	}
	return false;
}

std::unordered_set<std::string> RelationshipManager::getRuntimeRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, std::unordered_set<std::string>& filter) {
	std::unordered_set<std::string> set = std::unordered_set<std::string>();
	std::unordered_set<std::string> emptySet = std::unordered_set<std::string>();

	for (auto& store : runtimeRelStorages) {
		set = store->getRuntimeRelationshipByFirst(relType, firstArgument, filter);
		if (set != emptySet) {
			return set;
		}
	}
	return emptySet;
}

std::unordered_set<std::string> RelationshipManager::getRuntimeRelationshipBySecond(RelationshipType relType, TokenObject secondArgument, std::unordered_set<std::string>& filter) {
	std::unordered_set<std::string> set = std::unordered_set<std::string>();
	std::unordered_set<std::string> emptySet = std::unordered_set<std::string>();

	for (auto& store : runtimeRelStorages) {
		set = store->getRuntimeRelationshipBySecond(relType, secondArgument, filter);
		if (set != emptySet) {
			return set;
		}
	}
	return emptySet;
}

std::unordered_map<std::string, std::unordered_set<std::string>> RelationshipManager::getAllRuntimeRelationship(RelationshipType relType,
																									std::unordered_set<std::string>& filter1,
																									std::unordered_set<std::string>& filter2) {
	std::unordered_map<std::string, std::unordered_set<std::string>> map = std::unordered_map<std::string, std::unordered_set<std::string>>();
	std::unordered_map<std::string, std::unordered_set<std::string>> emptyMap = std::unordered_map<std::string, std::unordered_set<std::string>>();


	for (auto& store : runtimeRelStorages) {
		map = store->getAllRuntimeRelationship(relType, filter1, filter2);
		if (map != emptyMap) {
			return map;
		}
	}

	return emptyMap;
}

RelationshipManager::~RelationshipManager() {
	for (auto store : relStorages) {
		delete store;
	}

	for (auto runtimeStore : runtimeRelStorages) {
		delete runtimeStore;
	}
	relStorages.clear();
	runtimeRelStorages.clear();
}
