#ifndef SPA_FOLLOWSTCLAUSE_H
#define SPA_FOLLOWSTCLAUSE_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/pkb/clients/QPSClient.h"
#include "Follows.h"
#include <unordered_map>

class FollowsTClause : public Follows {
private:
    static const size_t priority = 10;

public:
    FollowsTClause(TokenObject left, TokenObject right,
                  std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
};

#endif //SPA_FOLLOWSTCLAUSE_H
