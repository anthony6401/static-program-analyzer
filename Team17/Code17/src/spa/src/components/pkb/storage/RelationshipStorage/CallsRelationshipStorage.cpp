#include "CallsRelationshipStorage.h"
#include "CallsRelationshipStorageInterface.h"
#include "models/Relationship/CallsRelationship.h"
#include "models/Relationship/RelationshipType.h"
#include "utils.h"

// Note that every DesignEntity passed in here is assume as Procedure
CallsRelationshipStorage::CallsRelationshipStorage() : CallsRelationshipStorageInterface(RelationshipType::CALLS) {}

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