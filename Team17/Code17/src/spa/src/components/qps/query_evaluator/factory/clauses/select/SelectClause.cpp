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

size_t SelectClause::getNumberOfSynonyms() {
    return 1;
}

std::unordered_set<std::string> SelectClause::getAllSynonyms() {
    std::unordered_set<std::string> synonyms = {};
    synonyms.emplace(synonym.getSynonym());
    return synonyms;
}