#pragma once
#include "components/pkb/storage/RelationshipStorage/RelationshipStorage.h"
#include "components/pkb/runtimeEvaluator/RuntimeRelationshipEvaluator.h"

#include <string>
#include <vector>

class RelationshipManager {
public:
	RelationshipManager();

	std::vector<RelationshipStorage*> getRelationshipStorage();
	bool getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument);
	std::unordered_set<std::string> getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType);
	std::unordered_set<std::string> getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returnType2);
	bool getRuntimeRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument);
	std::unordered_set<std::string> getRuntimeRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, std::unordered_set<std::string>& filter);
	std::unordered_set<std::string> getRuntimeRelationshipBySecond(RelationshipType relType, TokenObject secondArgument, std::unordered_set<std::string>& filter);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllRuntimeRelationship(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2);
	bool storeRelationship(Relationship* rel);
	void clearCache();
	~RelationshipManager();
	
private:
	std::vector<RelationshipStorage*> relStorages;
	std::vector<RuntimeRelationshipEvaluator*> runtimeRelStorages;
	
};
