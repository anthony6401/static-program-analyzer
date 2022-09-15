#ifndef SPA_FOLLOWSTCLAUSE_H
#define SPA_FOLLOWSTCLAUSE_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/pkb/clients/QPSClient.h"
#include <unordered_map>
#include <list>

class FollowsTClause : public Clause {
private:
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;
    Select synonym;
    QPSClient qpsClient;
    TokenObject left;
    TokenObject right;

public:
    FollowsTClause(TokenObject left, TokenObject right, Select synonym,
                  std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    RawResult evaluateClause() override;
    size_t getNumberOfSynonyms() override;
    std::set<std::string> getAllSynonyms() override;
    std::vector<std::pair<std::string, std::string>> processMapToVectorPair(std::unordered_map<std::string, std::unordered_set<std::string>> results);
    std::unordered_set<std::string> processMapToSet(std::unordered_map<std::string, std::unordered_set<std::string>> results);
    static RelationshipType getRelationshipType();
    RawResult evaluateSynonymSynonym();
    RawResult evaluateSynonymWildcard();
    RawResult evaluateSynonymInteger();
    RawResult evaluateIntegerSynonym();
    RawResult evaluateIntegerWildcard();
    RawResult evaluateIntegerInteger();
    RawResult evaluateWildcardSynonym();
    RawResult evaluateWildcardWildcard();
    RawResult evaluateWildcardInteger();
};

#endif //SPA_FOLLOWSTCLAUSE_H
