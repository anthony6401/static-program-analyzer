#include "ClauseCreator.h"
#include <memory>

std::shared_ptr<Clause> ClauseCreator::createClause(Select synonym, std::unordered_map<std::string, TokenType> synonymToDesignEntityMap) {
    return std::make_shared<SelectClause>(synonym, synonymToDesignEntityMap);
}