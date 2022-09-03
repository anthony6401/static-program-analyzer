#include "ClauseCreator.h"
#include <memory>

std::shared_ptr<Clause> ClauseCreator::createClause(Select synonym, std::unordered_map<std::string, TokenType> synonymToDesignEntityMap) {
    // TokenType returnTypeOfSynonym = synonymToDesignEntityMap[synonym.getName()];
    return std::make_shared<SelectClause>(synonym, synonymToDesignEntityMap);
}