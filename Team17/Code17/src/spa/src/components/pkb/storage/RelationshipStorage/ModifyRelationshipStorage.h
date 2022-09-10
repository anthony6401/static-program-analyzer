#pragma once
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "models/Relationship/Relationship.h"
#include "models/Relationship/RelationshipType.h"
#include "RelationshipStorage.h"
#include "../../../qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "../../../qps/query_preprocessor/query_tokenizer/TokenObject.h"

class ModifyRelationshipStorage : public RelationshipStorage {

public:
	ModifyRelationshipStorage();
	bool storeRelationship(Relationship* rel);
	bool getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument);
	std::unordered_set<std::string> getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType);
	std::unordered_set<std::string> getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returnType2);

private:
	// To answer Uses(1, "x"), Uses(1, v)
	std::unordered_map<std::string, std::unordered_set<std::string>> assignForwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>> readForwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>> ifForwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>> whileForwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>> procForwardStorage;

	// To answer Uses(s, "x"), Uses(a, v)
	std::unordered_map<std::string, std::unordered_set<std::string>> procBackwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>> assignBackwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>> readBackwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>> ifBackwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>> whileBackwardStorage;
};
