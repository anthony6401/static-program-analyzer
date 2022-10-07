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

    // evaluate by attribute name
    if (synonymsInTable.find(selectSynonymValue) != synonymsInTable.end()) {

    } else {
        DesignEntity returnType = synonymToDesignEntityMap[selectSynonymValue];
        // evaluate by synonym
        std::unordered_set<std::string> results = qpsClient.getAllEntity(returnType);
        // evaluate by attribute
    }
    return resultTable;
}


bool SelectAttributeClause::isAlternateAttributeName(DesignEntity returnType, std::string attributeName) {
    // Default returned values are statement numbers
    if (returnType == DesignEntity::CALL || returnType == DesignEntity::READ || returnType == DesignEntity::PRINT) {
        if (attributeName == "procName" || attributeName == "varName") {
            return true;
        }
    }
    return false;
}


size_t SelectAttributeClause::getNumberOfSynonyms() {
    return 1;
}

std::set<std::string> SelectAttributeClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    synonyms.emplace(selectSynonym.getValue());
    return synonyms;
}
