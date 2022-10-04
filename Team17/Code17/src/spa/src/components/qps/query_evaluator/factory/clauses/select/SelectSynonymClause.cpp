#include "SelectSynonymClause.h"
#include "SelectClause.h"
#include "components/pkb/pkb.h"
#include "components/pkb/clients/QPSClient.h"

SelectSynonymClause::SelectSynonymClause(TokenObject selectSynonym, std::unordered_set<std::string> &synonymsInTable, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient)
        : selectSynonym(selectSynonym), synonymsInTable(synonymsInTable), synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {}

ResultTable SelectSynonymClause::evaluateClause() {
    std::string selectSynonymValue = selectSynonym.getValue();
    ResultTable resultTable;
    // Select synonym found -> Just select synonym column from table
    if (synonymsInTable.find(selectSynonymValue) != synonymsInTable.end()) {
        resultTable.setIsSynonymResult();
        return resultTable;
    } else { // Evaluate and select all synonym
        resultTable.setIsSynonymResult();
        DesignEntity returnType = synonymToDesignEntityMap[selectSynonymValue];
        std::unordered_set<std::string> results = qpsClient.getAllEntity(returnType);
        resultTable = ResultTable(selectSynonymValue, results);
        return resultTable;
    }

}

size_t SelectSynonymClause::getNumberOfSynonyms() {
    return 1;
}

std::set<std::string> SelectSynonymClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    synonyms.emplace(selectSynonym.getValue());
    return synonyms;
}