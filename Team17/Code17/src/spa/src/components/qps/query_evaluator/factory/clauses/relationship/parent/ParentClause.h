#ifndef SPA_PARENTCLAUSE_H
#define SPA_PARENTCLAUSE_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/pkb/clients/QPSClient.h"
#include "Parent.h"
#include <unordered_map>

class ParentClause : public Parent {
private:
    static const size_t priority = 7;
public:
    ParentClause(TokenObject left, TokenObject right,
                 std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap,
                 QPSClient qpsClient);
};

#endif //SPA_PARENTCLAUSE_H
