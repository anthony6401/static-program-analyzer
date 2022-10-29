#ifndef SPA_PARENTTCLAUSE_H
#define SPA_PARENTTCLAUSE_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/pkb/clients/QPSClient.h"
#include "Parent.h"
#include <unordered_map>

class ParentTClause : public Parent {
private:
    static const size_t priority = 11;
public:
    ParentTClause(TokenObject left, TokenObject right,
                   std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
};

#endif //SPA_PARENTTCLAUSE_H
