#include "SelectClause.h"
#include "components/pkb/pkb.h"
#include "components/pkb/clients/QPSClient.h"
#include "iostream"

SelectClause::SelectClause(Select synonym, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient)
        : synonym(synonym), synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {}

RawResult SelectClause::evaluateClause() {
    std::cout << "----- Select Clause -------" << std::endl;
    DesignEntity returnType = synonymToDesignEntityMap[synonym.getSynonym()];
    // std::unordered_set<std::string> results = qpsClient.getAllEntity(returnType);
    //return {"v", {"x", "y", "z"}};
    return {"a", {"1", "2", "3", "4"}};
}

size_t SelectClause::getNumberOfSynonyms() {
    return 1;
}

std::set<std::string> SelectClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    synonyms.emplace(synonym.getSynonym());
    return synonyms;
}