#include "ParentRelationshipStorage.h"
#include "models/Relationship/ParentRelationship.h"
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
#include "typeinfo"
#include <iostream>


ParentRelationshipStorage::ParentRelationshipStorage() : RelationshipStorage(),
														ifToReadForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														ifToPrintForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														ifToAssignForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														ifToCallForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														ifToWhileForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														ifToIfForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														ifToStmtForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														ifToStmtBackwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														whileToReadForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														whileToPrintForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														whileToAssignForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														whileToCallForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														whileToWhileForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														whileToIfForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														whileToStmtForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														whileToStmtBackwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														stmtToReadForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														stmtToPrintForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														stmtToAssignForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														stmtToCallForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														stmtToWhileForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														stmtToIfForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														stmtToStmtForwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()),
														stmtToStmtBackwardMap(std::unordered_map<std::string, std::unordered_set<std::string>>()) {}



bool ParentRelationshipStorage::storeRelationship(Relationship* rel) {
	ParentRelationship* parentRelationship = dynamic_cast<ParentRelationship*>(rel);

	if (parentRelationship) {
		Entity* leftEntity = parentRelationship->getLeftEntity();
		Entity* rightEntity = parentRelationship->getRightEntity();

		std::string leftValue = leftEntity->getValue();
		std::string rightValue = rightEntity->getValue();

		bool result = false;

		result = result || Utils::insertEntity(this->stmtToStmtForwardMap, leftValue, rightValue);
		//std::cout << "Stmt -> Stmt f " << result << std::endl;
		result = result || Utils::insertEntity(this->stmtToStmtBackwardMap, rightValue, leftValue);
		//std::cout << "Stmt -> Stmt b " << result << std::endl;

		if (typeid(*leftEntity) == typeid(WhileEntity)) {
			//Store Stmt -> stmt forward and backward
			
			if (typeid(*rightEntity) == typeid(ReadEntity)) {
				result = result || Utils::insertEntity(this->stmtToReadForwardMap, leftValue, rightValue);
				//std::cout << "Stmt -> read " << result << std::endl;
				result = result || Utils::insertEntity(this->whileToReadForwardMap, leftValue, rightValue);
				//std::cout << "while -> read " << result << std::endl;
			
			} 
			else if (typeid(*rightEntity) == typeid(PrintEntity)) {
				result = result || Utils::insertEntity(this->stmtToPrintForwardMap, leftValue, rightValue);
				result = result || Utils::insertEntity(this->whileToPrintForwardMap, leftValue, rightValue);
			}
			else if (typeid(*rightEntity) == typeid(AssignEntity)) {
				result = result || Utils::insertEntity(this->stmtToAssignForwardMap, leftValue, rightValue);
				result = result || Utils::insertEntity(this->whileToAssignForwardMap, leftValue, rightValue);
			}
			else if (typeid(*rightEntity) == typeid(CallEntity)) {
				result = result || Utils::insertEntity(this->stmtToCallForwardMap, leftValue, rightValue);
				result = result || Utils::insertEntity(this->whileToCallForwardMap, leftValue, rightValue);
			}
			else if (typeid(*rightEntity) == typeid(WhileEntity)) {
				result = result || Utils::insertEntity(this->stmtToWhileForwardMap, leftValue, rightValue);
				result = result || Utils::insertEntity(this->whileToWhileForwardMap, leftValue, rightValue);
			}
			else if (typeid(*rightEntity) == typeid(IfEntity)) {
				result = result || Utils::insertEntity(this->stmtToIfForwardMap, leftValue, rightValue);
				result = result || Utils::insertEntity(this->whileToIfForwardMap, leftValue, rightValue);
			}

			result = result || Utils::insertEntity(this->whileToStmtForwardMap, leftValue, rightValue);
			//std::cout << "while -> stmt f " << result << std::endl;
			result = result || Utils::insertEntity(this->whileToStmtBackwardMap, rightValue, leftValue);
			//std::cout << "while -> stmt b " << result << std::endl;

		} else if (typeid(*leftEntity) == typeid(IfEntity)) {
			if (typeid(*rightEntity) == typeid(ReadEntity)) {
				result = result || Utils::insertEntity(this->stmtToReadForwardMap, leftValue, rightValue);
				result = result || Utils::insertEntity(this->ifToReadForwardMap, leftValue, rightValue);

			}
			else if (typeid(*rightEntity) == typeid(PrintEntity)) {
				result = result || Utils::insertEntity(this->stmtToPrintForwardMap, leftValue, rightValue);
				//std::cout << "stmt -> print " << result << std::endl;
				result = result || Utils::insertEntity(this->ifToPrintForwardMap, leftValue, rightValue);
				//std::cout << "if -> print " << result << std::endl;
			}
			else if (typeid(*rightEntity) == typeid(AssignEntity)) {
				result = result || Utils::insertEntity(this->stmtToAssignForwardMap, leftValue, rightValue);
				result = result || Utils::insertEntity(this->ifToAssignForwardMap, leftValue, rightValue);
			}
			else if (typeid(*rightEntity) == typeid(CallEntity)) {
				result = result || Utils::insertEntity(this->stmtToCallForwardMap, leftValue, rightValue);
				result = result || Utils::insertEntity(this->ifToCallForwardMap, leftValue, rightValue);
			}
			else if (typeid(*rightEntity) == typeid(WhileEntity)) {
				result = result || Utils::insertEntity(this->stmtToWhileForwardMap, leftValue, rightValue);
				result = result || Utils::insertEntity(this->ifToWhileForwardMap, leftValue, rightValue);
			}
			else if (typeid(*rightEntity) == typeid(IfEntity)) {
				result = result || Utils::insertEntity(this->stmtToIfForwardMap, leftValue, rightValue);
				result = result || Utils::insertEntity(this->ifToIfForwardMap, leftValue, rightValue);
			}

			result = result || Utils::insertEntity(this->ifToStmtForwardMap, leftValue, rightValue);
			result = result || Utils::insertEntity(this->ifToStmtBackwardMap, rightValue, leftValue);
		}
		//std::cout << "----------------------------------------------"  << std::endl;
		return result;
	}
	return false;
}

