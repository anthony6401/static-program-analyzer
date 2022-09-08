#include "ModifiesPClause.h"

ModifiesPClause::ModifiesPClause(TokenObject left, TokenObject right, Select synonym,
                                 std::unordered_map<std::string, TokenType> synonymToDesignEntityMap,
                                 QPSClient qpsClient) : left(left), right(right), synonym(synonym),
                                                        synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {};

std::unordered_set<std::string> ModifiesPClause::evaluateClause() {
    std::unordered_set<std::string> result;
    return result;
}

