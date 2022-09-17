#pragma once

#include "../../models/Relationship/Relationship.h"
#include  "models/Entity/Entity.h"
#include  "models/Entity/DesignEntity.h"

#include "./manager/EntityManager.h"
#include "./manager/RelationshipManager.h"
#include "./manager/PatternManager.h"

#include "../qps/query_preprocessor/query_tokenizer/TokenType.h"

#include <unordered_set>

class PKB {
public:
	PKB();
	//For getting entity
	std::unordered_set<std::string> getAllEntity(DesignEntity returnType);
	
	// For constant
	bool storeConstant(Entity* entity);

	//For relationship
	bool storeRelationship(Relationship* rel);
	bool getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument);
	std::unordered_set<std::string> getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType);
	std::unordered_set<std::string> getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returntype2);
	
	//For pattern
	bool storePattern(kb::Pattern* pattern);
	std::unordered_set<std::string> getPattern(DesignEntity designEntity, TokenObject firstArgument, TokenObject secondArgument);
	std::vector<std::pair<std::string, std::string>> getPatternPair(DesignEntity designEntity, TokenObject secondArgument);

	//Getters
	EntityManager* getEntityManager();
	RelationshipManager* getRelationshipManager();
	PatternManager* getPatternManager();

private:
	//Add managers
	EntityManager* entityManager;
	RelationshipManager* relManager;
	PatternManager* patternManager;
};