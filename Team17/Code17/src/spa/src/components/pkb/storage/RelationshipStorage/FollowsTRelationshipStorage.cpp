#include "FollowsTRelationshipStorage.h"
#include "models/Relationship/FollowsTRelationship.h"
#include "models/Relationship/RelationshipType.h"
#include "models/Entity/ProcedureEntity.h"
#include "models/Entity/AssignEntity.h"
#include "models/Entity/ReadEntity.h"
#include "models/Entity/CallEntity.h"
#include "models/Entity/IfEntity.h"
#include "models/Entity/WhileEntity.h"
#include "models/Entity/PrintEntity.h"
#include "models/Entity/Entity.h"
#include "models/Entity/DesignEntity.h"

#include "utils.h"

#include "utils.h"
#include "typeinfo"
#include <iostream>

FollowsTRelationshipStorage::FollowsTRelationshipStorage() : RelationshipStorage(),
readToReadForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
readToPrintForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
readToAssignForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
readToCallForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
readToWhileForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
readToIfForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
readToStmtForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
readToStmtBackwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),

printToReadForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
printToPrintForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
printToAssignForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
printToCallForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
printToWhileForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
printToIfForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
printToStmtForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
printToStmtBackwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),

assignToReadForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
assignToPrintForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
assignToAssignForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
assignToCallForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
assignToWhileForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
assignToIfForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
assignToStmtForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
assignToStmtBackwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),

callToReadForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
callToPrintForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
callToAssignForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
callToCallForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
callToWhileForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
callToIfForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
callToStmtForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
callToStmtBackwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),

whileToReadForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
whileToPrintForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
whileToAssignForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
whileToCallForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
whileToWhileForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
whileToIfForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
whileToStmtForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
whileToStmtBackwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),

ifToReadForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
ifToPrintForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
ifToAssignForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
ifToCallForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
ifToWhileForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
ifToIfForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
ifToStmtForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
ifToStmtBackwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),

stmtToReadForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
stmtToPrintForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
stmtToAssignForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
stmtToCallForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
stmtToWhileForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
stmtToIfForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
stmtToStmtForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
stmtToStmtBackwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()) {}


