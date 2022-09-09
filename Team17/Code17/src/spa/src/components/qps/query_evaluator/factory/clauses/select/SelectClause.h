#ifndef SPA_SELECTCLAUSE_H
#define SPA_SELECTCLAUSE_H

#include <unordered_map>
#include <list>
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/Declaration.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/pkb/clients/QPSClient.h"
#include "models/Entity/DesignEntity.h"

// Select v; Have to determine entity type of v
class SelectClause : public Clause {
private:
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;
    Select synonym;
    QPSClient qpsClient;

public:
    SelectClause(Select synonym, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    std::unordered_set<std::string> evaluateClause() override;
};

#endif //SPA_SELECTCLAUSE_H
