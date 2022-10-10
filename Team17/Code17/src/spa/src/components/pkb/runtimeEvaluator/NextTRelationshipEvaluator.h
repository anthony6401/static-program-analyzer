#pragma once
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "models/Relationship/Relationship.h"
#include "models/Relationship/RelationshipType.h"
#include "models/Entity/DesignEntity.h"
#include "components/pkb/storage/RelationshipStorage/NextRelationshipStorage.h"
#include "../../../qps/query_preprocessor/query_tokenizer/TokenObject.h"

class NextTRelationshipEvaluator {

public:
	NextTRelationshipEvaluator(NextRelationshipStorage* nextStorage);
	bool getRuntimeRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument);
	std::unordered_set<std::string> getRuntimeRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, std::unordered_set<std::string>& filter);
	std::unordered_set<std::string> getRuntimeRelationshipBySecond(RelationshipType relType, TokenObject secondArgument, std::unordered_set<std::string>& filter);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllRuntimeRelationship(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2);
private:
	bool DFSNextTForward(std::string curr, std::string target, std::unordered_set<std::string>& visited);
	void DFSNextTForwardWithSynonym(std::string curr, std::unordered_set<std::string>& visited,
						std::unordered_set<std::string>& result, std::unordered_set<std::string>& filter);
	void DFSNextTBackwardWithSynonym(std::string curr, std::unordered_set<std::string>& visited,
		std::unordered_set<std::string>& result, std::unordered_set<std::string>& filter);

	NextRelationshipStorage* nextStorage;
};
