#pragma once
#include "RelationshipStorage.h"

class ModifyRelationshipStorage : public RelationshipStorage {

public:
	ModifyRelationshipStorage();
	bool storeRelationship(Relationship* rel);
	bool getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument);
	std::unordered_set<std::string> getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType);
	std::unordered_set<std::string> getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returnType2);
	std::unordered_set<std::string> getModifiesForAssign(TokenObject stmtArgument);
	std::unordered_set<std::string> getModifiesForAffects(std::string stmt);

private:
	std::unordered_map<std::string, std::unordered_set<std::string>>* getStorageForward(DesignEntity designEntity);
	std::unordered_map<std::string, std::unordered_set<std::string>>* getStorageBackward(DesignEntity designEntity);
	std::unordered_set<std::string>* getSetByFirst(TokenObject firstArgument);
	std::unordered_set<std::string>* getSetBySecond(TokenObject secondArgument);
	// To answer Uses(1, "x"), Uses(1, v)
	std::unordered_map<std::string, std::unordered_set<std::string>> assignForwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>> readForwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>> ifForwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>> whileForwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>> procForwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>> callsForwardStorage;

	// To answer Uses(s, "x"), Uses(a, v)
	std::unordered_map<std::string, std::unordered_set<std::string>> procBackwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>> assignBackwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>> readBackwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>> ifBackwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>> whileBackwardStorage;
	std::unordered_map<std::string, std::unordered_set<std::string>> callsBackwardStorage;
};
