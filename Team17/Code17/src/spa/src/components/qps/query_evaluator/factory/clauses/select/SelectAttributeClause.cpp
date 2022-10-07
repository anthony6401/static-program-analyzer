#include "SelectAttributeClause.h"
#include "SelectClause.h"
#include "components/pkb/pkb.h"
#include "components/pkb/clients/QPSClient.h"
#include "iostream"

SelectAttributeClause::SelectAttributeClause(TokenObject selectSynonym, std::string attributeName, std::unordered_set<std::string> &synonymsInTable, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient)
        : selectSynonym(selectSynonym), attributeName(attributeName), synonymsInTable(synonymsInTable), synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {}

ResultTable SelectAttributeClause::evaluateClause() {
    // Evaluate all synonyms
    std::string selectSynonymValue = selectSynonym.getValue();
    ResultTable resultTable;
    DesignEntity returnType = synonymToDesignEntityMap[selectSynonymValue];
    std::unordered_set<std::string> results = qpsClient.getAllEntity(returnType);
    // Select synonym found -> evaluate by attribute name
    if (synonymsInTable.find(selectSynonymValue) != synonymsInTable.end()) {
    }
    return resultTable;
}


size_t SelectAttributeClause::getNumberOfSynonyms() {
    return 1;
}

std::set<std::string> SelectAttributeClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    synonyms.emplace(selectSynonym.getValue());
    return synonyms;
}
