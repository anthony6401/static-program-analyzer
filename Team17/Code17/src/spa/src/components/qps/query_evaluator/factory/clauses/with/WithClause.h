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
    TokenType leftType;
    TokenType rightType;
    std::vector<TokenObject> left;
    std::vector<TokenObject> right;
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;
    QPSClient qpsClient;

public:
    WithClause(TokenType leftType, TokenType rightType, std::vector<TokenObject> left, std::vector<TokenObject> right, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    ResultTable evaluateClause() override;
    size_t getNumberOfSynonyms() override;
    std::set<std::string> getAllSynonyms() override;
    std::unordered_set<std::string> findCommonAttributeNames(std::unordered_set<std::string> leftNameResult, std::unordered_set<std::string> rightNameResult);
    ResultTable evaluateAttributeAttribute();
    ResultTable evaluateAttributeInteger();
    ResultTable evaluateAttributeNameQuotes();
    ResultTable evaluateIntegerAttribute();
    ResultTable evaluateIntegerInteger();
    ResultTable evaluateIntegerNameQuotes();
    ResultTable evaluateNameQuotesAttribute();
    ResultTable evaluateNameQuotesInteger();
    ResultTable evaluateNameQuotesNameQuotes();
};

#endif //SPA_WITHCLAUSE_H
