#ifndef SPA_SELECTCLAUSE_H
#define SPA_SELECTCLAUSE_H

#include <unordered_map>
#include <list>
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/Declaration.h"
#include "components/qps/abstract_query_object/Select.h"

// Select v; Have to determine entity type of v
class SelectClause : public Clause {
private:
    std::unordered_map<std::string, TokenType> synonymToDesignEntityMap;
    Select synonym;

public:
    SelectClause(Select synonym, std::unordered_map<std::string, TokenType> synonymToDesignEntityMap);
    std::list<std::string> evaluateClause() override;
};

#endif //SPA_SELECTCLAUSE_H
