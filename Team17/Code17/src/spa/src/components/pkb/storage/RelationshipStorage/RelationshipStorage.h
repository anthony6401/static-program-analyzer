#pragma once
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "models/Relationship/Relationship.h"
#include "models/Relationship/RelationshipType.h"
#include "models/Entity/DesignEntity.h"
#include "../../../qps/query_preprocessor/query_tokenizer/TokenObject.h"

class RelationshipStorage {

public:
	RelationshipStorage();
	virtual bool storeRelationship(Relationship* rel) = 0;
	virtual bool getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) = 0;
	virtual std::unordered_set<std::string> getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType) = 0;
	virtual std::unordered_set<std::string> getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument) = 0;
	virtual std::unordered_set<std::string> getRelationshipWithSecondWildcard(RelationshipType relType, DesignEntity returnType) = 0;
	virtual std::unordered_map<std::string, std::unordered_set<std::string>> getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returnType2) = 0;
	~RelationshipStorage() = default;
};