// Answer Parent(1,2)
bool ParentRelationshipStorage::getRelationship(RelationshipType relType,TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == RelationshipType::PARENT) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};

		storage = &this->stmtToStmtForwardMap;

		if (storage->find(firstArgument.getValue())== storage->end()) {
			return false;
		}

		std::unordered_set<std::string>* set = &storage->find(firstArgument.getValue())->second;

		return set->find(secondArgument.getValue()) != set->end();
	}
	return false;
}

// Answer Parent(1,a)
std::unordered_set<std::string> ParentRelationshipStorage::getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType) {
	if (relType == RelationshipType::PARENT) {
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
		else if(returnType == DesignEntity::CALL) {
			storage = &this->stmtToCallForwardMap;
		}
		else if (returnType == DesignEntity::WHILE) {
			storage = &this->stmtToWhileForwardMap;
		}
		else if (returnType == DesignEntity::IF) {
			storage = &this->stmtToIfForwardMap;
		}

		std::string findValue = firstArgument.getValue();

		if (storage->find(findValue) == storage->end()) {
			return std::unordered_set<std::string>();
		}

		return storage->find(findValue)->second;

	}
	return std::unordered_set<std::string>();
}

// Answer Parent(s,2), Parent(w,2), or Parent(if, 2)
std::unordered_set<std::string> ParentRelationshipStorage::getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument) {
	if (relType == RelationshipType::PARENT) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};

		if (returnType == DesignEntity::STMT) {
			storage = &this->stmtToStmtBackwardMap;
		}
		else if (returnType == DesignEntity::WHILE) {
			storage = &this->whileToStmtBackwardMap;
		}
		else if (returnType == DesignEntity::IF) {
			storage = &this->ifToStmtBackwardMap;
		}

		std::string findValue = secondArgument.getValue();

		if (storage->find(findValue) == storage->end()) {
			return std::unordered_set<std::string>();
		}

		return storage->find(findValue)->second;

	}

	return std::unordered_set<std::string>();
}

//Answer Parent(s,w),...., Parent(w,a),..., Parent(if, a)
std::unordered_map<std::string, std::unordered_set<std::string>> ParentRelationshipStorage::getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returnType2) {
	if (relType == RelationshipType::PARENT) {
		if (returnType1 == DesignEntity::STMT) {
			
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

		return std::unordered_map<std::string, std::unordered_set<std::string>>();
	}
	return std::unordered_map<std::string, std::unordered_set<std::string>>();
}





