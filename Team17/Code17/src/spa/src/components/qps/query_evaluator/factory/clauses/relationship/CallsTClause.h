#ifndef SPA_CALLSTCLAUSE_H
#define SPA_CALLSTCLAUSE_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/pkb/clients/QPSClient.h"
#include <unordered_map>

class CallsTClause : public Clause {
private:
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;
    QPSClient qpsClient;
    TokenObject left;
    TokenObject right;

public:
    CallsTClause(TokenObject left, TokenObject right,
                std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    ResultTable evaluateClause() override;
    size_t getNumberOfSynonyms() override;
    std::set<std::string> getAllSynonyms() override;
    ResultTable evaluateSynonymSynonym();
    ResultTable evaluateSynonymWildcard();
    ResultTable evaluateSynonymNameQuotes();
    ResultTable evaluateWildcardSynonym();
    ResultTable evaluateWildcardWildcard();
    ResultTable evaluateWildcardNameQuotes();
    ResultTable evaluateNameQuotesSynonym();
    ResultTable evaluateNameQuotesWildcard();
    ResultTable evaluateNameQuotesNameQuotes();
};

#endif //SPA_CALLSTCLAUSE_H
