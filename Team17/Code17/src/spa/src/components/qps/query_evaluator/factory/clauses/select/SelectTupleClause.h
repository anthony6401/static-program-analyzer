#ifndef SPA_SELECTTUPLECLAUSE_H
#define SPA_SELECTTUPLECLAUSE_H

#include <unordered_map>
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/Select.h"
#include "components/pkb/clients/QPSClient.h"
#include "models/Entity/DesignEntity.h"

class SelectTupleClause : public Clause {
private:
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;
    std::unordered_set<std::string> synonymsInTable;
    std::vector<TokenObject> tuple;
    QPSClient qpsClient;
    ResultTable evaluateSynonymOrAttributeInTuple(std::string synonym, DesignEntity returnType);

public:
    SelectTupleClause(std::vector<TokenObject> tuple, std::unordered_set<std::string> &synonymsInTable, std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap, QPSClient qpsClient);
    ResultTable evaluateClause() override;
    size_t getNumberOfSynonyms() override;
    std::set<std::string> getAllSynonyms() override;
};

#endif //SPA_SELECTTUPLECLAUSE_H
