#include "CallsRelationshipStorage.h"
#include "models/Relationship/CallsRelationship.h"
#include "models/Entity/ProcedureEntity.h"
#include "utils.h"
#include "typeinfo"

// Note that every DesignEntity passed in here is assume as Procedure
CallsRelationshipStorage::CallsRelationshipStorage() : RelationshipStorage(),
														procForwardStorage(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														procBackwardStorage(std::unordered_map<std::string, std::unordered_set<std::string>>()) {}

bool CallsRelationshipStorage::storeRelationship(Relationship* rel) {
	CallsRelationship* callsRelationship = dynamic_cast<CallsRelationship*>(rel);
	if (callsRelationship) {
		Entity* leftEntity = callsRelationship->getLeftEntity();
		Entity* rightEntity = callsRelationship->getRightEntity();
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

// To answer Calls("proc1", "proc2")
bool CallsRelationshipStorage::getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::CALLS) {
		if (this->procForwardStorage.find(firstArgument.getValue()) != this->procForwardStorage.end()) {
			std::unordered_set<std::string> set = this->procForwardStorage.find(firstArgument.getValue())->second;
			return set.find(secondArgument.getValue()) != set.end();
		}
	}
	return false;
}

// To answer Calls("proc1", p)
std::unordered_set<std::string> CallsRelationshipStorage::getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType) {
	if (relType == RelationshipType::CALLS) {
		if (this->procForwardStorage.find(firstArgument.getValue()) != this->procForwardStorage.end()) {
			return this->procForwardStorage.find(firstArgument.getValue())->second;
		}
	}
	return std::unordered_set<std::string>();
}

// To answer Calls(p, "proc2")
std::unordered_set<std::string> CallsRelationshipStorage::getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument) {
	if (relType == RelationshipType::CALLS) {
		if (this->procBackwardStorage.find(secondArgument.getValue()) != this->procBackwardStorage.end()) {
			return this->procBackwardStorage.find(secondArgument.getValue())->second;
		}
	}
	return std::unordered_set<std::string>();
}

// To answer Calls(p1, p2)
std::unordered_map<std::string, std::unordered_set<std::string>> CallsRelationshipStorage::getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returnType2) {
	if (relType == RelationshipType::CALLS) {
		return this->procForwardStorage;
	}
	return std::unordered_map<std::string, std::unordered_set<std::string>>();
}
