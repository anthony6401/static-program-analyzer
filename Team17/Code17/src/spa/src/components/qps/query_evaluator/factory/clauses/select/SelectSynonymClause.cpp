#include "SelectSynonymClause.h"
#include "SelectClause.h"
#include "components/pkb/pkb.h"
#include "components/pkb/clients/QPSClient.h"
#include "iostream"

SelectSynonymClause::SelectSynonymClause(TokenObject selectSynonym, std::unordered_set<std::string> &synonymsInTable, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient)
        : selectSynonym(selectSynonym), synonymsInTable(synonymsInTable), synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {}

ResultTable SelectSynonymClause::evaluateClause() {
    std::cout << "IN EVALUATE SELECT SYNONYM CLAUSE" << std::endl;
    std::string selectSynonymValue = selectSynonym.getValue();
    ResultTable resultTable;
    // Select synonym found -> Just select synonym column from table
    if (synonymsInTable.find(selectSynonymValue) != synonymsInTable.end()) {
        std::cout << "select synonym found" << std::endl;
        resultTable.setIsSynonymResult();
        std::cout << "Table is synonym result: " << resultTable.getIsSynonymResult() << std::endl;
        return resultTable;
    } else { // Evaluate and select all synonym
        std::cout << "No select synonym found" << std::endl;
        DesignEntity returnType = synonymToDesignEntityMap[selectSynonymValue];
        std::unordered_set<std::string> results = qpsClient.getAllEntity(returnType);
        resultTable = std::move(ResultTable(selectSynonymValue, results));
        resultTable.setIsSynonymResult();
        std::cout << "Table is synonym result: " << resultTable.getIsSynonymResult() << std::endl;
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