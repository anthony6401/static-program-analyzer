#ifndef SPA_SELECTCLAUSE_H
#define SPA_SELECTCLAUSE_H
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/Declaration.h"

// Select v; Have to determine entity type of v
class SelectClause : public Clause {
private:
   std::string name; // Might not be needed
   TokenType entityReturnType;

public:
    std::vector<std::string> evaluateClause() override;
    SelectClause(TokenType entityReturnType);
};

#endif //SPA_SELECTCLAUSE_H
