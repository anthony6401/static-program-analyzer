#ifndef SPA_MODIFIESPCLAUSE_H
#define SPA_MODIFIESPCLAUSE_H
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/pkb/clients/QPSClient.h"
#include <unordered_map>
#include <list>

class ModifiesPClause : public Clause {
private:
    std::unordered_map<std::string, TokenType> synonymToDesignEntityMap;
    Select synonym;
    QPSClient qpsClient;
    TokenObject left;
    TokenObject right;

public:
    ModifiesPClause(TokenObject left, TokenObject right, Select synonym,
                    std::unordered_map<std::string, TokenType> synonymToDesignEntityMap, QPSClient qpsClient);
    RawResult evaluateClause() override;
};
#endif //SPA_MODIFIESPCLAUSE_H
