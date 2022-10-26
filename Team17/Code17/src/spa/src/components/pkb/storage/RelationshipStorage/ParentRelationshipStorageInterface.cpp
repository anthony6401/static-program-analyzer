#include "ParentRelationshipStorageInterface.h"
#include "models/Relationship/ParentRelationship.h"
#include "models/Relationship/ParentTRelationship.h"
#include "utils.h"

ParentRelationshipStorageInterface::ParentRelationshipStorageInterface(RelationshipType relationshipType) : RelationshipStorageFirstWildcard(), relationshipType(relationshipType) {}

std::unordered_map<std::string, std::unordered_set<std::string>>* ParentRelationshipStorageInterface::getWhileToSpecificStorage(DesignEntity right) {
	if (right == DesignEntity::READ) {
		return &(this->whileToReadForwardMap);
	}
	if (right == DesignEntity::PRINT) {
		return &(this->whileToPrintForwardMap);
	}
	if (right == DesignEntity::ASSIGN) {
		return &(this->whileToAssignForwardMap);
	}
	if (right == DesignEntity::CALL) {
		return &(this->whileToCallForwardMap);
	}
	if (right == DesignEntity::WHILE) {
		return &(this->whileToWhileForwardMap);
	}
	if (right == DesignEntity::IF) {
		return &(this->whileToIfForwardMap);
	}
	if (right == DesignEntity::STMT) {
		return &(this->whileToStmtForwardMap);
	}
	return nullptr;
}

std::unordered_map<std::string, std::unordered_set<std::string>>* ParentRelationshipStorageInterface::getIfToSpecificStorage(DesignEntity right) {
	if (right == DesignEntity::READ) {
		return &(this->ifToReadForwardMap);
	}

	else if (right == DesignEntity::PRINT) {
		return &(this->ifToPrintForwardMap);
	}
	else if (right == DesignEntity::ASSIGN) {
		return &(this->ifToAssignForwardMap);
	}
	else if (right == DesignEntity::CALL) {
		return &(this->ifToCallForwardMap);
	}
	else if (right == DesignEntity::WHILE) {
		return &(this->ifToWhileForwardMap);
	}
	else if (right == DesignEntity::IF) {
		return &(this->ifToIfForwardMap);
	}
	else if (right == DesignEntity::STMT) {
		return &(this->ifToStmtForwardMap);
	}
	return nullptr;
}

std::unordered_map<std::string, std::unordered_set<std::string>>* ParentRelationshipStorageInterface::getStmtToSpecificStorage(DesignEntity right) {
	if (right == DesignEntity::READ) {
		return &(this->stmtToReadForwardMap);
	}

	else if (right == DesignEntity::PRINT) {
		return &(this->stmtToPrintForwardMap);
	}
	else if (right == DesignEntity::ASSIGN) {
		return &(this->stmtToAssignForwardMap);
	}
	else if (right == DesignEntity::CALL) {
		return &(this->stmtToCallForwardMap);
	}
	else if (right == DesignEntity::WHILE) {
		return &(this->stmtToWhileForwardMap);
	}
	else if (right == DesignEntity::IF) {
		return &(this->stmtToIfForwardMap);
	}
	else if (right == DesignEntity::STMT) {
		return &(this->stmtToStmtForwardMap);
	}
	return nullptr;
}

std::unordered_map<std::string, std::unordered_set<std::string>>* ParentRelationshipStorageInterface::getStorageForward(DesignEntity left, DesignEntity right) {
	if (left == DesignEntity::WHILE) {
		//Store Stmt -> stmt forward and backward
		return getWhileToSpecificStorage(right);

	}
	else if (left == DesignEntity::IF) {
		return getIfToSpecificStorage(right);
	}
	else if (left == DesignEntity::STMT) {
		return getStmtToSpecificStorage(right);
	}
	return nullptr;
}

std::unordered_map<std::string, std::unordered_set<std::string>>* ParentRelationshipStorageInterface::getStorageBackward(DesignEntity left) {
	if (left == DesignEntity::WHILE) {
		//Store Stmt -> stmt forward and backward
		return &(this->whileToStmtBackwardMap);

	}
	else if (left == DesignEntity::IF) {
		return &(this->ifToStmtBackwardMap);
	}
	else if (left == DesignEntity::STMT) {
		return &(this->stmtToStmtBackwardMap);
	}
	return nullptr;
}

