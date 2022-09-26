#include "SelectClause.h"
#include "components/pkb/pkb.h"
#include "components/pkb/clients/QPSClient.h"
#include "iostream"

SelectClause::SelectClause(Select synonym, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient)
        : synonym(synonym), synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {}

ResultTable SelectClause::evaluateClause() {
    std::string selectSynonym = synonym.getSynonym();
    DesignEntity returnType = synonymToDesignEntityMap[synonym.getSynonym()];
    std::unordered_set<std::string> results = qpsClient.getAllEntity(returnType);
    return {selectSynonym, results}; // {"a", {"1", "2", "3", "4"}};
}

size_t SelectClause::getNumberOfSynonyms() {
    return 1;
}

std::set<std::string> SelectClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    synonyms.emplace(synonym.getSynonym());
    return synonyms;
}