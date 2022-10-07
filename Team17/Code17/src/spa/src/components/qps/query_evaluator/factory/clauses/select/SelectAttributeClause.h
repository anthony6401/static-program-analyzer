#ifndef SPA_SELECTATTRIBUTECLAUSE_H
#define SPA_SELECTATTRIBUTECLAUSE_H

#include <unordered_map>
#include <list>
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/pkb/clients/QPSClient.h"
#include "models/Entity/DesignEntity.h"

class SelectAttributeClause : public Clause {
private:
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;
    std::unordered_set<std::string> synonymsInTable;
    TokenObject selectSynonym;
    std::string attributeName;
    QPSClient qpsClient;

public:
    SelectAttributeClause(TokenObject selectSynonym, std::string attributeName, std::unordered_set<std::string> &synonymsInTable, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    ResultTable evaluateClause() override;
    size_t getNumberOfSynonyms() override;
    std::set<std::string> getAllSynonyms() override;
    bool checkIsAlternateAttributeName(DesignEntity returnType, std::string attributeName);
};

#endif //SPA_SELECTATTRIBUTECLAUSE_H
