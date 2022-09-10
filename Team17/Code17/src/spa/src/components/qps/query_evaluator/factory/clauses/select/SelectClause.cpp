#include "SelectClause.h"
#include "components/pkb/pkb.h"
#include "components/pkb/clients/QPSClient.h"

SelectClause::SelectClause(Select synonym, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient)
        : synonym(synonym), synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {}

RawResult SelectClause::evaluateClause() {
    DesignEntity returnType = synonymToDesignEntityMap[synonym.getSynonym()];
    // std::unordered_set<std::string> results = qpsClient.getAllEntity(returnType);
    return {};
}