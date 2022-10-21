#include "CallsRelationshipStorage.h"
#include "CallsRelationshipStorageInterface.h"
#include "models/Relationship/CallsRelationship.h"
#include "utils.h"

// Note that every DesignEntity passed in here is assume as Procedure
CallsRelationshipStorageInterface::CallsRelationshipStorageInterface(RelationshipType relationshipType) : RelationshipStorage(), relationshipType(relationshipType) {}

// To answer Calls("proc1", "proc2")
bool CallsRelationshipStorageInterface::getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == relationshipType) {
		if (this->procForwardStorage.find(firstArgument.getValue()) != this->procForwardStorage.end()) {
			std::unordered_set<std::string> set = this->procForwardStorage.find(firstArgument.getValue())->second;
			return set.find(secondArgument.getValue()) != set.end();
		}
	}
	return false;
}

// To answer Calls("proc1", p)
std::unordered_set<std::string> CallsRelationshipStorageInterface::getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType) {
	if (relType == relationshipType) {
		if (this->procForwardStorage.find(firstArgument.getValue()) != this->procForwardStorage.end()) {
			return this->procForwardStorage.find(firstArgument.getValue())->second;
		}
	}
	return std::unordered_set<std::string>();
}

// To answer Calls(p, "proc2")
std::unordered_set<std::string> CallsRelationshipStorageInterface::getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument) {
	if (relType == relationshipType) {
		if (this->procBackwardStorage.find(secondArgument.getValue()) != this->procBackwardStorage.end()) {
			return this->procBackwardStorage.find(secondArgument.getValue())->second;
		}
	}
	return std::unordered_set<std::string>();
}

// To answer Calls(p1, p2)
std::unordered_map<std::string, std::unordered_set<std::string>> CallsRelationshipStorageInterface::getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returnType2) {
	if (relType == relationshipType) {
		return this->procForwardStorage;
	}
	return std::unordered_map<std::string, std::unordered_set<std::string>>();
}
