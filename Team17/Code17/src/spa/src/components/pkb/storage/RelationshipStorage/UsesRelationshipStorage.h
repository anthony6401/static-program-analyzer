#pragma once
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "models/Relationship/Relationship.h"
#include "models/Relationship/RelationshipType.h"
#include "RelationshipStorage.h"
#include "../../../qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "../../../qps/query_preprocessor/query_tokenizer/TokenObject.h"

class UsesRelationshipStorage : public RelationshipStorage {

public:
	UsesRelationshipStorage();
	bool storeRelationship(Relationship* rel);
	bool getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument);
	std::unordered_set<std::string>* getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, TokenType returnType);
	std::unordered_set<std::string>* getRelationshipBySecond(RelationshipType relType, TokenType returnType, TokenObject secondArgument);
	std::unordered_set<std::string>* getAllRelationship(RelationshipType relType, TokenType returnType);

private:
	// To answer Uses(1, "x"), Uses(1, v)
	std::unordered_map<std::string, std::unordered_set<std::string>*>* stmtForwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>*>* procForwardStorage;

	// To answer Uses(s, "x"), Uses(a, v)
	std::unordered_map<std::string, std::unordered_set<std::string>*>* procBackwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>*>* assignBackwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>*>* printBackwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>*>* ifBackwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>*>* whileBackwardStorage;
};


