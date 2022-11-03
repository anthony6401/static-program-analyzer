#ifndef SPA_NEXTTCLAUSE_H
#define SPA_NEXTTCLAUSE_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/pkb/clients/QPSClient.h"
#include "Next.h"
#include <unordered_map>

class NextTClause : public Next {
private:
    static const size_t priority = 22;

public:
    NextTClause(TokenObject left, TokenObject right,
               std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
};

#endif //SPA_NEXTTCLAUSE_H
