#pragma once

#include "models/Relationship/Relationship.h"

#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"

#include "components/pkb/storage/RelationshipStorage/RelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/NextRelationshipStorage.h"
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
	bool getNextTRelationship(TokenObject firstArgument, TokenObject secondArgument);
	std::unordered_set<std::string> getNextTRelationshipByFirst(TokenObject firstArgument, DesignEntity returnType, std::unordered_set<std::string>& filter);
	std::unordered_set<std::string> getNextTRelationshipBySecond(DesignEntity returnType, TokenObject secondArgument, std::unordered_set<std::string>& filter);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllNextTRelationship(DesignEntity returnType1, DesignEntity returnType2, std::unordered_set<std::string>& filter);
	bool storeRelationship(Relationship* rel);
	
private:
	std::vector<RelationshipStorage*> relStorages;
	NextRelationshipStorage* nextStorage;
};