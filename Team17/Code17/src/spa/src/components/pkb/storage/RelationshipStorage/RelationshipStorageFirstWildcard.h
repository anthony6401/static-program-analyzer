#pragma once
#include "RelationshipStorage.h"

class RelationshipStorageFirstWildcard : public RelationshipStorage {

public:
	RelationshipStorageFirstWildcard();
	virtual std::unordered_set<std::string> getRelationshipWithFirstWilcard(RelationshipType relType, DesignEntity returnType) = 0;
};
