#pragma once
#include "models/Entity/DesignEntity.h"
#include "EntityStorage.h"
#include <unordered_map>

class EntityMappingStorage : public EntityStorage {

public:
	EntityMappingStorage();
	virtual std::string getStatementMapping(std::string& stmtNumber, DesignEntity entityType) = 0;
	virtual std::unordered_set<std::string> getStatementByName(std::string& name, DesignEntity entityType) = 0;
	virtual std::unordered_set<std::string> getAllName(DesignEntity returnType) = 0;
protected:
	std::unordered_map<std::string, std::string> forwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> backwardMap;
};
