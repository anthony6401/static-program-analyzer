#pragma once
#include <unordered_set>
#include <string>
#include "models/Relationship/Relationship.h"
#include "models/Relationship/RelationshipType.h"
#include "../../../qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "../../../qps/query_preprocessor/query_tokenizer/TokenObject.h"

class RelationshipStorage {

public:
	RelationshipStorage();
	virtual bool storeRelationship(Relationship* rel) = 0;
	virtual bool getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) = 0;
	virtual std::unordered_set<std::string> getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, TokenType returnType) = 0;
	virtual std::unordered_set<std::string> getRelationshipBySecond(RelationshipType relType, TokenType returnType, TokenObject secondArgument) = 0;
	virtual std::unordered_set<std::string> getAllRelationship(RelationshipType relType, TokenType returnType) = 0;
};