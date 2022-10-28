#pragma once
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "RuntimeRelationshipEvaluator.h"
#include "models/Relationship/RelationshipType.h"
#include "RuntimeRelationshipEvaluator.h"
#include "AffectsRelationshipInterface.h"
#include "components/pkb/storage/RelationshipStorage/NextRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/ModifyRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/UsesRelationshipStorage.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

class AffectsRelationshipInterface :public RuntimeRelationshipEvaluator {
public:
	AffectsRelationshipInterface(ModifyRelationshipStorage* modifiesStorage, UsesRelationshipStorage* usesStorage, NextRelationshipStorage* nextStorage);
	virtual bool getRuntimeRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) = 0;
	virtual std::unordered_set<std::string> getRuntimeRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, std::unordered_set<std::string>& filter) = 0;
	virtual std::unordered_set<std::string> getRuntimeRelationshipBySecond(RelationshipType relType, TokenObject secondArgument, std::unordered_set<std::string>& filter) = 0;
	virtual std::unordered_map<std::string, std::unordered_set<std::string>> getAllRuntimeRelationship(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2) = 0;
	virtual std::unordered_set<std::string> getRuntimeRelationshipWithFirstWildcard(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2) = 0;
	virtual std::unordered_set<std::string> getRuntimeRelationshipWithSecondWildcard(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2) = 0;

protected:
	void DFSAffectsForwardWithSynonym(std::string curr, std::string var, std::unordered_set<std::string>& visited,
		std::unordered_set<std::string>& result, std::unordered_set<std::string>& filter);
	void DFSAffectsBackwardWithSynonym(std::string curr, std::unordered_set<std::string>& usesSet, std::unordered_set<std::string>& visited,
		std::unordered_set<std::string>& result, std::unordered_set<std::string>& filter);

	std::unordered_set<std::string> DFSAffectsWildcardForward(std::unordered_set<std::string>& filter1,
		std::unordered_set<std::string>& filter2, std::unordered_set<std::string>& result);
	std::unordered_set<std::string> DFSAffectsWildcardBackward(std::unordered_set<std::string>& filter1,
		std::unordered_set<std::string>& filter2, std::unordered_set<std::string>& result);
	bool handleConstantWildcard(TokenObject firstArgument);
	bool handleWildcardConstant(TokenObject secondArgument);
	bool handleWildcardWildcard();
	bool DFSAffectsConstantWildcard(std::string curr, std::string var, std::unordered_set<std::string>& visited);
	bool DFSAffectsWildcardConstant(std::string curr, std::unordered_set<std::string>& usesSet, std::unordered_set<std::string>& visited);
	
	NextRelationshipStorage* nextStorage;
	ModifyRelationshipStorage* modifiesStorage;
	UsesRelationshipStorage* usesStorage;
};
