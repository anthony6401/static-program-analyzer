#pragma once
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "models/Relationship/Relationship.h"
#include "models/Relationship/RelationshipType.h"
#include "models/Entity/DesignEntity.h"
#include "AffectsRelationshipInterface.h"
#include "components/pkb/storage/RelationshipStorage/NextRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/ModifyRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/UsesRelationshipStorage.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

class AffectsRelationshipEvaluator : public AffectsRelationshipInterface {

public:
	AffectsRelationshipEvaluator(NextRelationshipStorage* nextStorage, ModifyRelationshipStorage* modifiesStorage, UsesRelationshipStorage* usesStorage);
	bool getRuntimeRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument);
	std::unordered_set<std::string> getRuntimeRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, std::unordered_set<std::string>& filter);
	std::unordered_set<std::string> getRuntimeRelationshipBySecond(RelationshipType relType, TokenObject secondArgument, std::unordered_set<std::string>& filter);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllRuntimeRelationship(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2);
	std::unordered_set<std::string> getRuntimeRelationshipWithFirstWildcard(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2);
	std::unordered_set<std::string> getRuntimeRelationshipWithSecondWildcard(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2);
private:
	bool DFSAffectsForward(std::string curr, std::string target, std::string var, std::unordered_set<std::string>& visited);
	void DFSAffectsWithTwoSynonyms(std::unordered_set<std::string>& filter1,
		std::unordered_set<std::string>& filter2,
		std::unordered_map<std::string, std::unordered_set<std::string>>& result_map);
	bool handleConstantConstant(TokenObject firstArgument, TokenObject secondArgument);
};
