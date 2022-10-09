#include "CallsTRelationshipStorage.h"
#include "models/Relationship/CallsTRelationship.h"
#include "models/Entity/ProcedureEntity.h"
#include "utils.h"
#include "typeinfo"

// Note that every DesignEntity passed in here is assume as Procedure
CallsTRelationshipStorage::CallsTRelationshipStorage() : RelationshipStorage() {}

bool CallsTRelationshipStorage::storeRelationship(Relationship* rel) {
	CallsTRelationship* callsTRelationship = dynamic_cast<CallsTRelationship*>(rel);
	if (callsTRelationship) {
		Entity* leftEntity = callsTRelationship->getLeftEntity();
		Entity* rightEntity = callsTRelationship->getRightEntity();
		std::string leftValue = leftEntity->getValue();
		std::string rightValue = rightEntity->getValue();

		bool result = false;

		bool resultOne = RelationshipUtils::insertEntity(&this->procForwardStorage, leftValue, rightValue);
		bool resultTwo = RelationshipUtils::insertEntity(&this->procBackwardStorage, rightValue, leftValue);

		result = result || resultOne || resultTwo;

		return result;
	}

	return false;
}

// To answer Calls*("proc1", "proc2")
bool CallsTRelationshipStorage::getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::CALLS_T) {
		if (this->procForwardStorage.find(firstArgument.getValue()) != this->procForwardStorage.end()) {
			std::unordered_set<std::string> set = this->procForwardStorage.find(firstArgument.getValue())->second;
			return set.find(secondArgument.getValue()) != set.end();
		}
	}
	return false;
}

// To answer Calls*("proc1", p)
std::unordered_set<std::string> CallsTRelationshipStorage::getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType) {
	if (relType == RelationshipType::CALLS_T) {
		if (this->procForwardStorage.find(firstArgument.getValue()) != this->procForwardStorage.end()) {
			return this->procForwardStorage.find(firstArgument.getValue())->second;
		}
	}
	return std::unordered_set<std::string>();
}

// To answer Calls*(p, "proc2")
std::unordered_set<std::string> CallsTRelationshipStorage::getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument) {
	if (relType == RelationshipType::CALLS_T) {
		if (this->procBackwardStorage.find(secondArgument.getValue()) != this->procBackwardStorage.end()) {
			return this->procBackwardStorage.find(secondArgument.getValue())->second;
		}
	}
	return std::unordered_set<std::string>();
}

// To answer Calls*(p1, p2)
std::unordered_map<std::string, std::unordered_set<std::string>> CallsTRelationshipStorage::getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returnType2) {
	if (relType == RelationshipType::CALLS_T) {
		return this->procForwardStorage;
	}
	return std::unordered_map<std::string, std::unordered_set<std::string>>();
}
