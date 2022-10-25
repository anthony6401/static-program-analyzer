#ifndef SPA_AFFECTSCLAUSE_H
#define SPA_AFFECTSCLAUSE_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/pkb/clients/QPSClient.h"
#include "Affects.h"
#include <unordered_map>

class AffectsClause : public Affects {
private:
    static const size_t priority = 23;

public:
    AffectsClause(TokenObject left, TokenObject right,
                std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
};

#endif //SPA_AFFECTSCLAUSE_H
