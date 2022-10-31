#ifndef SPA_CONTAINERPATTERNCLAUSE_H
#define SPA_CONTAINERPATTERNCLAUSE_H

#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/pkb/clients/QPSClient.h"

class ContainerPatternClause : public Clause {
private:
    std::string synonym;
    QPSClient qpsClient;
    TokenObject firstArgument;
    static const size_t priority = 2;
    DesignEntity designEntityType;
    ResultTable evaluateFirstArgAsSynonym(DesignEntity designEntityType);
    ResultTable evaluateFirstArgAsNameQuotes(DesignEntity designEntityType);
    ResultTable evaluateFirstArgAsWildcard(DesignEntity designEntityType);

public:
    ContainerPatternClause(std::string synonym, DesignEntity designEntityType, TokenObject firstArgument, QPSClient qpsClient);
    ResultTable evaluateClause() override;
    size_t getNumberOfSynonyms() override;
    std::set<std::string> getAllSynonyms() override;
    size_t getPriority() override;
};


#endif //SPA_CONTAINERPATTERNCLAUSE_H
