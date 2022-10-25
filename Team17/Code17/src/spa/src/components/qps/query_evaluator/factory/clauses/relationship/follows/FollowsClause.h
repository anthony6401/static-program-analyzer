#ifndef SPA_FOLLOWSCLAUSE_H
#define SPA_FOLLOWSCLAUSE_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/pkb/clients/QPSClient.h"
#include "Follows.h"
#include <unordered_map>

class FollowsClause : public Follows {
private:
    static const size_t priority = 3;

public:
    FollowsClause(TokenObject left, TokenObject right,
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
};

#endif //SPA_FOLLOWSCLAUSE_H
