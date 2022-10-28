#pragma once
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "models/Relationship/Relationship.h"
#include "models/Relationship/RelationshipType.h"
#include "models/Entity/DesignEntity.h"
#include "RuntimeRelationshipEvaluator.h"
#include "components/pkb/storage/RelationshipStorage/NextRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/ModifyRelationshipStorage.h"
#include "components/pkb/storage/RelationshipStorage/UsesRelationshipStorage.h"
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"

class AffectsTRelationshipEvaluator : public RuntimeRelationshipEvaluator {

public:
	AffectsTRelationshipEvaluator(NextRelationshipStorage* nextStorage, ModifyRelationshipStorage* modifiesStorage, UsesRelationshipStorage* usesStorage);
	bool getRuntimeRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument);
	std::unordered_set<std::string> getRuntimeRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, std::unordered_set<std::string>& filter);
	std::unordered_set<std::string> getRuntimeRelationshipBySecond(RelationshipType relType, TokenObject secondArgument, std::unordered_set<std::string>& filter);
	std::unordered_map<std::string, std::unordered_set<std::string>> getAllRuntimeRelationship(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2);
	std::unordered_set<std::string> getRuntimeRelationshipWithFirstWildcard(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2);
	std::unordered_set<std::string> getRuntimeRelationshipWithSecondWildcard(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2);
private:
	bool DFSAffectsTForward(std::string curr, std::string target, std::string var, std::unordered_set<std::string>& visited);
	void DFSAffectsTForwardWithSynonym(std::string curr, std::string var, std::unordered_set<std::string>& visited,
		std::unordered_set<std::string>& result, std::unordered_set<std::string>& filter);
	void DFSAffectsTBackwardWithSynonym(std::string curr, std::unordered_set<std::string>& usesSet, std::unordered_set<std::string>& visited,
		std::unordered_set<std::string>& result, std::unordered_set<std::string>& filter);
	void DFSAffectsTWithTwoSynonyms(std::unordered_set<std::string>& filter1,
		std::unordered_set<std::string>& filter2,
		std::unordered_map<std::string, std::unordered_set<std::string>>& result_map);
	bool isModifiesAssign(std::string target);
	void startNewDFSPath(std::unordered_set<std::string>& visited, std::string neighbour, std::unordered_set<std::string>& result, std::unordered_set<std::string>& filter);
	void removeUsesSet( std::unordered_set<std::string>& usesSet, std::unordered_set<std::string>& intersectionSet);
	void insertUsesSet(std::unordered_set<std::string>& usesSet, std::unordered_set<std::string>& intersectionSet);
	void startNewDFSPathForBackward(std::unordered_set<std::string>& result, std::unordered_set<std::string>& filter, std::string neighbour,
		std::unordered_set<std::string>::const_iterator& exist, std::unordered_set<std::string>& visited);
	std::unordered_set<std::string> DFSAffectsTWildcardForward(std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2,
		std::unordered_set<std::string>& result);
	std::unordered_set<std::string> DFSAffectsTWildcardBackward(std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2,
		std::unordered_set<std::string>& result);

	NextRelationshipStorage* nextStorage;
	ModifyRelationshipStorage* modifiesStorage;
	UsesRelationshipStorage* usesStorage;
};
