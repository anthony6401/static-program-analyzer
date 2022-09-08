#include "SelectClause.h"
#include "components/pkb/pkb.h"
#include "components/pkb/clients/QPSClient.h"

SelectClause::SelectClause(Select synonym, std::unordered_map<std::string, TokenType> synonymToDesignEntityMap, QPSClient qpsClient)
        : synonym(synonym), synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {}

RawResult SelectClause::evaluateClause() {
    std::unordered_set<std::string> results = qpsClient.getAllEntity(synonymToDesignEntityMap[synonym.getSynonym()]);
    return {results};
}