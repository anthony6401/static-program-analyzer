#include "SelectClause.h"

SelectClause::SelectClause(Select synonym, std::unordered_map<std::string, TokenType> synonymToDesignEntityMap)
        : synonym(synonym), synonymToDesignEntityMap(synonymToDesignEntityMap) {}

std::unordered_set<std::string> SelectClause::evaluateClause() {
    std::unordered_set<std::string> results({"x", "y", "z"});
    // Call PKB API
    return results;
}