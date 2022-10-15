#ifndef SPA_MODIFIESCLAUSE_H
#define SPA_MODIFIESCLAUSE_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/pkb/clients/QPSClient.h"
#include <unordered_map>

class ModifiesClause : public Clause {
private:
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;
    QPSClient qpsClient;
    TokenObject left;
    TokenObject right;

public:
    ModifiesClause(TokenObject left, TokenObject right,
               std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    ResultTable evaluateClause() override;
    size_t getNumberOfSynonyms() override;
    std::set<std::string> getAllSynonyms() override;
    ResultTable evaluateSynonymSynonym();
    ResultTable evaluateSynonymWildcard();
    ResultTable evaluateSynonymNameQuotes();
    ResultTable evaluateSecondAsSynonym();
    ResultTable evaluateSecondAsWildcard();
    ResultTable evaluateWithoutSynonymOrWildCard();
};


#endif //SPA_MODIFIESCLAUSE_H
