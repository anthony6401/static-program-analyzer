#ifndef SPA_CLAUSECREATOR_H
#define SPA_CLAUSECREATOR_H

#include <unordered_map>
#include <memory>
#include "components/qps/query_evaluator/factory/interface/Clause.h"
#include "components/qps/abstract_query_object/SuchThat.h"
#include "components/qps/abstract_query_object/Pattern.h"
#include "components/qps/abstract_query_object/Select.h"
#include "models/Entity/DesignEntity.h"
#include "components/qps/abstract_query_object/With.h"

class ClauseCreator {
public:
    static std::shared_ptr<Clause> createClause(SuchThat relationship, std::unordered_map<std::string, DesignEntity> &synonymToDesignEntityMap, QPSClient &qpsClient);
    static std::shared_ptr<Clause> createClause(qps::Pattern pattern, const std::unordered_map<std::string, DesignEntity> &synonymToDesignEntityMap, QPSClient &qpsClient);
    static std::shared_ptr<Clause> createClause(With with, std::unordered_map<std::string, DesignEntity> &synonymToDesignEntityMap, QPSClient &qpsClient);
    static std::shared_ptr<Clause> createClause(Select select, std::unordered_set<std::string> &tableSynonyms, std::unordered_map<std::string, DesignEntity> &synonymToDesignEntityMap, QPSClient &qpsClient);
};

#endif //SPA_CLAUSECREATOR_H
