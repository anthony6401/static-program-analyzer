#ifndef SPA_CALLSCLAUSE_H
#define SPA_CALLSCLAUSE_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/pkb/clients/QPSClient.h"
#include <unordered_map>

class CallsClause : public Clause {
private:
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;
    QPSClient qpsClient;
    TokenObject left;
    TokenObject right;
    size_t priority = 0;
    ResultTable evaluateSynonymSynonym();
    ResultTable evaluateSynonymWildcard();
    ResultTable evaluateSynonymNameQuotes();
    ResultTable evaluateWildcardSynonym();
    ResultTable evaluateWildcardWildcard();
    ResultTable evaluateWildcardNameQuotes();
    ResultTable evaluateNameQuotesSynonym();
    ResultTable evaluateNameQuotesWildcard();
    ResultTable evaluateNameQuotesNameQuotes();

public:
    CallsClause(TokenObject left, TokenObject right,
                  std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    ResultTable evaluateClause() override;
    size_t getNumberOfSynonyms() override;
    std::set<std::string> getAllSynonyms() override;
    size_t getPriority() override;
};

#endif //SPA_CALLSCLAUSE_H
