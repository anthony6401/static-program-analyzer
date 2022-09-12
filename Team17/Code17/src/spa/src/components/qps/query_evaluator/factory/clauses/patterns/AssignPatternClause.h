#ifndef SPA_ASSIGNPATTERNCLAUSE_H
#define SPA_ASSIGNPATTERNCLAUSE_H

#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/pkb/clients/QPSClient.h"

class AssignPatternClause : public Clause {
private:
    std::string assignSynonym;
    Select synonym;
    QPSClient qpsClient;
    TokenObject left;
    TokenObject right;

public:
    AssignPatternClause(std::string assignSynonym, TokenObject left, TokenObject right, QPSClient qpsClient, Select synonym);
    RawResult evaluateClause() override;
    size_t getNumberOfSynonyms() override;
    std::unordered_set<std::string> getAllSynonyms() override;
    RawResult evaluateSynonymWildcard();
    RawResult evaluateSynonymExpression();
    RawResult evaluateSynonymNameQuotes();
    RawResult evaluateSynonymSubExpression();
    RawResult evaluateWildcardWildcard();
    RawResult evaluateWildcardExpression();
    RawResult evaluateWildcardNameQuotes();
    RawResult evaluateWildcardSubExpression();
    RawResult evaluateNameQuotesWildcard();
    RawResult evaluateNameQuotesExpression();
    RawResult evaluateNameQuotesNameQuotes();
    RawResult evaluateNameQuotesSubExpression();
};

#endif //SPA_ASSIGNPATTERNCLAUSE_H
