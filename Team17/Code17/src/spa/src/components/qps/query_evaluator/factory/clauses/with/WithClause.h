#ifndef SPA_WITHCLAUSE_H
#define SPA_WITHCLAUSE_H

#include <unordered_map>
#include <list>
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/pkb/clients/QPSClient.h"
#include "models/Entity/DesignEntity.h"

class WithClause : public Clause {
private:
    std::vector<TokenObject> left;
    std::vector<TokenObject> right;
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;
    QPSClient qpsClient;

public:
    WithClause(std::vector<TokenObject> left, std::vector<TokenObject> right, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    ResultTable evaluateClause() override;
    size_t getNumberOfSynonyms() override;
    std::set<std::string> getAllSynonyms() override;
    std::unordered_set<std::string> findCommonAttributeValues(std::unordered_set<std::string> leftNameResult, std::unordered_set<std::string> rightNameResult);
    std::unordered_set<std::pair<std::string, std::string>, hashFunction> findCommonAttributeStatements(const std::unordered_set<std::string>& leftResult, std::unordered_set<std::string> rightResult);
    ResultTable evaluateAttributeAttribute();
    ResultTable evaluateAttributeInteger();
    ResultTable evaluateAttributeNameQuotes();
    ResultTable evaluateIntegerAttribute();
    ResultTable evaluateIntegerOrNameQuotes();
    ResultTable evaluateNameQuotesAttribute();
    ResultTable evaluateNameQuotesNameQuotes();
};

#endif //SPA_WITHCLAUSE_H