bool FollowsTRelationshipStorage::storeRelationship(Relationship* rel) {
	FollowsTRelationship* followsTRelationship = dynamic_cast<FollowsTRelationship*>(rel);

	if (followsTRelationship) {
		Entity* leftEntity = followsTRelationship->getLeftEntity();
		Entity* rightEntity = followsTRelationship->getRightEntity();

		std::string leftValue = leftEntity->getValue();
		std::string rightValue = rightEntity->getValue();

		bool result = false;
		bool resultOne = RelationshipUtils::insertEntity(this->stmtToStmtForwardMap, leftValue, rightValue);
		bool resultTwo = RelationshipUtils::insertEntity(this->stmtToStmtBackwardMap, rightValue, leftValue);

		result = result || resultOne || resultTwo;

		if (typeid(*leftEntity) == typeid(ReadEntity)) {
			if (typeid(*rightEntity) == typeid(ReadEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToReadForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->readToReadForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;

			}
			else if (typeid(*rightEntity) == typeid(PrintEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToPrintForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->readToPrintForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(AssignEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToAssignForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->readToAssignForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(CallEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToCallForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->readToCallForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(WhileEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToWhileForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->readToWhileForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(IfEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToIfForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->readToIfForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}

			bool resultOne = RelationshipUtils::insertEntity(this->readToStmtForwardMap, leftValue, rightValue);
			bool resultTwo = RelationshipUtils::insertEntity(this->readToStmtBackwardMap, rightValue, leftValue);
			result = result || resultOne || resultTwo;

		}
		else if (typeid(*leftEntity) == typeid(PrintEntity)) {
			if (typeid(*rightEntity) == typeid(ReadEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToReadForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->printToReadForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(PrintEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToPrintForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->printToPrintForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(AssignEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToAssignForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->printToAssignForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(CallEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToCallForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->printToCallForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(WhileEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToWhileForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->printToWhileForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(IfEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToIfForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->printToIfForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			bool resultOne = RelationshipUtils::insertEntity(this->printToStmtForwardMap, leftValue, rightValue);
			bool resultTwo = RelationshipUtils::insertEntity(this->printToStmtBackwardMap, rightValue, leftValue);
			result = result || resultOne || resultTwo;
		}
		else if (typeid(*leftEntity) == typeid(AssignEntity)) {
			if (typeid(*rightEntity) == typeid(ReadEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToReadForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->assignToReadForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(PrintEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToPrintForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->assignToPrintForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(AssignEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToAssignForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->assignToAssignForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(CallEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToCallForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->assignToCallForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(WhileEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToWhileForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->assignToWhileForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(IfEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToIfForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->assignToIfForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			bool resultOne = RelationshipUtils::insertEntity(this->assignToStmtForwardMap, leftValue, rightValue);
			bool resultTwo = RelationshipUtils::insertEntity(this->assignToStmtBackwardMap, rightValue, leftValue);
			result = result || resultOne || resultTwo;
		}
		else if (typeid(*leftEntity) == typeid(CallEntity)) {
			if (typeid(*rightEntity) == typeid(ReadEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToReadForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->callToReadForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(PrintEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToPrintForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->callToPrintForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(AssignEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToAssignForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->callToAssignForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(CallEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToCallForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->callToCallForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(WhileEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToWhileForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->callToWhileForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(IfEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToIfForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->callToIfForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			bool resultOne = RelationshipUtils::insertEntity(this->callToStmtForwardMap, leftValue, rightValue);
			bool resultTwo = RelationshipUtils::insertEntity(this->callToStmtBackwardMap, rightValue, leftValue);
			result = result || resultOne || resultTwo;
		}
		else if (typeid(*leftEntity) == typeid(WhileEntity)) {
			if (typeid(*rightEntity) == typeid(ReadEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToReadForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->whileToReadForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(PrintEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToPrintForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->whileToPrintForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(AssignEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToAssignForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->whileToAssignForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(CallEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToCallForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->whileToCallForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(WhileEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToWhileForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->whileToWhileForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(IfEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToIfForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->whileToIfForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			bool resultOne = RelationshipUtils::insertEntity(this->whileToStmtForwardMap, leftValue, rightValue);
			bool resultTwo = RelationshipUtils::insertEntity(this->whileToStmtBackwardMap, rightValue, leftValue);
			result = result || resultOne || resultTwo;
		}
		else if (typeid(*leftEntity) == typeid(IfEntity)) {
			if (typeid(*rightEntity) == typeid(ReadEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToReadForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->ifToReadForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(PrintEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToPrintForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->ifToPrintForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(AssignEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToAssignForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->ifToAssignForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(CallEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToCallForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->ifToCallForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(WhileEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToWhileForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->ifToWhileForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			else if (typeid(*rightEntity) == typeid(IfEntity)) {
				bool resultOne = RelationshipUtils::insertEntity(this->stmtToIfForwardMap, leftValue, rightValue);
				bool resultTwo = RelationshipUtils::insertEntity(this->ifToIfForwardMap, leftValue, rightValue);

				result = result || resultOne || resultTwo;
			}
			bool resultOne = RelationshipUtils::insertEntity(this->ifToStmtForwardMap, leftValue, rightValue);
			bool resultTwo = RelationshipUtils::insertEntity(this->ifToStmtBackwardMap, rightValue, leftValue);
			result = result || resultOne || resultTwo;
		}
		return result;
	}
	return false;
}

bool FollowsTRelationshipStorage::getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::FOLLOWS_T) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};

		storage = &this->stmtToStmtForwardMap;

		if (storage->find(firstArgument.getValue()) == storage->end()) {
			return false;
		}

		std::unordered_set<std::string>* set = &storage->find(firstArgument.getValue())->second;

		return set->find(secondArgument.getValue()) != set->end();
	}
	return false;
}

// Answer Follows(1,a)
std::unordered_set<std::string> FollowsTRelationshipStorage::getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType) {
	if (relType == RelationshipType::FOLLOWS_T) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};

		if (returnType == DesignEntity::READ) {
			storage = &this->stmtToReadForwardMap;
		}
		else if (returnType == DesignEntity::PRINT) {
			storage = &this->stmtToPrintForwardMap;
		}
		else if (returnType == DesignEntity::ASSIGN) {
			storage = &this->stmtToAssignForwardMap;
		}
		else if (returnType == DesignEntity::CALL) {
			storage = &this->stmtToCallForwardMap;
		}
		else if (returnType == DesignEntity::WHILE) {
			storage = &this->stmtToWhileForwardMap;
		}
		else if (returnType == DesignEntity::IF) {
			storage = &this->stmtToIfForwardMap;
		}
		else if (returnType == DesignEntity::STMT) {
			storage = &this->stmtToStmtForwardMap;
		}

		std::string findValue = firstArgument.getValue();

		if (storage->find(findValue) == storage->end()) {
			return std::unordered_set<std::string>();
		}

		return storage->find(findValue)->second;
	}
	return std::unordered_set<std::string>();
}

// Answer Follows(s,2), Follows(w,2), or Follows(if, 2)
std::unordered_set<std::string> FollowsTRelationshipStorage::getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument) {
	if (relType == RelationshipType::FOLLOWS_T) {
		std::unordered_map<std::string, std::unordered_set<std::string>> storage{};

		if (returnType == DesignEntity::READ) {
			storage = this->readToStmtBackwardMap;
		}
		else if (returnType == DesignEntity::PRINT) {
			storage = this->printToStmtBackwardMap;
		}
		else if (returnType == DesignEntity::ASSIGN) {
			storage = this->assignToStmtBackwardMap;
		}
		else if (returnType == DesignEntity::CALL) {
			storage = this->callToStmtBackwardMap;
		}
		else if (returnType == DesignEntity::WHILE) {
			storage = this->whileToStmtBackwardMap;
		}
		else if (returnType == DesignEntity::IF) {
			storage = this->ifToStmtBackwardMap;
		}
		else if (returnType == DesignEntity::STMT) {
			storage = this->stmtToStmtBackwardMap;
		}

		std::string findValue = secondArgument.getValue();

		if (storage.find(findValue) == storage.end()) {
			return std::unordered_set<std::string>();
		}

		return storage.find(findValue)->second;
	}
	return std::unordered_set<std::string>();
}

std::unordered_map<std::string, std::unordered_set<std::string>> FollowsTRelationshipStorage::getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returnType2) {
	if (relType == RelationshipType::FOLLOWS_T) {
		if (returnType1 == DesignEntity::READ) {
			if (returnType2 == DesignEntity::READ) {
				return this->readToReadForwardMap;
			}
			else if (returnType2 == DesignEntity::PRINT) {
				return this->readToPrintForwardMap;
			}
			else if (returnType2 == DesignEntity::ASSIGN) {
				return this->readToAssignForwardMap;
			}
			else if (returnType2 == DesignEntity::CALL) {
				return this->readToCallForwardMap;
			}
			else if (returnType2 == DesignEntity::WHILE) {
				return this->readToWhileForwardMap;
			}
			else if (returnType2 == DesignEntity::IF) {
				return this->readToIfForwardMap;
			}
			else if (returnType2 == DesignEntity::STMT) {
				return this->readToStmtForwardMap;
			}
		}
		else if (returnType1 == DesignEntity::PRINT) {
			if (returnType2 == DesignEntity::READ) {
				return this->printToReadForwardMap;
			}
			else if (returnType2 == DesignEntity::PRINT) {
				return this->printToPrintForwardMap;
			}
			else if (returnType2 == DesignEntity::ASSIGN) {
				return this->printToAssignForwardMap;
			}
			else if (returnType2 == DesignEntity::CALL) {
				return this->printToCallForwardMap;
			}
			else if (returnType2 == DesignEntity::WHILE) {
				return this->printToWhileForwardMap;
			}
			else if (returnType2 == DesignEntity::IF) {
				return this->printToIfForwardMap;
			}
			else if (returnType2 == DesignEntity::STMT) {
				return this->printToStmtForwardMap;
			}
		}
		else if (returnType1 == DesignEntity::ASSIGN) {
			if (returnType2 == DesignEntity::READ) {
				return this->assignToReadForwardMap;
			}
			else if (returnType2 == DesignEntity::PRINT) {
				return this->assignToPrintForwardMap;
			}
			else if (returnType2 == DesignEntity::ASSIGN) {
				return this->assignToAssignForwardMap;
			}
			else if (returnType2 == DesignEntity::CALL) {
				return this->assignToCallForwardMap;
			}
			else if (returnType2 == DesignEntity::WHILE) {
				return this->assignToWhileForwardMap;
			}
			else if (returnType2 == DesignEntity::IF) {
				return this->assignToIfForwardMap;
			}
			else if (returnType2 == DesignEntity::STMT) {
				return this->assignToStmtForwardMap;
			}
		}
		else if (returnType1 == DesignEntity::CALL) {
			if (returnType2 == DesignEntity::READ) {
				return this->callToReadForwardMap;
			}
			else if (returnType2 == DesignEntity::PRINT) {
				return this->callToPrintForwardMap;
			}
			else if (returnType2 == DesignEntity::ASSIGN) {
				return this->callToAssignForwardMap;
			}
			else if (returnType2 == DesignEntity::CALL) {
				return this->callToCallForwardMap;
			}
			else if (returnType2 == DesignEntity::WHILE) {
				return this->callToWhileForwardMap;
			}
			else if (returnType2 == DesignEntity::IF) {
				return this->callToIfForwardMap;
			}
			else if (returnType2 == DesignEntity::STMT) {
				return this->callToStmtForwardMap;
			}
		}
		else if (returnType1 == DesignEntity::WHILE) {
			if (returnType2 == DesignEntity::READ) {
				return this->whileToReadForwardMap;
			}
			else if (returnType2 == DesignEntity::PRINT) {
				return this->whileToPrintForwardMap;
			}
			else if (returnType2 == DesignEntity::ASSIGN) {
				return this->whileToAssignForwardMap;
			}
			else if (returnType2 == DesignEntity::CALL) {
				return this->whileToCallForwardMap;
			}
			else if (returnType2 == DesignEntity::WHILE) {
				return this->whileToWhileForwardMap;
			}
			else if (returnType2 == DesignEntity::IF) {
				return this->whileToIfForwardMap;
			}
			else if (returnType2 == DesignEntity::STMT) {
				return this->whileToStmtForwardMap;
			}
		}
		else if (returnType1 == DesignEntity::IF) {
			if (returnType2 == DesignEntity::READ) {
				return this->ifToReadForwardMap;
			}
			else if (returnType2 == DesignEntity::PRINT) {
				return this->ifToPrintForwardMap;
			}
			else if (returnType2 == DesignEntity::ASSIGN) {
				return this->ifToAssignForwardMap;
			}
			else if (returnType2 == DesignEntity::CALL) {
				return this->ifToCallForwardMap;
			}
			else if (returnType2 == DesignEntity::WHILE) {
				return this->ifToWhileForwardMap;
			}
			else if (returnType2 == DesignEntity::IF) {
				return this->ifToIfForwardMap;
			}
			else if (returnType2 == DesignEntity::STMT) {
				return this->ifToStmtForwardMap;
			}
		}
		else if (returnType1 == DesignEntity::STMT) {
			if (returnType2 == DesignEntity::READ) {
				return this->stmtToReadForwardMap;
			}
			else if (returnType2 == DesignEntity::PRINT) {
				return this->stmtToPrintForwardMap;
			}
			else if (returnType2 == DesignEntity::ASSIGN) {
				return this->stmtToAssignForwardMap;
			}
			else if (returnType2 == DesignEntity::CALL) {
				return this->stmtToCallForwardMap;
			}
			else if (returnType2 == DesignEntity::WHILE) {
				return this->stmtToWhileForwardMap;
			}
			else if (returnType2 == DesignEntity::IF) {
				return this->stmtToIfForwardMap;
			}
			else if (returnType2 == DesignEntity::STMT) {
				return this->stmtToStmtForwardMap;
			}
		}
		return std::unordered_map<std::string, std::unordered_set<std::string>>();

	}
	return std::unordered_map<std::string, std::unordered_set<std::string>>();
}