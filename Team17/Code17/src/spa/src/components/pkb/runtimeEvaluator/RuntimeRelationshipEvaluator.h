#pragma once
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "models/Relationship/Relationship.h"
#include "models/Relationship/RelationshipType.h"
#include "models/Entity/DesignEntity.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

class RuntimeRelationshipEvaluator {

public:
	RuntimeRelationshipEvaluator();
	virtual bool getRuntimeRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) = 0;
	virtual std::unordered_set<std::string> getRuntimeRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, std::unordered_set<std::string>& filter) = 0;
	virtual std::unordered_set<std::string> getRuntimeRelationshipBySecond(RelationshipType relType, TokenObject secondArgument, std::unordered_set<std::string>& filter) = 0;
	void clearCache();
	virtual std::unordered_map<std::string, std::unordered_set<std::string>> getAllRuntimeRelationship(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2) = 0;
	~RuntimeRelationshipEvaluator() = default;

protected:
	bool getForwardCacheKV(std::string key, std::string value);
	bool isExistKeyForwardCache(std::string key);
	bool isExistKeyBackwardCache(std::string key);
	std::unordered_set<std::string> getForwardCache(std::string key);
	std::unordered_set<std::string> getBackwardCache(std::string key);
	void storeForwardCache(std::string key, std::unordered_set<std::string> set);
	void storeBackwardCache(std::string key, std::unordered_set<std::string> set);
	std::unordered_map<std::string, std::unordered_set<std::string>> forwardCache;
	std::unordered_map<std::string, std::unordered_set<std::string>> backwardCache;
};
