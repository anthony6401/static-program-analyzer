#include "NextTRelationshipEvaluator.h"

NextTRelationshipEvaluator::NextTRelationshipEvaluator(NextRelationshipStorage* nextStorage) : nextStorage(nextStorage) {}

// DFS search to answer Next* queries with 2 integer values
bool NextTRelationshipEvaluator::DFSNextTForward(std::string curr, std::string target, std::unordered_set<std::string>& visited) {
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
void NextTRelationshipEvaluator::DFSNextTForwardWithSynonym(std::string curr, std::unordered_set<std::string>& visited,
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

// DFS search to answer Next* queries with synonym
void NextTRelationshipEvaluator::DFSNextTBackwardWithSynonym(std::string curr, std::unordered_set<std::string>& visited,
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

bool NextTRelationshipEvaluator::getRuntimeRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::NEXT_T) {
		std::unordered_set<std::string> visited;
		return DFSNextTForward(firstArgument.getValue(), secondArgument.getValue(), visited);
	}

	return false;
}

std::unordered_set<std::string> NextTRelationshipEvaluator::getRuntimeRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, std::unordered_set<std::string>& filter) {
	if (relType == RelationshipType::NEXT_T) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> result;
		DFSNextTForwardWithSynonym(firstArgument.getValue(), visited, result, filter);
		return result;
	}
	return std::unordered_set<std::string>();
}

std::unordered_set<std::string> NextTRelationshipEvaluator::getRuntimeRelationshipBySecond(RelationshipType relType, TokenObject secondArgument, std::unordered_set<std::string>& filter) {
	if (relType == RelationshipType::NEXT_T) {
		std::unordered_set<std::string> visited;
		std::unordered_set<std::string> result;
		DFSNextTBackwardWithSynonym(secondArgument.getValue(), visited, result, filter);
		return result;
	}
	return std::unordered_set<std::string>();
}

std::unordered_map<std::string, std::unordered_set<std::string>> NextTRelationshipEvaluator::getAllRuntimeRelationship(RelationshipType relType, 
																									std::unordered_set<std::string>& filter1,
																									std::unordered_set<std::string>& filter2) {
	if (relType == RelationshipType::NEXT_T) {
		std::unordered_map<std::string, std::unordered_set<std::string>> result_map;
		for (const auto& ele : filter1) {
			std::unordered_set<std::string> visited;
			std::unordered_set<std::string> result;
			std::string start = ele;
			DFSNextTForwardWithSynonym(start, visited, result, filter);
			if (result.size() != 0) {
				result_map[start] = result;
			}
		}

		return result_map;
	}
	return std::unordered_map<std::string, std::unordered_set<std::string>>();
}
