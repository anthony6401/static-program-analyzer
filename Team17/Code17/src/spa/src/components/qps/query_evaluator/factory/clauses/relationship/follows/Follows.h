#ifndef SPA_FOLLOWS_H
#define SPA_FOLLOWS_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/pkb/clients/QPSClient.h"
#include <unordered_map>

class Follows : public Clause {
private:
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;
    QPSClient qpsClient;
    TokenObject left;
    TokenObject right;
    RelationshipType relationshipType;
    size_t priority;
    ResultTable evaluateSynonymSynonym(RelationshipType relationshipType);
    ResultTable evaluateSynonymWildcard(RelationshipType relationshipType);
    ResultTable evaluateSynonymInteger(RelationshipType relationshipType);
    ResultTable evaluateIntegerSynonym(RelationshipType relationshipType);
    ResultTable evaluateWildcardSynonym(RelationshipType relationshipType);
    ResultTable evaluateWithoutSynonym(RelationshipType relationshipType);

public:
    Follows(TokenObject left, TokenObject right, RelationshipType relationshipType, size_t priority,
                  std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    ResultTable evaluateClause() override;
    size_t getNumberOfSynonyms() override;
    std::set<std::string> getAllSynonyms() override;
    size_t getPriority() override;
};

#endif //SPA_FOLLOWS_H
