#ifndef SPA_SELECTSYNONYMCLAUSE_H
#define SPA_SELECTSYNONYMCLAUSE_H

#include <unordered_map>
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/pkb/clients/QPSClient.h"
#include "models/Entity/DesignEntity.h"

class SelectSynonymClause : public Clause {
private:
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;
    std::unordered_set<std::string> synonymsInTable;
    TokenObject selectSynonym;
    QPSClient qpsClient;

public:
    SelectSynonymClause(TokenObject selectSynonym, std::unordered_set<std::string> &synonymsInTable, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    ResultTable evaluateClause() override;
    size_t getNumberOfSynonyms() override;
    std::set<std::string> getAllSynonyms() override;
};

#endif //SPA_SELECTSYNONYMCLAUSE_H
