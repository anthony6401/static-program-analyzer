#ifndef SPA_ASSIGNPATTERNCLAUSE_H
#define SPA_ASSIGNPATTERNCLAUSE_H

#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/pkb/clients/QPSClient.h"

class AssignPatternClause : public Clause {
private:
    std::string assignSynonym;
    QPSClient qpsClient;
    TokenObject left;
    TokenObject right;
    ResultTable evaluateFirstAsSynonym();
    ResultTable evaluateFirstAsWildcard();
    ResultTable evaluateFirstAsNameQuotes();

public:
    AssignPatternClause(std::string assignSynonym, TokenObject left, TokenObject right, QPSClient qpsClient);
    ResultTable evaluateClause() override;
    size_t getNumberOfSynonyms() override;
    std::set<std::string> getAllSynonyms() override;
};

#endif //SPA_ASSIGNPATTERNCLAUSE_H
