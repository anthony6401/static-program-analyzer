#ifndef SPA_SELECTCLAUSE_H
#define SPA_SELECTCLAUSE_H
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/Declaration.h"

// Select v; Have to determine entity type of v
class SelectClause : public Clause {
private:
   Declaration declarations;

public:
    std::string evaluateClause() override;
};

#endif //SPA_SELECTCLAUSE_H