bool ParentRelationshipStorageInterface::handleConstantConstant(TokenObject firstArgument, TokenObject secondArgument) {
	std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};
	storage = getStorageForward(DesignEntity::STMT, DesignEntity::STMT);
	if (storage->find(firstArgument.getValue()) != storage->end()) {
		std::unordered_set<std::string>* set = &storage->find(firstArgument.getValue())->second;
		return set->find(secondArgument.getValue()) != set->end();
	}

	return false;
}

bool ParentRelationshipStorageInterface::handleConstantWildcard(TokenObject firstArgument) {
	std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};
	storage = getStorageForward(DesignEntity::STMT, DesignEntity::STMT);
	return storage->find(firstArgument.getValue()) != storage->end();
}

bool ParentRelationshipStorageInterface::handleWildcardConstant(TokenObject secondArgument) {
	std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};
	storage = getStorageBackward(DesignEntity::STMT);
	return storage->find(secondArgument.getValue()) != storage->end();
}

bool ParentRelationshipStorageInterface::handleWilcardWildcard() {
	std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};
	storage = getStorageForward(DesignEntity::STMT, DesignEntity::STMT);
	return storage->size() != 0;
}

// Answer Parent(1,2)
bool ParentRelationshipStorageInterface::getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType ==relationshipType) {
		if (firstArgument.getTokenType() == TokenType::INTEGER && secondArgument.getTokenType() == TokenType::INTEGER) {
			return handleConstantConstant(firstArgument, secondArgument);
		}
		else if (firstArgument.getTokenType() == TokenType::WILDCARD && secondArgument.getTokenType() == TokenType::INTEGER) {
			return handleWildcardConstant(secondArgument);
		}
		else if (firstArgument.getTokenType() == TokenType::INTEGER && secondArgument.getTokenType() == TokenType::WILDCARD) {
			return handleConstantWildcard(firstArgument);
		}
		else if (firstArgument.getTokenType() == TokenType::WILDCARD && secondArgument.getTokenType() == TokenType::WILDCARD) {
			return handleWilcardWildcard();
		}
	}
	return false;
}

// Answer Parent(1,a)
std::unordered_set<std::string> ParentRelationshipStorageInterface::getRelationshipByFirst(RelationshipType relType, TokenObject firstArgument, DesignEntity returnType) {
	if (relType == relationshipType) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};

		storage = getStorageForward(DesignEntity::STMT, returnType);

		if (storage == nullptr) {
			return std::unordered_set<std::string>();
		}

		std::string findValue = firstArgument.getValue();

		if (storage->find(findValue) == storage->end()) {
			return std::unordered_set<std::string>();
		}

		return storage->find(findValue)->second;
	}
	return std::unordered_set<std::string>();
}

std::unordered_set<std::string> ParentRelationshipStorageInterface::getRelationshipWithFirstWildcard(RelationshipType relType, DesignEntity returnType) {
	if (relType == relationshipType) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};

		storage = getStorageForward(DesignEntity::STMT, returnType);

		if (storage == nullptr) {
			return std::unordered_set<std::string>();
		}

		std::unordered_set<std::string> result;

		for (auto const& pair : *storage) {
			result.insert(pair.second.begin(), pair.second.end());
		}

		return result;

	}
	return std::unordered_set<std::string>();
}

std::unordered_set<std::string> ParentRelationshipStorageInterface::getRelationshipWithSecondWildcard(RelationshipType relType, DesignEntity returnType) {
	if (relType == relationshipType) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};

		storage = getStorageForward(returnType, DesignEntity::STMT);

		if (storage == nullptr) {
			return std::unordered_set<std::string>();
		}

		std::unordered_set<std::string> result;

		for (auto const& pair : *storage) {
			result.insert(pair.first);
		}

		return result;

	}
	return std::unordered_set<std::string>();
}

// Answer Parent(s,2), Parent(w,2), or Parent(if, 2)
std::unordered_set<std::string> ParentRelationshipStorageInterface::getRelationshipBySecond(RelationshipType relType, DesignEntity returnType, TokenObject secondArgument) {
	if (relType ==relationshipType) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};

		storage = getStorageBackward(returnType);

		if (storage == nullptr) {
			return std::unordered_set<std::string>();
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
std::unordered_map<std::string, std::unordered_set<std::string>> ParentRelationshipStorageInterface::getAllRelationship(RelationshipType relType, DesignEntity returnType1, DesignEntity returnType2) {
	if (relType == relationshipType) {
		std::unordered_map<std::string, std::unordered_set<std::string>>* storage{};

		storage = getStorageForward(returnType1, returnType2);

		if (storage == nullptr) {
			return std::unordered_map<std::string, std::unordered_set<std::string>>();
		}

		return *storage;

	}
	return std::unordered_map<std::string, std::unordered_set<std::string>>();
}
