#include "SelectClause.h"
#include "components/pkb/pkb.h"
#include "components/pkb/clients/QPSClient.h"

SelectClause::SelectClause(Select synonym, std::unordered_map<std::string, TokenType> synonymToDesignEntityMap)
        : synonym(synonym), synonymToDesignEntityMap(synonymToDesignEntityMap) {}

std::unordered_set<std::string> SelectClause::evaluateClause() {
    PKB* pkb = new PKB();
    auto qpsClient = QPSClient(pkb);
    std::unordered_set<std::string> results = qpsClient.getAllEntity(synonymToDesignEntityMap[synonym.getSynonym()]);
    // Call PKB API
    return results;
}