#pragma once
#include "models/Entity/DesignEntity.h"


#include "../pkb.h"

#include <string>
#include <unordered_set>

#include "models/Entity/DesignEntity.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenType.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

#include "models/Relationship/RelationshipType.h"

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
	std::unordered_set<std::string> getStatementMapping(std::unordered_set<std::string>& stmtSet, DesignEntity entityType);

	//For Pattern
	std::unordered_set<std::string> getPattern(DesignEntity designEntity, TokenObject firstArgument, TokenObject secondArgument);
	std::vector<std::pair<std::string, std::string>> getPatternPair(DesignEntity designEntity, TokenObject secondArgument);

private:
	PKB* pkb;
};
