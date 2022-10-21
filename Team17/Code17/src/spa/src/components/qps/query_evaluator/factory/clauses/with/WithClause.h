#ifndef SPA_WITHCLAUSE_H
#define SPA_WITHCLAUSE_H

#include <unordered_map>
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/pkb/clients/QPSClient.h"
#include "models/Entity/DesignEntity.h"

class WithClause : public Clause {
private:
    std::vector<TokenObject> left;
    std::vector<TokenObject> right;
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;
    QPSClient qpsClient;
    size_t priority = 0;
    std::unordered_set<std::string> findCommonAttributeValues(std::unordered_set<std::string> leftNameResult, std::unordered_set<std::string> rightNameResult);
    std::unordered_set<std::pair<std::string, std::string>, hashFunction> findCommonAttributeStatements(const std::unordered_set<std::string>& leftResult, std::unordered_set<std::string> rightResult);
    ResultTable evaluateAttributeAttribute();
    std::unordered_set<std::pair<std::string, std::string>, hashFunction> leftAndRightAlternativeAttributeResultsHandler(DesignEntity leftDesignEntityType, DesignEntity rightDesignEntityType);
    std::unordered_set<std::pair<std::string, std::string>, hashFunction> leftAlternativeAttributeResultsHandler(DesignEntity leftDesignEntityType, DesignEntity rightDesignEntityType);
    std::unordered_set<std::pair<std::string, std::string>, hashFunction> rightAlternativeAttributeResultsHandler(DesignEntity leftDesignEntityType, DesignEntity rightDesignEntityType);
    ResultTable evaluateAttributeInteger();
    ResultTable evaluateAttributeNameQuotes();
    ResultTable evaluateIntegerAttribute();
    ResultTable evaluateIntegerOrNameQuotes();
    ResultTable evaluateNameQuotesAttribute();

public:
    WithClause(std::vector<TokenObject> left, std::vector<TokenObject> right, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    ResultTable evaluateClause() override;
    size_t getNumberOfSynonyms() override;
    std::set<std::string> getAllSynonyms() override;
    size_t getPriority() override;
};

#endif //SPA_WITHCLAUSE_H
