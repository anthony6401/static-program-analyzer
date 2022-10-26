#include "CallsRelationshipStorage.h"
#include "CallsRelationshipStorageInterface.h"
#include "models/Relationship/CallsRelationship.h"
#include "utils.h"

// Note that every DesignEntity passed in here is assume as Procedure
CallsRelationshipStorageInterface::CallsRelationshipStorageInterface(RelationshipType relationshipType) : RelationshipStorageFirstWildcard(), relationshipType(relationshipType) {}

// To answer Calls("proc1", "proc2"), Calls("proc1", _), Calls(_, "proc1"), Calls(_, _)
bool CallsRelationshipStorageInterface::getRelationship(RelationshipType relType, TokenObject firstArgument, TokenObject secondArgument) {
	if (relType == relationshipType) {
		if (firstArgument.getTokenType() == TokenType::NAME_WITH_QUOTATION && secondArgument.getTokenType() == TokenType::NAME_WITH_QUOTATION) {
			return handleConstantConstant(firstArgument, secondArgument);
		} else if (firstArgument.getTokenType() == TokenType::WILDCARD && secondArgument.getTokenType() == TokenType::NAME_WITH_QUOTATION) {
			return handleWildcardConstant(secondArgument);
		} else if (firstArgument.getTokenType() == TokenType::NAME_WITH_QUOTATION && secondArgument.getTokenType() == TokenType::WILDCARD) {
			return handleConstantWildcard(firstArgument);
		} else if (firstArgument.getTokenType() == TokenType::WILDCARD && secondArgument.getTokenType() == TokenType::WILDCARD) {
			return handleWilcardWildcard();
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

// To answer Calls(_, p)
std::unordered_set<std::string> CallsRelationshipStorageInterface::getRelationshipWithFirstWilcard(RelationshipType relType, DesignEntity returnType) {
	if (relType == relationshipType) {
		std::unordered_set<std::string> result;
		for (auto const& pair : this->procBackwardStorage) {
			result.insert(pair.first);
		}

		return result;
	}
	return std::unordered_set<std::string>();
}

// To answer Calls(p, _)
std::unordered_set<std::string> CallsRelationshipStorageInterface::getRelationshipWithSecondWildcard(RelationshipType relType, DesignEntity returnType) {
	if (relType == relationshipType) {
		std::unordered_set<std::string> result;
		for (auto const& pair : this->procForwardStorage) {
			result.insert(pair.first);
		}

		return result;
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

bool CallsRelationshipStorageInterface::handleConstantConstant(TokenObject firstArgument, TokenObject secondArgument) {
	if (this->procForwardStorage.find(firstArgument.getValue()) != this->procForwardStorage.end()) {
		std::unordered_set<std::string> set = this->procForwardStorage.find(firstArgument.getValue())->second;
		return set.find(secondArgument.getValue()) != set.end();
	}

	return false;
}

bool CallsRelationshipStorageInterface::handleConstantWildcard(TokenObject firstArgument) {
	return this->procForwardStorage.find(firstArgument.getValue()) != this->procForwardStorage.end();
}

bool CallsRelationshipStorageInterface::handleWildcardConstant(TokenObject secondArgument) {
	return this->procBackwardStorage.find(secondArgument.getValue()) != this->procBackwardStorage.end();
}

bool CallsRelationshipStorageInterface::handleWilcardWildcard() {
	return this->procForwardStorage.size() != 0;
}
