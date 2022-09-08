#include "ClauseCreator.h"
#include <memory>

/**
 * Creates a Select Clause object
 */
std::shared_ptr<Clause> ClauseCreator::createClause(Select synonym, std::unordered_map<std::string, TokenType> synonymToDesignEntityMap, QPSClient qpsClient) {
    return std::make_shared<SelectClause>(synonym, synonymToDesignEntityMap, qpsClient);
}

std::shared_ptr<Clause> ClauseCreator::createClause(SuchThat relationship, Select synonym, std::unordered_map<std::string, TokenType> synonymToDesignEntityMap, QPSClient qpsClient) {
    TokenType relationshipType = relationship.getRelationshipType();
    if (relationshipType == TokenType::MODIFIES) {

    }
}

