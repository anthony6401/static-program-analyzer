#ifndef SPA_NEXTCLAUSE_H
#define SPA_NEXTCLAUSE_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/pkb/clients/QPSClient.h"
#include <unordered_map>

class NextClause : public Clause {
private:
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;
    QPSClient qpsClient;
    TokenObject left;
    TokenObject right;
    size_t priority = 8;
    ResultTable evaluateSynonymSynonym();
    ResultTable evaluateSynonymWildcard();
    ResultTable evaluateSynonymInteger();
    ResultTable evaluateIntegerSynonym();
    ResultTable evaluateIntegerWildcard();
    ResultTable evaluateIntegerInteger();
    ResultTable evaluateWildcardSynonym();
    ResultTable evaluateWildcardWildcard();
    ResultTable evaluateWildcardInteger();

public:
    NextClause(TokenObject left, TokenObject right,
                  std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    ResultTable evaluateClause() override;
    size_t getNumberOfSynonyms() override;
    std::set<std::string> getAllSynonyms() override;
    size_t getPriority() override;
};


#endif //SPA_NEXTCLAUSE_H
