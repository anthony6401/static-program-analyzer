#ifndef SPA_SELECTCLAUSE_H
#define SPA_SELECTCLAUSE_H

#include <unordered_map>
#include <list>
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/Declaration.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/pkb/clients/QPSClient.h"

class SelectClause : public Clause {
private:
    std::unordered_map<std::string, TokenType> synonymToDesignEntityMap;
    Select synonym;
    QPSClient qpsClient;

public:
    SelectClause(Select synonym, std::unordered_map<std::string, TokenType> synonymToDesignEntityMap, QPSClient qpsClient);
    RawResult evaluateClause() override;
};

#endif //SPA_SELECTCLAUSE_H
