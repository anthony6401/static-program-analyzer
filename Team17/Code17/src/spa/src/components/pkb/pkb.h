#pragma once
#include "./manager/EntityManager.h"
#include "./manager/RelationshipManager.h"
#include "./manager/PatternManager.h"

class PKB {
public:
	PKB();
	//For getting entity
	std::unordered_set<std::string> getAllEntity(DesignEntity returnType);

	// For getting entity mapping
	std::string getStatementMapping(std::string& stmtNumber, DesignEntity entityType);
	std::unordered_set<std::string> getStatementByName(std::string& name, DesignEntity entityType);
	std::unordered_set<std::string> getAllName(DesignEntity entityType);
	
	// For constant
	bool storeConstant(Entity* entity);

	//For relationship
	bool storeRelationship(Relationship* rel);
	bool getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument);
	std::unordered_set<std::string> getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType);
	std::unordered_set<std::string> getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument);
	std::unordered_set<std::string> getRelationshipWithFirstWildcard(RelationshipType relType, DesignEntity returnType);
	std::unordered_set<std::string> getRelationshipWithSecondWildcard(RelationshipType relType, DesignEntity returnType);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returntype2);
	void clearCache();
	
	//For pattern
	bool storePattern(kb::Pattern* pattern);
	std::unordered_set<std::string> getPattern(DesignEntity designEntity, TokenObject firstArgument, TokenObject secondArgument);
	std::unordered_set<std::string> getPatternWildcard(DesignEntity designEntity, TokenObject secondArgument);
	std::vector<std::pair<std::string, std::string>> getPatternPair(DesignEntity designEntity, TokenObject secondArgument);

	//Getters
	EntityManager* getEntityManager();
	RelationshipManager* getRelationshipManager();
	PatternManager* getPatternManager();

	~PKB();

private:
	bool isRuntimeRelationship(RelationshipType relType);
	std::unordered_set<std::string> getFilter(RelationshipType relType, DesignEntity designEntity);
	EntityManager* entityManager;
	RelationshipManager* relManager;
	PatternManager* patternManager;
};