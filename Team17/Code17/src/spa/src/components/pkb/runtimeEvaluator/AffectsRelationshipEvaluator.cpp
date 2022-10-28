#include "AffectsRelationshipEvaluator.h"
#include "AffectsRelationshipInterface.h"
#include "utils.h"

AffectsRelationshipEvaluator::AffectsRelationshipEvaluator(NextRelationshipStorage* nextStorage, ModifyRelationshipStorage* modifiesStorage, UsesRelationshipStorage* usesStorage)
				: AffectsRelationshipInterface(modifiesStorage, usesStorage, nextStorage) {};


// DFS search to answer Next* queries with 2 integer values
bool AffectsRelationshipEvaluator::DFSAffectsForward(std::string curr, std::string target, std::string var, std::unordered_set<std::string>& visited) {
	visited.insert(curr);

	std::unordered_set<std::string> neighbours = this->nextStorage->getNextForward(curr);

	for (std::string neighbour : neighbours) {
		if (target == neighbour || (visited.find(neighbour) == visited.end() && !RuntimeRelationshipUtils::isModifies(modifiesStorage ,neighbour, var) && DFSAffectsForward(neighbour, target, var, visited))) {
			return true;
		}
	}

	return false;
}


// DFS search to answer Next* queries with 2 synonyms
void AffectsRelationshipEvaluator::DFSAffectsWithTwoSynonyms(std::unordered_set<std::string>& filter1,
														std::unordered_set<std::string>& filter2,
														std::unordered_map<std::string, std::unordered_set<std::string>>& result_map) {
	for (const auto& ele : filter1) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> result;
		std::string start = ele;
		std::unordered_set<std::string> modifiesSet = modifiesStorage->getModifiesForAssign(start);

		if (modifiesSet.size() == 0) {
			continue;
		}

		std::string var = *(modifiesSet.begin());
		DFSAffectsForwardWithSynonym(start, var, visited, result, filter2);
		if (result.size() != 0) {
			result_map[start] = result;
		}
	}
}


bool AffectsRelationshipEvaluator::getRuntimeRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::AFFECTS) {

		if (firstArgument.getTokenType() == TokenType::INTEGER && secondArgument.getTokenType() == TokenType::INTEGER) {
			return handleConstantConstant(firstArgument, secondArgument);
		}
		else if (firstArgument.getTokenType() == TokenType::WILDCARD && secondArgument.getTokenType() == TokenType::INTEGER) {
			return handleWildcardConstant(secondArgument);
		}
		else if (firstArgument.getTokenType() == TokenType::CONSTANT && secondArgument.getTokenType() == TokenType::WILDCARD) {
			return handleConstantWildcard(firstArgument);
		}
		else if (firstArgument.getTokenType() == TokenType::WILDCARD && secondArgument.getTokenType() == TokenType::WILDCARD) {
			return handleWildcardWildcard();
		}
	}

	return false;
}

std::unordered_set<std::string> AffectsRelationshipEvaluator::getRuntimeRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, std::unordered_set<std::string>& filter) {
	if (relType == RelationshipType::AFFECTS) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> result;
		std::unordered_set<std::string> modifiesSet = modifiesStorage->getModifiesForAssign(firstArgument.getValue());

		if (modifiesSet.size() != 0) {
			std::string var = *(modifiesSet.begin());
			DFSAffectsForwardWithSynonym(firstArgument.getValue(), var, visited, result, filter);
			return result;
		}
	}
	return std::unordered_set<std::string>();
}

std::unordered_set<std::string> AffectsRelationshipEvaluator::getRuntimeRelationshipBySecond(RelationshipType relType, TokenObject secondArgument, std::unordered_set<std::string>& filter) {
	if (relType == RelationshipType::AFFECTS) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> result;
		std::unordered_set<std::string> usesSet = usesStorage->getUsesForAssign(secondArgument.getValue());
		DFSAffectsBackwardWithSynonym(secondArgument.getValue(), usesSet, visited, result, filter);
		return result;
	}
	return std::unordered_set<std::string>();
}

std::unordered_map<std::string, std::unordered_set<std::string>> AffectsRelationshipEvaluator::getAllRuntimeRelationship(RelationshipType relType,
																												std::unordered_set<std::string>& filter1,
																												std::unordered_set<std::string>& filter2) {
	if (relType == RelationshipType::AFFECTS) {
		std::unordered_map<std::string, std::unordered_set<std::string>> result_map;
		DFSAffectsWithTwoSynonyms(filter1, filter2, result_map);
		return result_map;
	}
	return std::unordered_map<std::string, std::unordered_set<std::string>>();
}

std::unordered_set<std::string> AffectsRelationshipEvaluator::getRuntimeRelationshipWithFirstWildcard(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2) {
	if (relType == RelationshipType::AFFECTS) {
		std::unordered_set<std::string> result;
		return DFSAffectsWildcardBackward(filter1, filter2, result);
	}
	return std::unordered_set<std::string>();
}

std::unordered_set<std::string> AffectsRelationshipEvaluator::getRuntimeRelationshipWithSecondWildcard(RelationshipType relType, std::unordered_set<std::string>& filter1, std::unordered_set<std::string>& filter2) {
	if (relType == RelationshipType::AFFECTS) {
		std::unordered_set<std::string> result;
		return DFSAffectsWildcardForward(filter1, filter2, result);
	}
	return std::unordered_set<std::string>();
}

bool AffectsRelationshipEvaluator::handleConstantConstant(TokenObject firstArgument, TokenObject secondArgument) {
	std::unordered_set<std::string> visited;
	std::unordered_set<std::string> modifiesSet = modifiesStorage->getModifiesForAssign(firstArgument.getValue());
	std::unordered_set<std::string> usesSet = usesStorage->getUsesForAssign(secondArgument.getValue());
	std::unordered_set<std::string> varSet = RuntimeRelationshipUtils::getIntersectionVar(modifiesSet, usesSet);

	if (varSet.size() != 0) {
		std::string var = *varSet.begin();
		return DFSAffectsForward(firstArgument.getValue(), secondArgument.getValue(), var, visited);
	}
	return false;
}
