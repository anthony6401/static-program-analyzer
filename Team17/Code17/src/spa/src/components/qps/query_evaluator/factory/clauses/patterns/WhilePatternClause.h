#ifndef SPA_WHILEPATTERNCLAUSE_H
#define SPA_WHILEPATTERNCLAUSE_H

#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/pkb/clients/QPSClient.h"

class WhilePatternClause : public Clause {
private:
    std::string whileSynonym;
    QPSClient qpsClient;
    TokenObject firstArgument;
    ResultTable evaluateFirstArgAsSynonym();
    ResultTable evaluateFirstArgAsNameQuotes();
    ResultTable evaluateFirstArgAsWildcard();

public:
    WhilePatternClause(std::string whileSynonym, TokenObject firstArgument, QPSClient qpsClient);
    ResultTable evaluateClause() override;
    size_t getNumberOfSynonyms() override;
    std::set<std::string> getAllSynonyms() override;
};

#endif //SPA_WHILEPATTERNCLAUSE_H
