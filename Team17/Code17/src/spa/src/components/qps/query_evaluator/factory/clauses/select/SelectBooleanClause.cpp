#include "SelectBooleanClause.h"

SelectBooleanClause::SelectBooleanClause(Select select, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient)
        : select(select), synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {}

ResultTable SelectBooleanClause::evaluateClause() {
    std::string selectSynonym = select.getSynonym();
    DesignEntity returnType = synonymToDesignEntityMap[select.getSynonym()];
    std::unordered_set<std::string> results = qpsClient.getAllEntity(returnType);
    return {selectSynonym, results}; // {"a", {"1", "2", "3", "4"}};
}

size_t SelectBooleanClause::getNumberOfSynonyms() {
    return 1;
}

std::set<std::string> SelectBooleanClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    synonyms.emplace(select.getSynonym());
    return synonyms;
}
