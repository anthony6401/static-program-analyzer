#include "AffectsRelationshipEvaluator.h"

AffectsRelationshipEvaluator::AffectsRelationshipEvaluator(NextRelationshipStorage* nextStorage, ModifyRelationshipStorage* modifiesStorage, UsesRelationshipStorage* usesStorage) 
														: nextStorage(nextStorage),
														  modifiesStorage(modifiesStorage),
														  usesStorage(usesStorage) {}

// DFS search to answer Next* queries with 2 integer values
bool AffectsRelationshipEvaluator::DFSAffectsForward(std::string curr, std::string target, std::unordered_set<std::string>& visited) {
	visited.insert(curr);

	std::unordered_set<std::string> neighbours = this->nextStorage->getNextForward(curr);

	for (std::string neighbour : neighbours) {
		if (target == neighbour || (visited.find(neighbour) == visited.end() && DFSNextTForward(neighbour, target, visited))) {
			return true;
		}
	}

	return false;
}

// DFS search forward to answer Next* queries with synonym
void AffectsRelationshipEvaluator::DFSAffectsForwardWithSynonym(std::string curr, std::unordered_set<std::string>& visited,
	std::unordered_set<std::string>& result,
	std::unordered_set<std::string>& filter) {
	visited.insert(curr);

	std::unordered_set<std::string> neighbours = this->nextStorage->getNextForward(curr);

	for (std::string neighbour : neighbours) {
		std::unordered_set<std::string>::const_iterator exist = visited.find(neighbour);
		if (filter.find(neighbour) != filter.end()) {
			result.insert(neighbour);
		}
		if (exist == visited.end()) {
			DFSNextTForwardWithSynonym(neighbour, visited, result, filter);
		}
	}
}

// DFS search backward to answer Next* queries with synonym
void AffectsRelationshipEvaluator::DFSAffectsBackwardWithSynonym(std::string curr, std::unordered_set<std::string>& visited,
	std::unordered_set<std::string>& result,
	std::unordered_set<std::string>& filter) {
	visited.insert(curr);

	std::unordered_set<std::string> neighbours = this->nextStorage->getNextBackward(curr);

	for (std::string neighbour : neighbours) {
		std::unordered_set<std::string>::const_iterator exist = visited.find(neighbour);
		if (filter.find(neighbour) != filter.end()) {
			result.insert(neighbour);
		}
		if (exist == visited.end()) {
			DFSNextTBackwardWithSynonym(neighbour, visited, result, filter);
		}
	}
}

// DFS search to answer Next* queries with 2 synonyms
void AffectsRelationshipEvaluator::DFSAffectsWithTwoSynonyms(std::unordered_set<std::string>& filter1,
	std::unordered_set<std::string>& filter2,
	std::unordered_map<std::string, std::unordered_set<std::string>>& result_map) {
	for (const auto& ele : filter1) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> result;
		std::string start = ele;
		DFSNextTForwardWithSynonym(start, visited, result, filter2);
		if (result.size() != 0) {
			result_map[start] = result;
		}
	}
}

bool AffectsRelationshipEvaluator::getRuntimeRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::AFFECTS) {
		std::unordered_set<std::string> visited;
		return DFSAffectsForward(firstArgument.getValue(), secondArgument.getValue(), visited);
	}

	return false;
}

std::unordered_set<std::string> AffectsRelationshipEvaluator::getRuntimeRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, std::unordered_set<std::string>& filter) {
	if (relType == RelationshipType::AFFECTS) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> result;
		DFSAffectsForwardWithSynonym(firstArgument.getValue(), visited, result, filter);
		return result;
	}
	return std::unordered_set<std::string>();
}

std::unordered_set<std::string> AffectsRelationshipEvaluator::getRuntimeRelationshipBySecond(RelationshipType relType, TokenObject secondArgument, std::unordered_set<std::string>& filter) {
	if (relType == RelationshipType::AFFECTS) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> result;
		DFSAffectsBackwardWithSynonym(secondArgument.getValue(), visited, result, filter);
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
