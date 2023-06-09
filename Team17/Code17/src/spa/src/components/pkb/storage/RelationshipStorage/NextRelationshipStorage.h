#pragma once
#include "RelationshipStorageFirstWildcard.h"

class NextRelationshipStorage : public RelationshipStorageFirstWildcard {
public:
	NextRelationshipStorage();
	bool storeRelationship(Relationship* rel);
	bool getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument);
	std::unordered_set<std::string> getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType);
	std::unordered_set<std::string> getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument);
	std::unordered_set<std::string> getRelationshipWithFirstWildcard(RelationshipType relType, DesignEntity returnType);
	std::unordered_set<std::string> getRelationshipWithSecondWildcard(RelationshipType relType, DesignEntity returnType);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returntype2);
	std::unordered_set<std::string> getNextForward(std::string c);
	std::unordered_set<std::string> getNextBackward(std::string c);
	bool isEmpty();

private:
	bool handleConstantConstant(TokenObject firstArgument, TokenObject secondArgument);
	bool handleConstantWildcard(TokenObject firstArgument);
	bool handleWildcardConstant(TokenObject secondArgument);
	bool handleWilcardWildcard();
	std::unordered_map<std::string, std::unordered_set<std::string>>* getReadSpecificEntityStorage(DesignEntity right);
	std::unordered_map<std::string, std::unordered_set<std::string>>* getPrintSpecificEntityStorage(DesignEntity right);
	std::unordered_map<std::string, std::unordered_set<std::string>>* getAssignSpecificEntityStorage(DesignEntity right);
	std::unordered_map<std::string, std::unordered_set<std::string>>* getCallSpecificEntityStorage(DesignEntity right);
	std::unordered_map<std::string, std::unordered_set<std::string>>* getWhileSpecificEntityStorage(DesignEntity right);
	std::unordered_map<std::string, std::unordered_set<std::string>>* getIfSpecificEntityStorage(DesignEntity right);
	std::unordered_map<std::string, std::unordered_set<std::string>>* getStmtSpecificEntityStorage(DesignEntity right);
	std::unordered_map<std::string, std::unordered_set<std::string>>* getStorageForward(DesignEntity left, DesignEntity right);
	std::unordered_map<std::string, std::unordered_set<std::string>>* getStorageBackward(DesignEntity left);

	std::unordered_map<std::string, std::unordered_set<std::string>> readToReadForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> readToPrintForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> readToAssignForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> readToCallForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> readToWhileForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> readToIfForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> readToStmtForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> readToStmtBackwardMap;

	std::unordered_map<std::string, std::unordered_set<std::string>> printToReadForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> printToPrintForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> printToAssignForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> printToCallForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> printToWhileForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> printToIfForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> printToStmtForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> printToStmtBackwardMap;

	std::unordered_map<std::string, std::unordered_set<std::string>> assignToReadForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> assignToPrintForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> assignToAssignForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> assignToCallForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> assignToWhileForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> assignToIfForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> assignToStmtForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> assignToStmtBackwardMap;

	std::unordered_map<std::string, std::unordered_set<std::string>> callToReadForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> callToPrintForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> callToAssignForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> callToCallForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> callToWhileForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> callToIfForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> callToStmtForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> callToStmtBackwardMap;

	std::unordered_map<std::string, std::unordered_set<std::string>> whileToReadForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> whileToPrintForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> whileToAssignForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> whileToCallForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> whileToWhileForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> whileToIfForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> whileToStmtForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> whileToStmtBackwardMap;

	std::unordered_map<std::string, std::unordered_set<std::string>> ifToReadForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> ifToPrintForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> ifToAssignForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> ifToCallForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> ifToWhileForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> ifToIfForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> ifToStmtForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> ifToStmtBackwardMap;

	std::unordered_map<std::string, std::unordered_set<std::string>> stmtToReadForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtToPrintForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtToAssignForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtToCallForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtToWhileForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtToIfForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtToStmtForwardMap;
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtToStmtBackwardMap;
};
