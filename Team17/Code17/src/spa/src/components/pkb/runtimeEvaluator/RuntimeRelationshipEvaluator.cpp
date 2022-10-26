#include "RuntimeRelationshipEvaluator.h"

RuntimeRelationshipEvaluator::RuntimeRelationshipEvaluator() {}

void RuntimeRelationshipEvaluator::clearCache() {
	forwardCache.clear();
	backwardCache.clear();
}

bool RuntimeRelationshipEvaluator::getForwardCacheKV(std::string key, std::string value) {
	if (forwardCache.find(key) != forwardCache.end()) {
		std::unordered_map<std::string, std::unordered_set<std::string>>::iterator it = forwardCache.find(key);

		if (it->second.find(value) != it->second.end()) {
			return true;
		}
	}

	return false;
}

std::unordered_set<std::string> RuntimeRelationshipEvaluator::getForwardCache(std::string key) {
	if (forwardCache.find(key) != forwardCache.end()) {
		return forwardCache.find(key)->second;
	}

	return std::unordered_set<std::string>();
}

std::unordered_set<std::string> RuntimeRelationshipEvaluator::getBackwardCache(std::string key) {
	if (backwardCache.find(key) != backwardCache.end()) {
		return backwardCache.find(key)->second;
	}

	return std::unordered_set<std::string>();
}

void RuntimeRelationshipEvaluator::storeForwardCache(std::string key, std::string value) {
	if (forwardCache.find(key) == forwardCache.end()) {
		forwardCache.insert({ key, std::unordered_set<std::string>() });
	}
	std::unordered_map<std::string, std::unordered_set<std::string>>::iterator it = forwardCache.find(key);

	it->second.insert(value);
}

void RuntimeRelationshipEvaluator::storeBackwardCache(std::string key, std::string value) {
	if (backwardCache.find(key) == backwardCache.end()) {
		backwardCache.insert({ key, std::unordered_set<std::string>() });
	}
	std::unordered_map<std::string, std::unordered_set<std::string>>::iterator it = backwardCache.find(key);

	it->second.insert(value);
}
