#ifndef SPA_NEXTCLAUSE_H
#define SPA_NEXTCLAUSE_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/pkb/clients/QPSClient.h"
#include "Next.h"
#include <unordered_map>

class NextClause : public Next {
private:
    static const size_t priority = 8;
public:
    NextClause(TokenObject left, TokenObject right,
                  std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
};


#endif //SPA_NEXTCLAUSE_H
