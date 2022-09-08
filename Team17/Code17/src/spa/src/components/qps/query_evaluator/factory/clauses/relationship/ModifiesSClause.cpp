#include "ModifiesSClause.h"

ModifiesSClause::ModifiesSClause(TokenObject left, TokenObject right, Select synonym,
                                 std::unordered_map<std::string, TokenType> synonymToDesignEntityMap,
                                 QPSClient qpsClient) : left(left), right(right), synonym(synonym),
                                 synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {};

std::unordered_set<std::string> ModifiesSClause::evaluateClause() {
    std::unordered_set<std::string> result;
    return result;
}


