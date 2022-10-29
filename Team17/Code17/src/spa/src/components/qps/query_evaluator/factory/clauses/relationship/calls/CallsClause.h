#ifndef SPA_CALLSCLAUSE_H
#define SPA_CALLSCLAUSE_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/pkb/clients/QPSClient.h"
#include "Calls.h"
#include <unordered_map>

class CallsClause : public Calls {
private:
    static const size_t priority = 4;

public:
    CallsClause(TokenObject left, TokenObject right,
                  std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
};

#endif //SPA_CALLSCLAUSE_H
