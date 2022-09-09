#ifndef SPA_MODIFIESSCLAUSE_H
#define SPA_MODIFIESSCLAUSE_H
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/pkb/clients/QPSClient.h"
#include <unordered_map>
#include <list>

class ModifiesSClause : public Clause {
private:
    std::unordered_map<std::string, TokenType> synonymToDesignEntityMap;
    Select synonym;
    QPSClient qpsClient;
    TokenObject left;
    TokenObject right;

public:
    ModifiesSClause(TokenObject left, TokenObject right, Select synonym,
                    std::unordered_map<std::string, TokenType> synonymToDesignEntityMap, QPSClient qpsClient);
    RawResult evaluateClause() override;
    TokenType getRelationshipType();
    RawResult evaluateSynonymSynonym();
    RawResult evaluateSynonymWildcard();
    RawResult evaluateSynonymIdentQuotes();
    RawResult evaluateIntegerSynonym();
    RawResult evaluateIntegerWildcard();
    RawResult evaluateIntegerIdentQuotes();
};

#endif //SPA_MODIFIESSCLAUSE_H
