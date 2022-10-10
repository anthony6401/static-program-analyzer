#pragma once
#include "../pkb.h"

class QPSClient {

public:

	QPSClient(PKB *knowledge);

	//For getting entity
	std::unordered_set<std::string> getAllEntity(DesignEntity returnType);

	//For Relationship
	bool storeRelationship(Relationship* rel);
	bool getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument);
	std::unordered_set<std::string> getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType);
	std::unordered_set<std::string> getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returntype2);
	std::string getStatementMapping(std::string& stmtNumber, DesignEntity entityType);

	//For Pattern
	std::unordered_set<std::string> getPattern(DesignEntity designEntity, TokenObject firstArgument, TokenObject secondArgument);
	std::unordered_set<std::string> getContainerPattern(DesignEntity designEntity, TokenObject firstArgument);
	std::vector<std::pair<std::string, std::string>> getPatternPair(DesignEntity designEntity, TokenObject secondArgument);
	std::vector<std::pair<std::string, std::string>> getContainerPatternPair(DesignEntity designEntity);

private:
	PKB* pkb;
};
