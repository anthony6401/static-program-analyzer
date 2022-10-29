#include "SelectSynonymClause.h"
#include <utility>
#include "components/pkb/pkb.h"
#include "components/pkb/clients/QPSClient.h"

SelectSynonymClause::SelectSynonymClause(TokenObject selectSynonym, std::unordered_set<std::string> &synonymsInTable, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient)
        : selectSynonym(std::move(selectSynonym)), synonymsInTable(synonymsInTable), synonymToDesignEntityMap(std::move(synonymToDesignEntityMap)), qpsClient(qpsClient) {}

ResultTable SelectSynonymClause::evaluateClause() {
    std::string selectSynonymValue = selectSynonym.getValue();
    ResultTable resultTable;

    if (synonymsInTable.find(selectSynonymValue) != synonymsInTable.end()) {
        return resultTable;
    } else {
        DesignEntity returnType = synonymToDesignEntityMap[selectSynonymValue];
        std::unordered_set<std::string> results = qpsClient.getAllEntity(returnType);
        resultTable = std::move(ResultTable(selectSynonymValue, results));
        return resultTable;
    }
}

size_t SelectSynonymClause::getNumberOfSynonyms() {
    return 1;
}

size_t SelectSynonymClause::getPriority() {
    return 0;
}

std::set<std::string> SelectSynonymClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    synonyms.emplace(selectSynonym.getValue());
    return synonyms;
}