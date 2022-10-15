#ifndef SPA_PARENTTCLAUSE_H
#define SPA_PARENTTCLAUSE_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/pkb/clients/QPSClient.h"
#include <unordered_map>

class ParentTClause : public Clause {
private:
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;
    QPSClient qpsClient;
    TokenObject left;
    TokenObject right;

public:
    ParentTClause(TokenObject left, TokenObject right,
                   std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    ResultTable evaluateClause() override;
    size_t getNumberOfSynonyms() override;
    std::set<std::string> getAllSynonyms() override;
    ResultTable evaluateSynonymSynonym();
    ResultTable evaluateSynonymWildcard();
    ResultTable evaluateSynonymInteger();
    ResultTable evaluateIntegerSynonym();
    ResultTable evaluateIntegerWildcard();
    ResultTable evaluateIntegerInteger();
    ResultTable evaluateWildcardSynonym();
    ResultTable evaluateWildcardWildcard();
    ResultTable evaluateWildcardInteger();
};

#endif //SPA_PARENTTCLAUSE_H
