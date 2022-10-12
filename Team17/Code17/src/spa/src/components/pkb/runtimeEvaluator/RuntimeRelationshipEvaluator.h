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
	virtual std::unordered_map<std::string, std::unordered_set<std::string>> getAllRuntimeRelationship(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2) = 0;
};
