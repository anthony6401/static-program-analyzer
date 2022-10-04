#ifndef SPA_SELECTBOOLEANCLAUSE_H
#define SPA_SELECTBOOLEANCLAUSE_H

#include <unordered_map>
#include <list>
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/pkb/clients/QPSClient.h"
#include "models/Entity/DesignEntity.h"

class SelectBooleanClause : public Clause {
private:
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;
    Select select;
    QPSClient qpsClient;

public:
    SelectBooleanClause(Select select, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    ResultTable evaluateClause() override;
    size_t getNumberOfSynonyms() override;
    std::set<std::string> getAllSynonyms() override;
};

#endif //SPA_SELECTBOOLEANCLAUSE_H
