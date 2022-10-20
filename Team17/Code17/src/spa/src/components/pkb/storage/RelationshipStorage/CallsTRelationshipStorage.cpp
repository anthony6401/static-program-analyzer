#include "CallsTRelationshipStorage.h"
#include "CallsRelationshipStorageInterface.h"
#include "models/Relationship/CallsTRelationship.h"
#include "models/Relationship/RelationshipType.h"
#include "utils.h"

// Note that every DesignEntity passed in here is assume as Procedure
CallsTRelationshipStorage::CallsTRelationshipStorage() : CallsRelationshipStorageInterface(RelationshipType::CALLS_T) {}

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
