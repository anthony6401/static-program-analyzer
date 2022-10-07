#pragma once
#include "models/Entity/DesignEntity.h"
#include "EntityStorage.h"
#include <unordered_map>
#include <unordered_set>

class EntityMappingStorage : public EntityStorage {

public:
	EntityMappingStorage();
	virtual std::unordered_set<std::string> getStatementMapping(std::unordered_set<std::string>& stmtSet, DesignEntity entityType) = 0;
protected:
	std::unordered_map<std::string, std::string> map;
};
