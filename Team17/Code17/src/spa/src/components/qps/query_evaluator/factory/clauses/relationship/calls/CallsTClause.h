#ifndef SPA_CALLSTCLAUSE_H
#define SPA_CALLSTCLAUSE_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/pkb/clients/QPSClient.h"
#include "Calls.h"
#include <unordered_map>

class CallsTClause : public Calls {
private:
    static const size_t priority = 9;

public:
    CallsTClause(TokenObject left, TokenObject right,
                std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
};

#endif //SPA_CALLSTCLAUSE_H
