#pragma once
#include "RelationshipStorage.h"

class CallsRelationshipStorage : public RelationshipStorage {

public:
	CallsRelationshipStorage();
	bool storeRelationship(Relationship* rel);
	bool getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument);
	std::unordered_set<std::string> getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType);
	std::unordered_set<std::string> getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returnType2);

private:
	// To answer Calls("proc1", "proc2"), Calls("proc1", p), Calls(p1, p2)
	std::unordered_map<std::string, std::unordered_set<std::string>> procForwardStorage;

	// To answer Calls(p, "proc2")
	std::unordered_map<std::string, std::unordered_set<std::string>> procBackwardStorage;
};
