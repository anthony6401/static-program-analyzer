#ifndef SPA_SELECTBOOLEANCLAUSE_H
#define SPA_SELECTBOOLEANCLAUSE_H

#include <list>
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/pkb/clients/QPSClient.h"
#include "models/Entity/DesignEntity.h"

class SelectBooleanClause : public Clause {
public:
    SelectBooleanClause();
    ResultTable evaluateClause() override;
    size_t getNumberOfSynonyms() override;
    std::set<std::string> getAllSynonyms() override;
    size_t getPriority() override;
};

#endif //SPA_SELECTBOOLEANCLAUSE_H
