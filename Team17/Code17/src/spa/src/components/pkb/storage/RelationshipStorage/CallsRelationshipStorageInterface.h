#pragma once
#include "RelationshipStorageFirstWildcard.h"

class CallsRelationshipStorageInterface : public RelationshipStorageFirstWildcard {

public:
	CallsRelationshipStorageInterface(RelationshipType relationshipType);
	virtual bool storeRelationship(Relationship* rel) = 0;
	bool getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument);
	std::unordered_set<std::string> getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType);
	std::unordered_set<std::string> getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument);
	std::unordered_set<std::string> getRelationshipWithFirstWildcard(RelationshipType relType, DesignEntity returnType);
	std::unordered_set<std::string> getRelationshipWithSecondWildcard(RelationshipType relType, DesignEntity returnType);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returnType2);

protected:
	bool handleConstantConstant(TokenObject firstArgument, TokenObject secondArgument);
	bool handleConstantWildcard(TokenObject firstArgument);
	bool handleWildcardConstant(TokenObject secondArgument);
	bool handleWilcardWildcard();
	RelationshipType relationshipType;

	// To answer Calls("proc1", "proc2"), Calls("proc1", p), Calls(p1, p2)
	std::unordered_map<std::string, std::unordered_set<std::string>> procForwardStorage;

	// To answer Calls(p, "proc2")
	std::unordered_map<std::string, std::unordered_set<std::string>> procBackwardStorage;
};
