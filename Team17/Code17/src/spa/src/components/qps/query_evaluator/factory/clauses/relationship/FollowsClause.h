#ifndef SPA_FOLLOWSCLAUSE_H
#define SPA_FOLLOWSCLAUSE_H
#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/pkb/clients/QPSClient.h"
#include <unordered_map>
#include <list>

class FollowsClause : public Clause {
private:
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;
    Select synonym;
    QPSClient qpsClient;
    TokenObject left;
    TokenObject right;

public:
    FollowsClause(TokenObject left, TokenObject right, Select synonym,
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    RawResult evaluateClause() override;
    size_t getNumberOfSynonyms() override;
    std::unordered_set<std::string> getAllSynonyms() override;
    RawResult evaluateSynonymSynonym();
    RawResult evaluateSynonymWildcard();
    RawResult evaluateSynonymInteger();
    RawResult evaluateIntegerSynonym();
    RawResult evaluateIntegerWildcard();
    RawResult evaluateIntegerInteger();
    RawResult evaluateWildcardSynonym();
    RawResult evaluateWildcardWildcard();
    RawResult evaluateWildcardInteger();
    TokenType getRelationshipType();
};

#endif //SPA_FOLLOWSCLAUSE_H
