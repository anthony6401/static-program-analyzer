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
    DesignEntity returnType = synonymToDesignEntityMap[selectSynonymValue];
    ResultTable resultTable;

    if (synonymsInTable.find(selectSynonymValue) != synonymsInTable.end()) {
        if (checkIsAlternateAttributeName(returnType, attributeName)) {
            resultTable.setHasAlternativeAttributeNameToTrue();
            return resultTable;
        }
        return resultTable;
    } else {
        // evaluate by synonym
        std::unordered_set<std::string> results = qpsClient.getAllEntity(returnType);
        resultTable = std::move(ResultTable(selectSynonymValue, results));
        return resultTable;
    }
}


bool SelectAttributeClause::checkIsAlternateAttributeName(DesignEntity returnType, std::string attributeName) {
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
