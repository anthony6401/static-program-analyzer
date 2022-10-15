#include "SelectAttributeClause.h"
#include <utility>
#include "components/pkb/pkb.h"
#include "components/pkb/clients/QPSClient.h"

SelectAttributeClause::SelectAttributeClause(TokenObject selectSynonym, std::string attributeName, std::unordered_set<std::string> &synonymsInTable, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient)
        : selectSynonym(std::move(selectSynonym)), attributeName(std::move(attributeName)), synonymsInTable(synonymsInTable), synonymToDesignEntityMap(std::move(synonymToDesignEntityMap)), qpsClient(qpsClient) {}

ResultTable SelectAttributeClause::evaluateClause() {
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
        std::unordered_set<std::string> results = qpsClient.getAllEntity(returnType);
        resultTable = std::move(ResultTable(selectSynonymValue, results));
        if (checkIsAlternateAttributeName(returnType, attributeName)) {
            resultTable.setHasAlternativeAttributeNameToTrue();
            return resultTable;
        }

        return resultTable;
    }
}


bool SelectAttributeClause::checkIsAlternateAttributeName(DesignEntity returnType, std::string attributeName) {
    if (returnType == DesignEntity::CALL || returnType == DesignEntity::READ || returnType == DesignEntity::PRINT) {
        return (attributeName == "procName" || attributeName == "varName");
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
