#pragma once

#include "models/Relationship/Relationship.h"

#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"

#include "components/pkb/storage/RelationshipStorage/RelationshipStorage.h"
#include "models/Entity/DesignEntity.h"

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
	bool storeRelationship(Relationship* rel);
	
private:
	std::vector<RelationshipStorage*> relStorages;
};