#ifndef SPA_IFPATTERNCLAUSE_H
#define SPA_IFPATTERNCLAUSE_H

#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/pkb/clients/QPSClient.h"

class IfPatternClause : public Clause {
private:
    std::string ifSynonym;
    QPSClient qpsClient;
    TokenObject firstArgument;
    static const size_t priority = 2;
    ResultTable evaluateFirstArgAsSynonym();
    ResultTable evaluateFirstArgAsNameQuotes();
    ResultTable evaluateFirstArgAsWildcard();

public:
    IfPatternClause(std::string ifSynonym, TokenObject firstArgument, QPSClient qpsClient);
    ResultTable evaluateClause() override;
    size_t getNumberOfSynonyms() override;
    std::set<std::string> getAllSynonyms() override;
    size_t getPriority() override;
};

#endif //SPA_IFPATTERNCLAUSE_H
