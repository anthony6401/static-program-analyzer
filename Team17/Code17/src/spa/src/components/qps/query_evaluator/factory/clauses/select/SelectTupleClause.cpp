#include "SelectTupleClause.h"
#include "components/pkb/pkb.h"
#include "components/pkb/clients/QPSClient.h"

SelectTupleClause::SelectTupleClause(std::vector<TokenObject> tuple, std::unordered_set<std::string> &synonymsInTable, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient)
        : tuple(tuple), synonymsInTable(synonymsInTable), synonymToDesignEntityMap(synonymToDesignEntityMap), qpsClient(qpsClient) {}

ResultTable SelectTupleClause::evaluateClause() {
    ResultTable resultTable;
    // TokenObjects can be synonyms of attributes
    return resultTable;
}

size_t SelectTupleClause::getNumberOfSynonyms() {
    return 1;
}

std::set<std::string> SelectTupleClause::getAllSynonyms() {
    std::set<std::string> synonyms = {};
    return synonyms;
}