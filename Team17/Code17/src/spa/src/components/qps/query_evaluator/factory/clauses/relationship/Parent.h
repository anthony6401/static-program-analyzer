#ifndef SPA_PARENT_H
#define SPA_PARENT_H

#include "components/qps/query_preprocessor/query_tokenizer/TokenObject.h"
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/pkb/clients/QPSClient.h"
#include <unordered_map>

class Parent : public Clause {
private:
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;
    RelationshipType relationshipType;
    QPSClient qpsClient;
    TokenObject left;
    TokenObject right;
    size_t priority;
    ResultTable evaluateSynonymSynonym(RelationshipType relationshipType);
    ResultTable evaluateSynonymWildcard(RelationshipType relationshipType);
    ResultTable evaluateSynonymInteger(RelationshipType relationshipType);
    ResultTable evaluateIntegerSynonym(RelationshipType relationshipType);
    ResultTable evaluateIntegerWildcard(RelationshipType relationshipType);
    ResultTable evaluateIntegerInteger(RelationshipType relationshipType);
    ResultTable evaluateWildcardSynonym(RelationshipType relationshipType);
    ResultTable evaluateWildcardWildcard(RelationshipType relationshipType);
    ResultTable evaluateWildcardInteger(RelationshipType relationshipType);

public:
    Parent(TokenObject left, TokenObject right, RelationshipType relationshipType,
                 std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    ResultTable evaluateClause() override;
    size_t getNumberOfSynonyms() override;
    std::set<std::string> getAllSynonyms() override;
    size_t getPriority() override;
};

#endif //SPA_PARENT_H
